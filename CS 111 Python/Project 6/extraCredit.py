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
selectedBoxCount = 0 # Updated whenever a word box is selected. Max count is 4
mistakeCount = 4 # Gameover boolean is set to True when mistakes count is 0
gameover = False
categories = [] 

submit = turtle.Turtle()
submit.hideturtle()

mistakes = turtle.Turtle()
mistakes.hideturtle()

categoryFound = turtle.Turtle()
categoryFound.hideturtle()

displayCategories = turtle.Turtle()
displayCategories.hideturtle()

title = turtle.Turtle()
title.hideturtle()

# Input is number of turtles to be created
# Runs through a for loop and appends each turtle to the list
# Returns the list of turtles
def createTurtleList(boxCount):
    boxes = []
    for i in range(boxCount):
        boxes.append(turtle.Turtle())
    
    return boxes 

def drawTitle():
    global title
    global FONT
    global FONTSIZE
    global boxColor
    global textColor

    title.penup()
    title.goto((-230, 270))

    title.color(boxColor)
    title.begin_fill()
    title.pendown()
    title.forward(460)
    title.right(90)
    title.forward(30)
    title.right(90)
    title.forward(460)
    title.right(90)
    title.forward(30)
    title.end_fill()
    title.penup()

    title.goto((0, 245))
    title.pendown()
    title.color(textColor)
    text = "Create Four Groups of Four!"
    title.write(text, False, align = 'center', font = (FONT, FONTSIZE, "normal"))
    title.penup()

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

# Draws empty grey boxes with each turtle from the list of turtles
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

# Shuffles the words and returns a list of shuffled words
def shuffleWords(words):
    shuffledWords = []
    for i in range(boxCount):
        num = random.randint(0, len(words) - 1)
        shuffledWords.append(words[num])
        words.pop(num)

    return shuffledWords

# Writes the words in the middle of the boxes previously drawn
def writeText(shuffledWords, boxes, coordinates):
    global boxCount
    global FONT
    global FONTSIZE
    global textColor

    for i in range(boxCount):
        x = coordinates[i][0]
        y = coordinates[i][1]

        text = shuffledWords[i].upper()

        boxes[i].goto(x, y - 10)
        boxes[i].pendown()
        boxes[i].color(textColor)
        boxes[i].write(text, False, align = 'center', font = (FONT, FONTSIZE, "normal"))
        boxes[i].penup()

# Creates a list of false booleans for every word box
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
    global submit
    
    if(not gameover):
        count = -1
        submitSelected = False
        for i in range(boxCount):
            if(coordinates[i][0] - (WIDTH / 2) <= x <= coordinates[i][0] + (WIDTH / 2) and coordinates[i][1] - (HEIGHT / 2) <= y <= coordinates[i][1] + (HEIGHT / 2)):
                count = i
        if(130 <= x <= 230 and -270 <= y <= -240):
            submitSelected = True
        
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
                boxes[count].goto(x, y - 10)
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
            boxes[count].goto(x, y - 10)
            boxes[count].pendown()
            boxes[count].color(textColor)
            boxes[count].write(text, False, align = 'center', font = (FONT, FONTSIZE, "normal"))
            boxes[count].penup()
            selectedBoxCount -= 1
            selectBoxChoiceList[count] = False

        if(selectedBoxCount >= 4):
            submit.clear()
            drawSubmitButton(textColor, boxColor)
        else:
            submit.clear()
            drawSubmitButton(boxColor, textColor)

        if(submitSelected and selectedBoxCount >= 4):
            findWords()

# Checks if wordsSelected match a category in solution.
# If they do, returns the category.  If not, returns empty string.
# Assumes all words are lower case (in solution and wordsSelected).
# INPUTS:
# solution - a dictionary that pairs the category with the set of four words
# wordsSelected - a set of four words entered by player
# OUTPUT:
# category - a string that represents the category found
def checkSolution(solution, wordsSelected):
    for category in solution:
        if wordsSelected == solution[category]:
            return category
    return ""

# Draws the submit button
def drawSubmitButton(boxColor, textColor):
    global submit
    global FONT
    global FONTSIZE

    submit.hideturtle()
    submit.penup()
    submit.goto((230, -270))

    submit.color(boxColor)
    submit.begin_fill()
    submit.pendown()
    submit.left(90)
    submit.forward(30)
    submit.left(90)
    submit.forward(100)
    submit.left(90)
    submit.forward(30)
    submit.left(90)
    submit.forward(100)
    submit.end_fill()
    submit.penup()

    submit.goto((180, -265))
    submit.pendown()
    submit.color(textColor)
    text = "SUBMIT"
    submit.write(text, False, align = 'center', font = (FONT, FONTSIZE, "normal"))
    submit.penup()

# Finds the words selected and checks if they match a category
# Updates mistakes if category is not found
def findWords():
    global selectBoxChoiceList
    global solution
    global shuffledWords
    global mistakes
    global mistakeCount
    global gameover
    global selectedBoxCount
    global boxColor
    global textColor
    global submit
    global categories
    global boxes
    global boxCount
    
    selectedIndexes = []
    for i in range(len(selectBoxChoiceList)):
        if(selectBoxChoiceList[i] == True):
            selectedIndexes.append(i)
    
    wordsSelected = set()
    for i in selectedIndexes:
        wordsSelected.add(shuffledWords[i])
    
    category = checkSolution(solution, wordsSelected)
    categories.append(category.upper())
    
    if(len(category) > 0):
        showCategory(categories)
        removeBoxes(selectedIndexes)
        selectedBoxCount = 0

        if(len(boxes) <= 0):
            printCategory()
        for i in range(len(selectBoxChoiceList)):
            selectBoxChoiceList[i] = False
    else:
        mistakeCount -= 1
        mistakes.clear()
        drawMistakes()
    
# Removes the selected boxes if they match a category
# updates the list of turtles and shuffled words
# last 4 coordinates in the list of coordinates are removed
def removeBoxes(selectedIndexes):
    global boxes
    global coordinates
    global shuffledWords
    global boxCount
    global boxColor
    global textColor
  
    newBoxes = []
    newWords = []
    for i in range(len(boxes)):
        if(not i in selectedIndexes):
            newBoxes.append(boxes[i])
            newWords.append(shuffledWords[i])
    for i in boxes:
        i.clear()
    boxes.clear()
    boxes = newBoxes[:]
    shuffledWords = newWords[:]   
            
    coordinates.pop(-1)
    coordinates.pop(-1)
    coordinates.pop(-1)
    coordinates.pop(-1)

    boxCount -= 4 
    for i in boxes:
        i.clear()
    mistakes.clear()
    submit.clear()

    drawBox(boxes, coordinates)
    writeText(shuffledWords, boxes, coordinates)
    drawMistakes()
    drawSubmitButton(boxColor, textColor)

# Displays the number of mistakes remaining
def drawMistakes():
    global mistakes
    global FONT
    global FONTSIZE
    global boxColor
    global textColor
    global mistakeCount
    global gameover

    mistakes.penup()
    mistakes.goto(-230, -240)

    mistakes.pendown()
    mistakes.color(boxColor)
    mistakes.begin_fill()
    mistakes.forward(340)
    mistakes.right(90)
    mistakes.forward(30)
    mistakes.right(90)
    mistakes.forward(340)
    mistakes.right(90)
    mistakes.forward(30)
    mistakes.right(90)
    mistakes.end_fill()
    mistakes.penup()

    mistakes.goto((-60, -265))
    mistakes.pendown()
    mistakes.color(textColor)

    if(mistakeCount > 0):
        text = "MISTAKES REMAINING: " + (mistakeCount * "X")
    else:
        text = "GAME OVER"
        gameover = True
    mistakes.write(text, False, align = 'center', font = (FONT, FONTSIZE, "normal"))
    mistakes.penup()

# Ending Screen
# All categories are printed to the screen
def printCategory():
    global categoryFound
    global selectedBoxColor
    global selectedTextColor
    global FONT
    global categories
    global displayCategories

    displayCategories.clear()

    categoryFound.penup()
    categoryFound.goto(-230, 120)

    categoryFound.pendown()
    categoryFound.color(selectedBoxColor)
    categoryFound.begin_fill()
    categoryFound.forward(460)
    categoryFound.right(90)
    categoryFound.forward(240)
    categoryFound.right(90)
    categoryFound.forward(460)
    categoryFound.right(90)
    categoryFound.forward(240)
    categoryFound.right(90)
    categoryFound.end_fill()
    categoryFound.penup() 

    x = 0
    y = 60
    categoryFound.goto(x, y)
    categoryFound.pendown()
    categoryFound.color(selectedTextColor)
    
    text = "Categories Found: "
    categoryFound.write(text, False, align = 'center', font = (FONT, 16, "normal"))
    categoryFound.penup()

    x -= 150
    y-= 40

    # for i in range(len(categories)):
    #     if(categories[i] == ""):
    #         categories.pop(i)

    for i in categories:
        text = i

        y -= 30
        categoryFound.goto(x, y)
        categoryFound.pendown()
        categoryFound.write(text, False, align = 'left', font = (FONT, 16, "normal"))
        categoryFound.penup()

# Latest category found is shown above the mistakes remaining box
def showCategory(categories):
    global displayCategories
    global boxColor
    global textColor

    displayCategories.clear()

    x = -230
    y = -200
    textX = -60
    textY = -242
    
    temp = []
    for i in range(len(categories)):
        if(categories[i] == ""):
            temp.append(i)
    for i in temp:
        categories.remove("")
    
    for i in categories:

        displayCategories.penup()
        displayCategories.goto(x, y)

        displayCategories.pendown()
        displayCategories.color(boxColor)
        displayCategories.begin_fill()
        displayCategories.forward(340)
        displayCategories.right(90)
        displayCategories.forward(30)
        displayCategories.right(90)
        displayCategories.forward(340)
        displayCategories.right(90)
        displayCategories.forward(30)
        displayCategories.right(90)
        displayCategories.end_fill()
        displayCategories.penup()

        displayCategories.goto((textX, textY))
        displayCategories.pendown()
        displayCategories.color(textColor)

        text = i.upper()
        displayCategories.write(text, False, align = 'center', font = (FONT, FONTSIZE, "normal"))
        displayCategories.penup()

        y += 40
        textY += 40

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    # Here is a screen object to use
    s = turtle.Screen()
    s.bgcolor("black")
    s.tracer(False)
    s.title("Connections")

    fileNum = input("Enter a number (0 - 6): ")

    if(0 <= int(fileNum) <= 6):
        filename = "Day" + fileNum + ".txt"
    else:
        print("Number out of range")
        print("Loading default board")
        filename = "Day0.txt"

    words, solution = readFile(filename)
    boxes = createTurtleList(boxCount)
    coordinates = getCoordinates()
    shuffledWords = shuffleWords(words)
    
    drawTitle()
    drawBox(boxes, coordinates)
    writeText(shuffledWords, boxes, coordinates)

    selectBoxChoiceList = selectBoxChoiceList()
    drawSubmitButton(boxColor, textColor)
    drawMistakes()
    s.onclick(selectUnselectBox)    
    
    turtle.mainloop() # If this is removed, the graphics window will close and you won't see your graphics