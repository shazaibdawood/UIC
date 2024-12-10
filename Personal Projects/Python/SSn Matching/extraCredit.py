import math

file1 = open("summary.txt")
list1 = file1.readlines()
file1.close()

file2 = open("employee.txt")
list2 = file2.readlines()
file2.close()

f1 = {}
f2 = {}

for i in range(len(list1)):
    temp = list1[i]

    temp2 = temp.split("\t")
    string = temp2[-1]
    last = ""
    for j in range(len(string) - 1):
        last += string[j]
    temp2[-1] = last
    key = temp2[0]
    temp2.pop(0)

    f1[key] = temp2

for i in range(len(list2)):
    temp = list2[i]

    temp2 = temp.split("\t")
    string = temp2[-1]
    last = ""
    for j in range(len(string) - 1):
        last += string[j]
    temp2[-1] = last
    key = temp2[0]
    temp2.pop(0)

    f2[key] = temp2


included = open("included.txt", "w")
excluded = open("excluded.txt", "w")

# for i in f2:
#     for j in f1:
#         if(j == i):
#             temp1 = f1[j]
#             temp2 = f2[i]
#             f2[i] = temp2 + temp1
#             break

keyslist = f2.keys()
for i in f2:
    for j in f1:
        if(j == i):
            f2[i] = f2[i] + f1[j]
            
            break
    included.write(i + "^")
    for y in f2[i]:
        included.write(y + "^")
    included.write("\n")
for i in f1:
    if(i not in keyslist):
        excluded.write(i + "^")
        for x in f1[i]:
            excluded.write(x + "^")
        excluded.write("\n")

included.close()
excluded.close()

        
# for i in temp3:
#     print(i, end = " ")
#     for j in temp3[i]:
#         print(j, end = " ")
#     print()


# for i in f2:
#     print(i, end = "^")
#     for j in f2[i]:
#         print(j, end = "^")
#     print()