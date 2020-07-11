#!/usr/bin/env python3

import os
import os.path
import shutil
import sys
import string

SOURCE_PATH = '.'
LINUX_DIR = 'linux'
VSCODE_DIR = '.vscode'
APPS_DIR = 'apps'
SRC_FILE = 'T.cpp'
    
def copy_files_tree(dest, project_names):
    try:
        if not os.path.exists(dest):
            os.makedirs(dest)
        
        vscode_src_dir = os.path.join(SOURCE_PATH, LINUX_DIR, VSCODE_DIR)
        vscode_dst_dir = os.path.join(dest, VSCODE_DIR)
        shutil.copytree(vscode_src_dir, vscode_dst_dir)
        
        dest_apps = os.path.join(dest, APPS_DIR)
        os.makedirs(dest_apps)
        template_src_file = os.path.join(SOURCE_PATH, SRC_FILE)
        for name in project_names:      
            dst_src_file = os.path.join(dest, name + '.cpp')
            shutil.copy(template_src_file, dst_src_file)

    except Exception as err:
        print('Failed to copy files to {0}: {1}'.format(dest, err))
        return False
    
    return True

def gen_names(count, names = []):
    if len(names) == 0:
        names = [s for s in string.ascii_uppercase[:count]]
    return names

    
def create(dest, count, names=[]):
    if len(names) == 0 and count > 26:
        print('Number of tasks exceeded!')
        return False
        
    file_names = gen_names(count, names)
        
    if not copy_files_tree(dest, file_names):
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

    if sys.argv[2].isdigit():
        count = int(sys.argv[2])
        create(sys.argv[1], int(sys.argv[2]))
    else:
        names = sys.argv[2:]
        create(sys.argv[1], len(names), names)
   
