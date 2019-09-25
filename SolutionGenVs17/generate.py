import uuid
import os
import os.path
import shutil
import sys
import string

SOURCE_PATH = 'template'
SOLUTION_FILE = 'Contest.sln'
PROJECT_LIST_TEMPLATE_FILE = 'project_list.template'
PROJECTS_CONFIG_LIST_TEMPLATE_FILE = 'project_configurations.template'
CLEAN_BATCH_FILE = 'clean.bat'
BITS_DIR = 'bits'
PROJECT_DIR = 'Project'

def get_uuid():
    return str(uuid.uuid4()).upper()

def gen_solution_projects_list(template_path, names, uuids):
    with open(template_path, 'r') as f:
        template_data = f.read()
    
    text_blocks = [template_data.replace("@PROJ_NAME@", name).replace("@PROJ_UUID@", uuid) for name, uuid in zip(names, uuids)]
    return '\n'.join(text_blocks)
 
def gen_solution_project_configurations_list(template_path, uuids):
    with open(template_path, 'r') as f:
        template_data = f.read()
    
    text_blocks = [template_data.replace("@PROJ_UUID@", uuid) for uuid in uuids]
    return '\n'.join(text_blocks)

def process_solution_file(dest, uuid, proj_names, proj_uuids):
    try:
        template_path = os.path.join(SOURCE_PATH, PROJECT_LIST_TEMPLATE_FILE)
        projects_content = gen_solution_projects_list(template_path, proj_names, proj_uuids)
        template_path = os.path.join(SOURCE_PATH, PROJECTS_CONFIG_LIST_TEMPLATE_FILE)
        project_configurations_content = gen_solution_project_configurations_list(template_path, proj_uuids)
        
        file_path = os.path.join(dest, SOLUTION_FILE)
        with open(file_path, 'r+') as f:
            filedata = f.read()
            newdata = filedata.replace("@PROJECTS@", projects_content).replace("@PROJECTS_CONFIGURATIONS@", project_configurations_content).replace("@SOLUTION_UUID@", uuid)
            f.seek(0)
            f.write(newdata)
            f.truncate()
    except Exception as err:
        print('Failed to process solution file {0}: {1}'.format(file_path, err))
        return False
    return True
    
def process_project_file(file_path, name, uuid):
    with open(file_path, 'r+') as f:
        file_data = f.read()
        newdata = file_data.replace("@PROJ_UUID@", uuid).replace("@PROJ_NAME@", name)
        f.seek(0)
        f.write(newdata)
        f.truncate()
    return True
    
def copy_files_tree(dest, project_names):
    try:
        if not os.path.exists(dest):
            os.makedirs(dest)
        
        src_solution = os.path.join(SOURCE_PATH, SOLUTION_FILE)
        dest_solution = os.path.join(dest, SOLUTION_FILE)
        shutil.copy(src_solution, dest_solution)
       
        src_clean_bat = os.path.join(SOURCE_PATH, CLEAN_BATCH_FILE)
        dest_clean_bat = os.path.join(dest, CLEAN_BATCH_FILE)
        shutil.copy(src_clean_bat, dest_clean_bat)
        
        src_bits = os.path.join(SOURCE_PATH, BITS_DIR)
        dest_bits = os.path.join(dest, BITS_DIR)
        shutil.copytree(src_bits, dest_bits)
        
        for name in project_names:
            src_proj_dir = os.path.join(SOURCE_PATH, PROJECT_DIR)
            dst_proj_dir = os.path.join(dest, name)
            shutil.copytree(src_proj_dir, dst_proj_dir)
    except Exception as err:
        print('Failed to copy files to {0}: {1}'.format(dest, err))
        return False
    
    return True
    
def process_projects(dest, project_names, uuids):
    try:
        for name, uuid in zip(project_names, uuids):
            orig_proj_file = os.path.join(dest, name, 'win', 'T.vcxproj')
            new_proj_file = os.path.join(dest, name, 'win', '{0}.vcxproj'.format(name))
            os.rename(orig_proj_file, new_proj_file)
            
            orig_filters_file = os.path.join(dest, name, 'win', 'T.vcxproj.filters')
            new_filters_file = os.path.join(dest, name, 'win', '{0}.vcxproj.filters'.format(name))
            os.rename(orig_filters_file, new_filters_file)
            
            if not process_project_file(new_proj_file, name, uuid):
                print('Failed to process project file {0}'.format(new_proj_file))
                return False
            
    except Exception as err:
        print('Failed to process projects: {0}'.format(err))
        return False
    
    return True
    
def gen_names_and_uuids(count):
    names = [s for s in string.ascii_uppercase[:count]]
    uuids = [get_uuid() for _ in range(count)]
    return (names, uuids)
    
def create(dest, count):
    if count > 26:
        print('Number of projects exceeded!')
        return False

    proj_names, proj_uuids = gen_names_and_uuids(count)
    solution_uuid = get_uuid()
    
    if not copy_files_tree(dest, proj_names):
        print('Failed to copy files to {0}'.format(dest))
        return False
    
    if not process_solution_file(dest, solution_uuid, proj_names, proj_uuids):
        print('Failed to process solution file in {0}'.format(dest))
        return False

    if not process_projects(dest, proj_names, proj_uuids):
        print('Failed to process projects in {0}'.format(dest))
        return False
        
    return True

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Use app path num_of_projects")
        print('For example:')
        print('\tgenerate.py ../cf544div2 5')
        sys.exit()

    create(sys.argv[1], int(sys.argv[2]))
   