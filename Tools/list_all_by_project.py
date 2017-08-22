import os
import traceback

dir_list = ("Core", "Application")
ext_list = ("h", "cpp", "c")

file_count = 0

try:
    print("File list by project:")
    print("===============")
    for directory in dir_list:
        for (dir,_, files) in os.walk("..\\" + directory):
            for f in files:
                path = os.path.join(dir, f)
                if os.path.exists(path) and path.endswith(ext_list):
                    print(path)
                    file_count += 1
    print("===============")
    print("Total file count = ", file_count)
except:
    traceback.print_exc()
input("press any key to exit...")

