# Implement a program that identifies to whom a sequence of DNA belongs. 
# The program should have one input prompt: the integer value of the DNA sequence to process.
# Enter number (1-20): 
# Dna Sequence #1 matches: Edsger
# Enter number (1-20): 
# Dna Sequence #13 matches: No Match.

fileNum = int(input("Enter number (1-20): "))
filename = str(fileNum) + ".txt"

if(1 <= fileNum <= 4):
    file = open("small.txt")
    database = file.readlines()
    file.close()
else:
    file = open("large.txt")
    database = file.readlines()
    file.close()

file = open(filename)
sequence = file.readline()
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

STRList = DNACodes.split(",")
STRList.pop(0)

keyList = []
for i in STRList:
    temp = sequence.count(i)
    keyList.append(temp)

print()
print("Dna Sequence #", end = "")
print(fileNum, "matches: ", end = "")

matched = False
for i in codeCounts:
    if(keyList == codeCounts[i]):
        print(i)
        matched = True
if(not matched):
    print("No Match.")
