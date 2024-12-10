# Implement a program that identifies to whom a sequence of all 20 DNA sequences belongs. 
# The program has no inputs, it should loop through all 20 files and identify each one. 

# Dna Sequence #1 matches: Edsger
# Enter number (1-20): 
# Dna Sequence #13 matches: No Match.

def formatData(fileNum):
    # Input is an integer that is then converted into the names of the data files
    # Small.txt is used when the number is less than or equal to 4
    # Large.txt is used when the number is greater than 4
    # Splits data and returns:
    # Dictionary of lists by person name,
    # List of STRs,
    # String of the DNA sequence


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

    return sequence, STRList, codeCounts

def findConsecutiveSTR(sequence, STRList, codeCounts):
    # Input is:
    # String of the DNA sequence,
    # List of the STRs,
    # Dictionary of the key lists by name

    # Replaces each STR in a copy of the DNA sequence with a single variable
    # Counts the number of consecutive occurances of that variable
    # Creates a key list of the maximum occurances of each STR in the DNA sequence
    # Compares that list to the list associated with each person in the Dictionary
    # Prints out the name of the person that the list matches with
    # Or else prints out "No Match."


    keyList = []
    for i in STRList:
        copy = sequence[:]
        copy = copy.replace(i, "x")

        count = 0
        maximum = 0
        for j in copy:
            if(j == "x"):
                count += 1
                maximum = max(maximum, count)
            else:
                count = 0
                maximum = max(maximum, count)
        keyList.append(maximum)

    print("Dna Sequence #", end = "")
    print(fileNum, "matches: ", end = "")

    matched = False
    for i in codeCounts:
        if(keyList == codeCounts[i]):
            print(i)
            matched = True
    if(not matched):
        print("No Match.")


for fileNum in range(1,21):
    sequence, STRList, codeCounts = formatData(fileNum)
    findConsecutiveSTR(sequence, STRList, codeCounts)