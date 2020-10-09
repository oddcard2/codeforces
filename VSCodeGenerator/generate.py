#!/usr/bin/env python3

import os
import os.path
import shutil
import sys
import string
import platform

SOURCE_PATH = '.'
WIN_DIR = 'win'
LINUX_DIR = 'linux'
VSCODE_DIR = '.vscode'
APPS_DIR = 'apps'
SRC_FILE = 'T.cpp'
BITS_DIR='bits'
WIN_HIGHTAIL_APPS_DIR='C:\\dmitrys\\Hightail\\Apps'
LINUX_HIGHTAIL_APPS_DIR='/home/dmitry/Projects/Oddcard2/HighTail/Apps'

WIN_HELP = """VSCode C++ for Windows:
https://code.visualstudio.com/docs/cpp/config-msvc

1. Run Developer Command Prompt (type Developer in Start menu search bar)
2. Go to project directory
3. Type \"code .\"
"""
    
def copy_files_tree(dest, project_names, is_win):
    try:
        if not os.path.exists(dest):
            os.makedirs(dest)
        
        os_dir = LINUX_DIR
        hightail_apps_dir = LINUX_HIGHTAIL_APPS_DIR
        if is_win:
            os_dir = WIN_DIR
            hightail_apps_dir = WIN_HIGHTAIL_APPS_DIR
        
        vscode_src_dir = os.path.join(SOURCE_PATH, os_dir, VSCODE_DIR)
        vscode_dst_dir = os.path.join(dest, VSCODE_DIR)
        shutil.copytree(vscode_src_dir, vscode_dst_dir)
        
        dest_apps = os.path.join(dest, APPS_DIR)
        os.makedirs(dest_apps)
        template_src_file = os.path.join(SOURCE_PATH, SRC_FILE)
        for name in project_names:      
            dst_src_file = os.path.join(dest, name + '.cpp')
            shutil.copy(template_src_file, dst_src_file)
        
        # copies bits/stdc++.h file for Windows
        if is_win:
            bits_dst_dir = os.path.join(dest, BITS_DIR)
            shutil.copytree(BITS_DIR, bits_dst_dir)
        
        # creates symlink to apps directory
        try:
            apps_abs_path = os.path.abspath(dest_apps)
            if os.path.islink(hightail_apps_dir):
                os.unlink(hightail_apps_dir)
            os.symlink(apps_abs_path, hightail_apps_dir)
            print('Symlink {0} -> {1} created'.format(apps_abs_path, hightail_apps_dir))
        except Exception as e:
            print('Failed to create link: {0}'.format(e))

    except Exception as err:
        print('Failed to copy files to {0}: {1}'.format(dest, err))
        return False
    
    return True

def gen_names(count, names = []):
    if len(names) == 0:
        names = [s for s in string.ascii_uppercase[:count]]
    return names

    
def create(dest, count, is_win, names=[]):
    if len(names) == 0 and count > 26:
        print('Number of tasks exceeded!')
        return False
        
    file_names = gen_names(count, names)
        
    if not copy_files_tree(dest, file_names, is_win):
        print('Failed to copy files to {0}'.format(dest))
        return False
        
    return True

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("Use app path num_of_tasks")
        print('For example:')
        print('\tgenerate.py ../cf544div2 5')
        print('\tgenerate.py ../cf544div2 A1 A2 B C1 C2')
        sys.exit()
    
    is_win = platform.system() == 'Windows'

    if sys.argv[2].isdigit():
        count = int(sys.argv[2])
        create(sys.argv[1], int(sys.argv[2]), is_win)
    else:
        names = sys.argv[2:]
        create(sys.argv[1], len(names), is_win, names)
    if is_win:
        print(WIN_HELP)
