# In a file called main.py, implement a program that reads and prints the database files. 
# The program should have one input prompt: the string value of the database file (before .txt) to read.

# Your program should open the appropriate database file (either small.txt or large.txt) and print its contents in the following format:

# Alan: 28 42 14
# Edsger: 17 22 19
# Katherine: 36 18 25
# STR list: ['AGATC', 'AATG', 'TATC']
# You may assume that the first row of the file will be the column names. 
# The first column will be the word name and the remaining columns will be the STR counts themselves. 
# You are required to read the whole file and you can not hard-code anything. 
# You should save the data from the file into a container and then printing out the data from this container. 
# The data needs to be stored in a container for the next step. 
# We recommend a container that can be easily searched by STR count.

filename = input()
filename = filename + ".txt"

file = open(filename)
database = file.readlines()
file.close()

DNACodes = database[0]
DNACodes = DNACodes.replace("\n", "")
database.pop(0)

codeCounts = {}
for i in database:
    temp = i.split(",")
    key = temp[0]
    temp.pop(0)

    temp[-1] = temp[-1].replace("\n", "")

    for j in range(len(temp)):
        temp[j] = int(temp[j])

    codeCounts[key] = temp

for i in codeCounts:
    displayString = i + ": "
    for j in codeCounts[i]:
        displayString += str(j) + " "
    print(displayString[0:-1])

STRList = DNACodes.split(",")
STRList.pop(0)
print("STR list:", STRList)