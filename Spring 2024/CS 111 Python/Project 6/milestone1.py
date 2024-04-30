FONTSIZE = 12

# -function name is meaningful
# -when called, it draws one "box" (this can be a square, rounded square, or any other shape you choose) 
# -the turtle that draws the box is created outside of the function and then sent in as an argument
# -the function has parameters for location of the box, size of the box, and color of the box.
# -the function can write text centered inside the box.

import turtle
import math
import random

def drawTextBox(box, location, width, height, boxColor, text, textColor):
    x = location[0]
    y = location[1]

    box.goto(x - (width / 2), y - (height / 2))

    box.color(boxColor)
    box.begin_fill()
    box.pendown()
    box.forward(width)
    box.left(90)
    box.forward(height)
    box.left(90)
    box.forward(width)
    box.left(90)
    box.forward(height)
    box.left(90)
    box.end_fill()
    box.penup()

    box.goto(x, y)
    box.pendown()
    box.color(textColor)
    box.write(text, False, align = 'center', font = ("Arial", 12, "normal"))
    box.penup()

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    # Here is a screen object to use
    s = turtle.getscreen()

    # Here is a turtle object to use to draw the box
    # You should create the turtle object outside of your function (like this)
    # and send the box turtle in as an argument
    box = turtle.Turtle()
    box.hideturtle()
    box.penup()

    drawTextBox(box, [100, 100], 200, 100, "red", "Project 6", "grey")
    drawTextBox(box, [200, -100], 250, 150, "darkblue", "Project 6", "grey")
    drawTextBox(box, [-200, -200], 200, 100, "purple", "Project 6", "grey")


    # turtle.mainloop() # If this is removed, the graphics window will close and you won't see your graphics
