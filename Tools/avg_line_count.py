import os
import traceback

dir_list = ("Core", "Application")
ext_list = ("h", "cpp", "c")

total_line_count = 0
total_file_count = 0

print("Average line count by project:")
print("===============")
try:
    for directory in dir_list:
        project_line_count = 0
        project_file_count = 0
        for (dir,_, files) in os.walk("..\\" + directory):
                for f in files:
                    path = os.path.join(dir, f)
                    if os.path.exists(path) and path.endswith(ext_list):
                        project_line_count += len(open(path).readlines(  ))
                        project_file_count += 1
        total_line_count += project_line_count
        total_file_count += project_file_count
        project_line_count /= project_file_count
        print(directory + ": ", project_line_count)
    print("===============")
    total_line_count /= total_file_count
    print("Average line count = ", total_line_count)
except:
    traceback.print_exc()
input("press any key to exit...")
