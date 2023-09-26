import os

def find_all_dep_file(path):
    files = []
    for file in os.listdir(path):
        if file.endswith(".d"):
            files.append(os.path.join(path, file))
        elif os.path.isdir(os.path.join(path, file)):
            files += find_all_dep_file(os.path.join(path, file))
    return files
