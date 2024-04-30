# Final Project
# CS 111, Hayes & Reckinger
# TODO: Comment here

import turtle
import random
import pygame

player1 = turtle.Turtle()
player1.penup()
player1.goto(100, 100)
player1.hideturtle()
player1.color("white")

player2 = turtle.Turtle()
player2.shape("turtle")
player2.penup()
player2.hideturtle()
player2.color("white")

turtle.addshape("c.gif")
turtle.addshape("python.gif")

player1.shape("c.gif")
player2.shape("python.gif")

writeNames = turtle.Turtle()
writeNames.hideturtle()

levelCreator = turtle.Turtle()
levelCreator.hideturtle()
levelCreator.width(5)

timer = turtle.Turtle()
timer.hideturtle()

pygame.init()

pygame.mixer.music.load("backgroundMusic.wav")
pygame.mixer.music.play(5)

# Constants

STARTGAME = False
GAMEOVER = False
playerNames = []
level1 = False
level2 = False
hunterSelected = False
fugitiveSelected = False
p1L1Score = 0
p1L2Score = 0
p2L1Score = 0
p2L2Score = 0
COUNTER = 0
p1TotalScore = 0
p2TotalScore = 0

def drawStartScreen():
    global STARTGAME

    s.bgpic("startScreen.png")
    s.tracer(True)

    fugitive = turtle.Turtle()
    fugitive.penup()
    fugitive.shape("turtle")
    fugitive.color("yellow")
    fugitive.hideturtle()

    hunter = turtle.Turtle()
    hunter.penup()
    hunter.color("yellow")
    hunter.hideturtle()
    
    fugitive.goto(-150, 160)
    fugitive.showturtle()
    hunter.goto(-165, 160)
    hunter.showturtle()

    while(not STARTGAME):
        startScreenAnimation(fugitive, hunter)
    
    p1Name, p2Name = getPlayerNames()
    playerNames.append(p1Name)
    playerNames.append(p2Name)

    fugitive.hideturtle()
    hunter.hideturtle()

    drawPlayerSelectionScreen()
    
def drawGameOverScreen():
    global player1
    global player2
    global playerNames
    global writeNames
    global levelCreator
    global timer

    timer.clear()

    player1.hideturtle()
    player2.hideturtle()
    levelCreator.clear()

    s.tracer(False)
    if(p1TotalScore > p2TotalScore):
        s.bgpic("hunterWins.png")
    elif(p2TotalScore > p1TotalScore):
        s.bgpic("fugitiveWins.png")
    else:
        s.bgpic("gameOverScreen.png")

    highscoreList = [p1TotalScore,p2TotalScore]

    file = open("highscores.txt", "a")
    file.write(str(highscoreList) + "\n")
    file.close()

    file = open("highscores.txt")
    p1Highscore = 0
    p2Highscore = 0
    scoresList = file.readlines()
    file.close()
    for i in scoresList:
        scores = list(i)
        scores.pop(0)
        scores.pop(-1)
        scores.pop(-1)

        highscores = ""
        for j in scores:
            highscores += j
        highscores = highscores.split(", ")
        if(int(highscores[0]) > p1Highscore):
            p1Highscore = int(highscores[0])
        if(int(highscores[1]) > p2Highscore):
            p2Highscore = int(highscores[1])

    writeNames.color("yellow")
    writeNames.penup()
    writeNames.goto(-185, 200)
    writeNames.pendown()
    writeNames.write(str(p1TotalScore).upper(), False, align = "center", font = ("Verdana", 12, "bold"))
    writeNames.penup()
    writeNames.goto(185, 200)
    writeNames.pendown()
    writeNames.write(str(p2TotalScore).upper(), False, align = "center", font = ("Verdana", 12, "bold"))
    writeNames.penup()

    writeNames.color("yellow")
    writeNames.penup()
    writeNames.goto(-125, -220)
    writeNames.pendown()
    writeNames.write("HUNTER HIGHSCORE: " + str(p1Highscore).upper(), False, align = "center", font = ("Verdana", 10, "bold"))
    writeNames.penup()
    writeNames.goto(125, -220)
    writeNames.pendown()
    writeNames.write("FUGITIVE HIGHSCORE: " + str(p2Highscore).upper(), False, align = "center", font = ("Verdana", 10, "bold"))
    writeNames.penup()

    playerNames.clear()

    turtle.ontimer(s.bye, 5000)

def drawLevels():
    global levelCreator
    global player1
    global player2
    global level1
    global level2

    s.tracer(False)

    if(level1):
        s.bgpic("blankBackground.png")
        levelCreator.penup()
        levelCreator.goto(-210,210)
        levelCreator.color("white")
        levelCreator.pendown()
        levelCreator.forward(420)
        levelCreator.right(90)
        levelCreator.forward(420)
        levelCreator.right(90)
        levelCreator.forward(420)
        levelCreator.right(90)
        levelCreator.forward(420)
        levelCreator.right(90)
        levelCreator.penup()
    elif(level2):
        levelCreator.clear()

        s.bgpic("blankBackground.png")
        levelCreator.penup()
        levelCreator.color("royalblue")
        levelCreator.goto(-65, 210)
        levelCreator.setheading(270)
        levelCreator.pendown()
        levelCreator.forward(150)
        levelCreator.penup()

        levelCreator.color("magenta")
        levelCreator.goto(-170, -60)
        levelCreator.pendown()
        levelCreator.setheading(90)
        levelCreator.forward(30)
        levelCreator.setheading(0)
        levelCreator.forward(180)
        levelCreator.setheading(270)
        levelCreator.forward(30)
        levelCreator.penup()

        levelCreator.goto(-170, -100)
        levelCreator.pendown()
        levelCreator.setheading(270)
        levelCreator.forward(30)
        levelCreator.setheading(0)
        levelCreator.forward(180)
        levelCreator.setheading(90)
        levelCreator.forward(30)
        levelCreator.penup()

        levelCreator.color("cyan")
        levelCreator.goto(135, -170)
        levelCreator.setheading(90)
        levelCreator.pendown()
        levelCreator.forward(190)
        levelCreator.penup()

        levelCreator.goto(10, 160)
        levelCreator.setheading(270)
        levelCreator.pendown()
        levelCreator.forward(100)
        levelCreator.setheading(0)
        levelCreator.forward(80)
        levelCreator.penup()

        levelCreator.goto(-210,210)
        levelCreator.color("white")
        levelCreator.pendown()
        levelCreator.forward(420)
        levelCreator.right(90)
        levelCreator.forward(420)
        levelCreator.right(90)
        levelCreator.forward(420)
        levelCreator.right(90)
        levelCreator.forward(420)
        levelCreator.right(90)
        levelCreator.penup()

def startScreenAnimation(fugitive, hunter):
    global STARTGAME

    # fugitive.shapesize(0.75, 0.75, 1)
    # hunter.shapesize(0.75, 0.75, 1)

    while(-165 <= fugitive.xcor() <= 150 and fugitive.ycor() <= 160 and not STARTGAME):
        x = fugitive.xcor()
        y = fugitive.ycor()

        fugitive.goto(x + 15, y)

        hunter.setheading(0)
        hunter.goto(x, y)
    if(not STARTGAME):
        fugitive.setheading(270)

    while(fugitive.xcor() == 165 and 115 <= fugitive.ycor() <= 160 and not STARTGAME):
        x = fugitive.xcor()
        y = fugitive.ycor()

        fugitive.goto(x, y - 15)

        hunter.setheading(270)
        hunter.goto(x, y)
    if(not STARTGAME):
        fugitive.setheading(0)

    while(165 <= fugitive.xcor() <= 225 and fugitive.ycor() == 100 and not STARTGAME):
        x = fugitive.xcor()
        y = fugitive.ycor()

        fugitive.goto(x + 15, y)

        hunter.setheading(0)
        hunter.goto(x, y)
    if(not STARTGAME):
        fugitive.setheading(270)
    
    while(fugitive.xcor() == 240 and -5 <= fugitive.ycor() <= 100 and not STARTGAME):
        x = fugitive.xcor()
        y = fugitive.ycor()

        fugitive.goto(x, y - 15)

        hunter.setheading(270)
        hunter.goto(x, y)
    if(not STARTGAME):
        fugitive.setheading(180)

    while(-225 <= fugitive.xcor() <= 240 and fugitive.ycor() == -20 and not STARTGAME):
        x = fugitive.xcor()
        y = fugitive.ycor()

        fugitive.goto(x - 15, y)

        hunter.setheading(180)
        hunter.goto(x, y)
    if(not STARTGAME):
        fugitive.setheading(90)

    while(fugitive.xcor() == -240 and -20 <= fugitive.ycor() <= 85 and not STARTGAME):
        x = fugitive.xcor()
        y = fugitive.ycor()

        fugitive.goto(x, y + 15)

        hunter.setheading(90)
        hunter.goto(x, y)
    if(not STARTGAME):
        fugitive.setheading(0)

    while(-240 <= fugitive.xcor() <= -180 and fugitive.ycor() == 100 and not STARTGAME):
        x = fugitive.xcor()
        y = fugitive.ycor()

        fugitive.goto(x + 15, y)

        hunter.setheading(0)
        hunter.goto(x, y)
    if(not STARTGAME):
        fugitive.setheading(90)
    
    while(fugitive.xcor() == -165 and 100 <= fugitive.ycor() <= 135 and not STARTGAME):
        x = fugitive.xcor()
        y = fugitive.ycor()

        fugitive.goto(x, y + 15)

        hunter.setheading(90)
        hunter.goto(x, y)
    if(not STARTGAME):
        fugitive.setheading(0)

def drawPlayerSelectionScreen():
    global hunterSelected
    global writeNames

    s.bgpic("hunterSelect.png")

    writeNames.color("yellow")
    writeNames.penup()
    writeNames.goto(-185, 216)
    writeNames.pendown()
    writeNames.write(playerNames[0].upper(), False, align = "center", font = ("Verdana", 12, "bold"))
    writeNames.penup()
    writeNames.goto(185, 216)
    writeNames.pendown()
    writeNames.write(playerNames[1].upper(), False, align = "center", font = ("Verdana", 12, "bold"))
    writeNames.penup()

def playGame():
    global player1
    global player2
    global GAMEOVER
    global COUNTER

    s.tracer(True)
    GAMEOVER = False

    player1.hideturtle()
    player2.hideturtle()
    player1.goto(random.randint(-200, 0), random.randint(-200, 200))
    player1.shapesize(3, 3, 1)
    player2.goto(random.randint(0, 200), random.randint(-200, 200))
    player2.shapesize(3, 3, 1)

    player1.showturtle()
    player2.showturtle()

    drawLevels()
    COUNTER = 0
    addScore()

    s.listen()
    s.onkey(p1Up, "Up")
    s.onkey(p1Right, "Right")
    s.onkey(p1Down, "Down")
    s.onkey(p1Left, "Left")

    s.onkey(p2Up, "w")
    s.onkey(p2Right, "d")
    s.onkey(p2Down, "s")
    s.onkey(p2Left, "a")
        
def chooseOption(x, y):
    global STARTGAME
    global GAMEOVER
    global player1
    global player2
    global writeNames
    global hunterSelected
    global level1

    if(-100 <= x <= 100 and -70 <= y <= -25 and not STARTGAME):
        STARTGAME = True
        GAMEOVER = False
    elif(-100 <= x <= 100 and -70 <= y <= -25 and GAMEOVER):
        STARTGAME = False
        hunterSelected = False
        writeNames.clear()
        writeNames.hideturtle()
        drawStartScreen()

    if(-135 <= x <= -60 and -100 <= y <= -25 and not hunterSelected):
        hunterSelected = True
        player1.shape("c.gif")
        player2.shape("python.gif")
        level1 = True
        playGame()
    elif(60 <= x <= 135 and -100 <= y <= -25 and not hunterSelected):
        hunterSelected = True
        player1.shape("python.gif")
        player2.shape("c.gif")
        level1 = True
        playGame()

def getPlayerNames():
    s.bgpic("playerNameSelection.png")
    print("Enter Username for Player 1  (Between 6 - 10 characters): ")
    p1Name = input()
    print()
    if(not 6 <= len(p1Name) <= 10):
        print("Entered username violates character limits")
        p1Name = input("Enter Username for Player 1  (Between 6 - 10 characters): ")
        print()
        if(not 6 <= len(p1Name) <= 10):
            p1Name = "Player1"
            print("Username did not meet requirements. Player1 will be displayed")

    p2Name = input("Enter Username for Player 2  (Between 6 - 10 characters): ")
    print()
    if(not 6 <= len(p2Name) <= 10):
        print("Entered username violates character limits")
        p2Name = input("Enter Username for Player 2  (Between 6 - 10 characters): ")
        print()
        if(not 6 <= len(p2Name) <= 10):
            p2Name = "Player2"
            print("Username did not meet requirements. Player2 will be displayed")
    print("Hunter Name -", p1Name)
    print("Fugitive Name -", p2Name)
    print("Please return to turtle window")

    return p1Name, p2Name

# Player movement functions

def p1Up():
    global player1
    global GAMEOVER
    global level1
    global level2

    if(not GAMEOVER):
        s.tracer(True)
        player1.setheading(90)

        x = player1.xcor()
        y = player1.ycor()

        if(y <= 185 and level1):
            player1.forward(10)
        elif(level2):
            if(y <= 185 and not(-170 <= x <= 15 and -45 <= y < -30) and not(-170 <= x <= 15 and -145 <= y < -130) and not(10 <= x <= 95 and 45 <= y < 60)):
                player1.forward(10)

        checkPosition()

def p2Up():
    global player2
    global GAMEOVER
    global level1
    global level2

    if(not GAMEOVER):
        s.tracer(True)
        player2.setheading(90)

        x = player2.xcor()
        y = player2.ycor()

        if(y <= 185 and level1):
            player2.forward(10)
        elif(level2):
            if(y <= 185 and not(-170 <= x <= 15 and -45 <= y <= -15) and not(-170 <= x <= 15 and -145 <= y <= -115) and not(10 <= x <= 95 and 45 <= y <= 75)):
                player2.forward(10)

        checkPosition()

def p1Down():
    global player1
    global GAMEOVER
    global level1
    global level2

    if(not GAMEOVER):
        s.tracer(True)
        player1.setheading(270)

        x = player1.xcor()
        y = player1.ycor()

        if(y >= -185 and level1):
            player1.forward(10)
        elif(level2):
            if(y >= -185 and not(-170 <= x <= 15 and -30 < y <= -15) and not(-170 <= x <= 15 and -130 < y <= -115) and not(10 <= x <= 95 and 60 < y <= 75)):
                player1.forward(10)

        checkPosition()

def p2Down():
    global player2
    global GAMEOVER
    global level1
    global level2

    if(not GAMEOVER):
        s.tracer(True)
        player2.setheading(270)

        x = player2.xcor()
        y = player2.ycor()

        if(y >= -185 and level1):
            player2.forward(10)
        elif(level2):
            if(y >= -185 and not(-170 <= x <= 15 and -30 < y <= -15) and not(-170 <= x <= 15 and -130 < y <= -115) and not(10 <= x <= 95 and 60 < y <= 75)):
                player2.forward(10)

        checkPosition()

def p1Right():
    global player1
    global GAMEOVER
    global level1
    global level2

    if(not GAMEOVER):
        s.tracer(True)
        player1.setheading(0)

        x = player1.xcor()
        y = player1.ycor()

        if(x <= 185 and level1):
            player1.forward(10)
        elif(level2):
            if(x <= 185 and not(-80 <= x < -65 and 60 <= y <= 210) and not(-5 <= x < 10 and 60 <= y <= 160) and not(120 <= x < 135 and -170 <= y <= 20) and not(-180 <= x < -170 and -60 <= y <= -30) and not(-5 <= x < 10 and -60 <= y <= -30) and not(-180 <= x < -170 and -125 <= y <= -100) and not(-5 <= x < 10 and -125 <= y <= -100)):
                player1.forward(10)

        checkPosition()

def p2Right():
    global player2
    global GAMEOVER
    global level1
    global level2

    if(not GAMEOVER):
        s.tracer(True)
        player2.setheading(0)

        x = player2.xcor()
        y = player2.ycor()

        if(x <= 185 and level1):
            player2.forward(10)
        elif(level2):
           if(x <= 185 and not(-80 <= x < -65 and 60 <= y <= 210) and not(-5 <= x < 10 and 60 <= y <= 160) and not(120 <= x < 135 and -170 <= y <= 20) and not(-180 <= x < -170 and -60 <= y <= -30) and not(-5 <= x < 10 and -60 <= y <= -30) and not(-180 <= x < -170 and -125 <= y <= -100) and not(-5 <= x < 10 and -125 <= y <= -100)):
                player2.forward(10)

        checkPosition()

def p1Left():
    global player1
    global GAMEOVER
    global level1
    global level2

    if(not GAMEOVER):
        s.tracer(True)
        player1.setheading(180)

        x = player1.xcor()
        y = player1.ycor()

        if(x >= -185 and level1):
            player1.forward(10)
        elif(level2):
            if(x >= -185 and not(-65 < x <= -50 and 60 <= y <= 210) and not(10 < x <= 25 and 60 <= y <= 160) and not(135 < x <= 150 and -170 <= y <= 20) and not(-170 < x <= -155 and -60 <= y <= -30) and not(10 < x <= 25 and -60 <= y <= -30) and not(-170 < x <= -155 and -125 <= y <= -100) and not(10 < x <= 25 and -125 <= y <= -100)):
                player1.forward(10)

        checkPosition()

def p2Left():
    global player2
    global GAMEOVER
    global level1
    global level2

    if(not GAMEOVER):
        s.tracer(True)
        player2.setheading(180)

        x = player2.xcor()
        y = player2.ycor()

        if(x >= -185 and level1):
            player2.forward(10)
        elif(level2):
            if(x >= -185 and not(-65 < x <= -50 and 60 <= y <= 210) and not(10 < x <= 25 and 60 <= y <= 160) and not(135 < x <= 150 and -170 <= y <= 20) and not(-170 < x <= -155 and -60 <= y <= -30) and not(10 < x <= 25 and -60 <= y <= -30) and not(-170 < x <= -155 and -125 <= y <= -100) and not(10 < x <= 25 and -125 <= y <= -100)):
                player2.forward(10)

        checkPosition()

def checkPosition():
    global player1
    global player2
    global GAMEOVER
    global STARTGAME
    global level1
    global level2
    global COUNTER
    global timer
    global p1L1Score
    global p1L2Score
    global p2L1Score
    global p2L2Score
    global p1TotalScore
    global p2TotalScore

    if(player1.distance(player2.xcor(), player2.ycor()) <= 25 or COUNTER >= 30):
        if(level1):
            level1 = False
            level2 = True
            GAMEOVER = True
            p2L1Score = COUNTER
            p1L1Score = 30 - COUNTER
            COUNTER = 30
            turtle.ontimer(playGame, 2000)
        elif(level2):
            level2 = False
            GAMEOVER = True
            timer.clear()
            p2L2Score = COUNTER
            p1L2Score = 30 - COUNTER
            COUNTER = 30

            p1TotalScore = p1L1Score + p1L2Score
            p2TotalScore = p2L1Score + p2L2Score
            turtle.ontimer(drawGameOverScreen, 2000)
            
# Timer runs on a recursive function
# It calls itself every second and updates the counter variable
def addScore():
    global COUNTER
    global timer
    global GAMEOVER

    if(COUNTER < 30):
        COUNTER += 1

        timer.clear()
        timer.hideturtle()
        timer.color("yellow")
        timer.penup()
        timer.goto(-185, -236)
        timer.pendown()
        timer.write(str(COUNTER).upper(), False, align = "center", font = ("Verdana", 12, "bold"))

        s.ontimer(addScore, 1000) 
    else:
        timer.clear()   

s = turtle.Screen()
s.title("Python Pursuit")
s.setup(500, 500)
s.tracer(False)

s.listen()

s.onclick(chooseOption)
drawStartScreen()

s.mainloop() # If this is removed, the graphics window will close and you won't see your graphics