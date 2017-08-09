import os

dir_list = ("Core", "Application")
ext_list = ("h", "cpp", "c")

total_count = 0

print("Line count by project:")
print("===============")
for directory in dir_list:
    count = 0
    for (dir,_, files) in os.walk("..\\" + directory):
            for f in files:
                path = os.path.join(dir, f)
                if os.path.exists(path) and path.endswith(ext_list):
                    count += len(open(path).readlines(  ))
    total_count += count
    print(directory + ": ", count)
print("===============")
print("Total count = ", total_count)
input("")