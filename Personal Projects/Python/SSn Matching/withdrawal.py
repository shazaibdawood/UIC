import math

file1 = open("file1.txt")
list1 = file1.readlines()
file1.close()

file3 = open("file3.txt")
list3 = file3.readlines()
file3.close()

f1 = {}
f3 = {}

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

for i in range(len(list3)):
    temp = list3[i]

    temp2 = temp.split("\t")
    string = temp2[-1]
    last = ""
    for j in range(len(string) - 1):
        last += string[j]
    temp2[-1] = last
    key = temp2[0]
    temp2.pop(0)

    f3[key] = temp2



temp3 = []
for i in f3:
    for j in f1:
        if(i == j):
            f1[j][0] = f3[i][0]
            break



for i in f1:
    print(i, end = "^")
    for j in f1[i]:
        print(j, end = "^")
    print()

# print(f3)