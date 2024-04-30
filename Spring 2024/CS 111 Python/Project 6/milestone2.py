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

def writeText(words, boxes, coordinates):
    global boxCount
    global FONT
    global FONTSIZE
    global textColor

    wordsCopy = words[:]

    for i in range(boxCount):
        x = coordinates[i][0]
        y = coordinates[i][1]

        # Shuffling words
        num = random.randint(0, len(wordsCopy) - 1)
        text = wordsCopy[num].upper()
        wordsCopy.pop(num)

        boxes[i].goto(x, y)
        boxes[i].pendown()
        boxes[i].color(textColor)
        boxes[i].write(text, False, align = 'center', font = (FONT, FONTSIZE, "normal"))
        boxes[i].penup()

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    # Here is a screen object to use
    s = turtle.getscreen()
    s.tracer(False)

    filename = "Day0.txt"

    words, solution = readFile(filename)
    boxes = createTurtleList(boxCount)
    coordinates = getCoordinates()
    
    drawBox(boxes, coordinates)
    writeText(words, boxes, coordinates)

    # turtle.mainloop() # If this is removed, the graphics window will close and you won't see your graphics