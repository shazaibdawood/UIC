import random
import turtle

viewAlgorithm = turtle.Turtle()
viewAlgorithm.hideturtle()
viewAlgorithm.penup()

# @param numElements: Size of the unsorted list of integers
# @param maxInt: Maximum integer value in unsorted list
# @description: Creates random numbers in the specified range and appends them to the list unsortedList
# @return unsortedList: An unsorted list of integers with range 0 - maxInt and size numElements

def createUnsortedList(numElements, maxInt):
    unsortedList = []
    for i in range(numElements):
        temp = random.randint(0, maxInt)
        unsortedList.append(temp)
    
    return unsortedList

# @param unsortedList: An unsorted list of integers with range 0 - maxInt and size numElements
# @description: Creates and/or overwrites data in file 'unsorted.txt'
#               All elements in list unsortedList are written into the file
# @return void

def writeToFile(unsortedList):
    file = open("unsorted.txt", "w")

    for i in unsortedList:
        file.write(str(i) + "\n")
    file.close()

# @param None
# @description: Reads in unsorted integers from file "unsorted.txt" and appends them to the list unsortedList
# @return unsortedList: A list of unsorted integers from the file "unsorted.txt"

def readUnsortedData():
    file = open("unsorted.txt")
    unsortedList = file.readlines()

    for i in range(len(unsortedList)):
        temp = unsortedList[i][0:-1]
        unsortedList[i] = int(temp)
    
    return unsortedList        

def findMax(unsortedList):
    max = 0

    for i in unsortedList:
        if(i > max):
            max = i
    
    return max

def drawSortingMechanism(unsortedList):
    global viewAlgorithm
    global height
    global width

    viewAlgorithm.goto((width / -2) + 10, (height / -2) + 10)
    for i in range(len(unsortedList)):
        viewAlgorithm.pendown()
        viewAlgorithm.begin_fill()
        viewAlgorithm.setheading(90)
        viewAlgorithm.forward(unsortedList[i])
        viewAlgorithm.setheading(180)
        viewAlgorithm.forward(5)
        viewAlgorithm.setheading(270)
        viewAlgorithm.forward(unsortedList[i])
        viewAlgorithm.setheading(0)
        viewAlgorithm.forward(5)
        viewAlgorithm.end_fill()

        viewAlgorithm.penup()
        viewAlgorithm.forward(10)

numElements = int(input("Enter the number of elements created: "))
maxInt = int(input("Enter the max integer value: "))
print()

unsortedList = createUnsortedList(numElements, maxInt)
writeToFile(unsortedList)
unsortedList = readUnsortedData()

s = turtle.Screen()
s.bgcolor("white")
s.tracer(False)
s.title("Sorting Algorithms")

height = findMax(unsortedList) + 20
width = 10 + (10 * len(unsortedList))

print(width, height)

s.setup(width, height)

drawSortingMechanism(unsortedList)
turtle.mainloop()