import os
import traceback

total_count = 0
search_text = input("Enter the text to be searched:\n")

print("Search results for \"" + search_text + "\":")
print("===============")

try:
    cwd = os.getcwd()
    for (dir,_, files) in os.walk(cwd):
        for f in files:
            found = 0
            path = os.path.join(dir, f)
            try:
               with open(f, "r", encoding="latin-1") as file_contents:
                   line_num = 1
                   for line in file_contents:
                       index = line.find(search_text)
                       if index > -1:
                           if found == 0:
                               print(path)
                               found = 1
                           print("    line", line_num, end=": ")
                           print(line, end="")
                           total_count += 1
                           line_num +=1
            except:
                print("can't open file" + path)
                break
    	
    print("===============")
    print("Total matching entries found = ", total_count)
except:
    traceback.print_exc()
input("press any key to exit...")
