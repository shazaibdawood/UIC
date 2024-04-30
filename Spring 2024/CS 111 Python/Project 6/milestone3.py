# You will need this function to write this milestone 
# but you will also need the code you wrote from Milestone #1

# This function reads in data from the file named filename.
# (e.g. words, solution = readFile("Day0.txt")
# sets up list of words and solution for Day 0 board
# INPUT:
# filename - a string, e.g. "Day0.txt."
# OUTPUTS:
# words - a list of words (strings) that will make up the 4 by 4 gameboard
# solution - a dictionary of the solution, e.g. solution = {"data types": {"int",
# "float", "string", "boolean"}, ...}
def readFile(filename):
    file = open(filename)
    list = file.readlines()
    words = []  # list of all words
    solution = {}  # dictionary of solution
    for line in range(1, len(list) + 1): # line is line number
        if line % 2 == 1: # odd, 1, 3, 5, 7 (categories)
            category = list[line - 1]
        else:  # even, 2, 4, 6, 8 (words)
            tokens = list[line - 1].split(", ")
            tokens[-1] = tokens[-1].strip()
            solution[category] = set(tokens)
            words.extend(tokens)  # clean up new line character
    return words, solution
    
# -Your function should accept a list of words as a parameter and draw those words into the grid.
# -Your function should accept a list of 16 word boxes (which should be a list of 16 turtles) as a parameter.  
# This is really helpful for game play later as you will more easily be able to access and change each word box.
# -Your function to call/use the function(s) you wrote in MS 1

import turtle
import math
import random

# Constants
boxCount = 16
HEIGHT = 100
WIDTH = 100
SPACING = 20
FONT = "Times New Roman"
FONTSIZE = 11
ROWS = 4
COLS = 4
boxColor = "silver"
textColor = "darkmagenta"
selectedBoxColor = "lightcoral"
selectedTextColor = "black"
selectedBoxCount = 0

# Input is number of turtles to be created
# Runs through a for loop and appends each turtle to the list
# Returns the list of turtles
def createTurtleList(boxCount):
    boxes = []
    for i in range(boxCount):
        boxes.append(turtle.Turtle())
    
    return boxes 

# Creates a list of x,y coordinate lists
# Input is the number, dimensions, and spacing between boxes
# Output is a list of lists of coordinates
def getCoordinates():
    global ROWS
    global COLS
    global WIDTH
    global HEIGHT
    global SPACING

    coordinates = []
    x = -230
    y = 230
    for i in range(ROWS):
        for j in range(COLS):
            midX = int(x + WIDTH / 2)
            midY = int(y - HEIGHT / 2)
            coordinates.append([midX, midY])
            x += (WIDTH + SPACING)
        y -= (HEIGHT + SPACING)
        x = -230
    return coordinates

def drawBox(boxes, coordinates):
    global WIDTH
    global HEIGHT
    global boxColor
    global boxCount

    for i in range(boxCount):

        x = coordinates[i][0]
        y = coordinates[i][1]

        boxes[i].hideturtle()
        boxes[i].penup()
        boxes[i].goto(x - (WIDTH / 2), y - (HEIGHT / 2))

        boxes[i].color(boxColor)
        boxes[i].begin_fill()
        boxes[i].pendown()
        boxes[i].forward(WIDTH)
        boxes[i].left(90)
        boxes[i].forward(HEIGHT)
        boxes[i].left(90)
        boxes[i].forward(WIDTH)
        boxes[i].left(90)
        boxes[i].forward(HEIGHT)
        boxes[i].left(90)
        boxes[i].end_fill()
        boxes[i].penup()

def shuffleWords(words):
    shuffledWords = []
    for i in range(boxCount):
        num = random.randint(0, len(words) - 1)
        shuffledWords.append(words[num])
        words.pop(num)

    return shuffledWords


def writeText(shuffledWords, boxes, coordinates):
    global boxCount
    global FONT
    global FONTSIZE
    global textColor

    for i in range(boxCount):
        x = coordinates[i][0]
        y = coordinates[i][1]

        text = shuffledWords[i].upper()

        boxes[i].goto(x, y)
        boxes[i].pendown()
        boxes[i].color(textColor)
        boxes[i].write(text, False, align = 'center', font = (FONT, FONTSIZE, "normal"))
        boxes[i].penup()

def selectBoxChoiceList():
    global boxCount

    selectBoxChoiceList = []
    for i in range(boxCount):
        selectBoxChoiceList.append(False)
    return selectBoxChoiceList

def selectUnselectBox(x , y):
    global boxCount
    global coordinates
    global boxes
    global shuffledWords
    global selectedBoxColor
    global selectedTextColor
    global selectedBoxCount
    global selectBoxChoiceList
    global boxColor
    global textColor
    
    count = -1
    for i in range(boxCount):
        if(coordinates[i][0] - (WIDTH / 2) <= x <= coordinates[i][0] + (WIDTH / 2) and coordinates[i][1] - (HEIGHT / 2) <= y <= coordinates[i][1] + (HEIGHT / 2)):
            count = i

    if(count >= 0 and selectBoxChoiceList[count] == False):
        if(0 <= selectedBoxCount < 4):
            x = coordinates[count][0]
            y = coordinates[count][1]

            boxes[count].clear()

            boxes[count].hideturtle()
            boxes[count].penup()
            boxes[count].goto(x - (WIDTH / 2), y - (HEIGHT / 2))

            boxes[count].color(selectedBoxColor)
            boxes[count].begin_fill()
            boxes[count].pendown()
            boxes[count].forward(WIDTH)
            boxes[count].left(90)
            boxes[count].forward(HEIGHT)
            boxes[count].left(90)
            boxes[count].forward(WIDTH)
            boxes[count].left(90)
            boxes[count].forward(HEIGHT)
            boxes[count].left(90)
            boxes[count].end_fill()
            boxes[count].penup()

            text = shuffledWords[count].upper()
            boxes[count].goto(x, y)
            boxes[count].pendown()
            boxes[count].color(selectedTextColor)
            boxes[count].write(text, False, align = 'center', font = (FONT, FONTSIZE, "normal"))
            boxes[count].penup()
            selectedBoxCount += 1
            selectBoxChoiceList[count] = True
        else:
            selectedBoxCount = 4
    elif(count >= 0 and selectBoxChoiceList[count] == True):
        x = coordinates[count][0]
        y = coordinates[count][1]

        boxes[count].clear()

        boxes[count].hideturtle()
        boxes[count].penup()
        boxes[count].goto(x - (WIDTH / 2), y - (HEIGHT / 2))

        boxes[count].color(boxColor)
        boxes[count].begin_fill()
        boxes[count].pendown()
        boxes[count].forward(WIDTH)
        boxes[count].left(90)
        boxes[count].forward(HEIGHT)
        boxes[count].left(90)
        boxes[count].forward(WIDTH)
        boxes[count].left(90)
        boxes[count].forward(HEIGHT)
        boxes[count].left(90)
        boxes[count].end_fill()
        boxes[count].penup()

        text = shuffledWords[count].upper()
        boxes[count].goto(x, y)
        boxes[count].pendown()
        boxes[count].color(textColor)
        boxes[count].write(text, False, align = 'center', font = (FONT, FONTSIZE, "normal"))
        boxes[count].penup()
        selectedBoxCount -= 1
        selectBoxChoiceList[count] = False
        

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    # Here is a screen object to use
    s = turtle.getscreen()
    s.tracer(False)

    filename = "Day0.txt"

    words, solution = readFile(filename)
    boxes = createTurtleList(boxCount)
    coordinates = getCoordinates()
    shuffledWords = shuffleWords(words)
    
    drawBox(boxes, coordinates)
    writeText(shuffledWords, boxes, coordinates)

    selectBoxChoiceList = selectBoxChoiceList()

    s.onclick(selectUnselectBox)

    #turtle.mainloop() # If this is removed, the graphics window will close and you won't see your graphics