import uuid
import os
import os.path
import shutil
import sys

def copy_template(proj_name, path):
    #recursive copying template directory -> path/proj_name
    shutil.copytree("template", os.path.join(path, proj_name))
    #rename files in .idea direcory (replace T to proj_name)
    idea_dir = os.path.join(path, proj_name, ".idea")
    for filename in os.listdir(idea_dir):
        if filename.startswith("T"):
            os.rename(os.path.join(idea_dir, filename), os.path.join(idea_dir, proj_name + filename[1:]))

            
def replace_file_content(file_name, proj_id, proj_name):
    f = open(file_name,'r')
    filedata = f.read()
    f.close()

    newdata = filedata.replace("@PROJ_NAME@", proj_name).replace("@PROJ_UUID@", proj_id)

    f = open(file_name,'w')
    f.write(newdata)
    f.close()
    
def prepare(proj_name, path):
    #generate project uuid
    proj_id = str(uuid.uuid4())
    
    #replace @PROJ_NAME@ and @PROJ_UUID@
    idea_dir = os.path.join(path, proj_name, ".idea")
    for filename in os.listdir(idea_dir):
        f = os.path.join(idea_dir, filename)
        replace_file_content(f, proj_id, proj_name)

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Use app proj_name path")
        print("For example: generate.py A ../cf544div2")
        sys.exit()

    proj_name=str(sys.argv[1])
    out_path=str(sys.argv[2])
    
    copy_template(proj_name, out_path)
    prepare(proj_name, out_path)
   