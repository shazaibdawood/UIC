import matplotlib.pyplot as plt

# Your code should be able to plot all sequence files listed. 
# The points from this milestone will solely depend on the plot png's your program produces. 
# They will be manually graded by TA's. 
# The autograder here will only be making sure your outputs are correct, but will not be worth any points. 

# When we run your code to generate your plots, we will first run the command:
# rm *.png
# which will delete any images in your filetree.

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
    # Stores the name of the person that the list matches with
    # Or else stores "No Match."


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

    matched = False
    for i in codeCounts:
        if(keyList == codeCounts[i]):
            person  = i
            matched = True
    if(not matched):
        person = "No Match"
    
    return person, keyList

def drawPlot(fileNum, person, keyList, STRList):
    # Input is:
    # file number,
    # matched person,
    # list of STRs,
    # list of consecutive DNA matches

    # draws a bar graph for each file

    color = ["Red", "Orange", "Yellow", "Green", "Cyan", "Blue", "Purple", "Black"]
    plt.figure()
    bars = plt.bar(keyList, STRList)

    for i in range(len(bars)):
        bars[i].set_color(color[i])
    
    title = str(fileNum) + ".txt: " + person
    save = str(fileNum) + ".png"
    
    plt.title(title)
    plt.savefig(save)

def drawSubplot():
    color = ["Red", "Orange", "Yellow", "Green", "Cyan", "Blue", "Purple", "Black"]
    plot, grid = plt.subplots(4, 5)
    plot.set_figheight(10)
    plot.set_figwidth(15)

    x = 0
    y = 0
    for fileNum in range(1, 21):
        sequence, STRList, codeCounts = formatData(fileNum)
        person, keyList = findConsecutiveSTR(sequence, STRList, codeCounts)

        bars = grid[y, x].barh(STRList, keyList)
        for i in range(len(bars)):
            bars[i].set_color(color[i])

        title = str(fileNum) + ".txt: " + person
        grid[y, x].set_title(title)               

        x += 1
        if(x > 4):
            y += 1
            x = 0
    plt.suptitle("Extra Credit")
    plot.subplots_adjust(wspace = 1, hspace = 0.5)
    plt.savefig("extraCredit.png")
        



for fileNum in range(1,21):
    sequence, STRList, codeCounts = formatData(fileNum)
    person, keyList = findConsecutiveSTR(sequence, STRList, codeCounts)
    drawPlot(fileNum, person, STRList, keyList)
drawSubplot()