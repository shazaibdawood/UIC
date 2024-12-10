# Starter code for MS 3 - Do not edit/remove anything provided here.

import random

# This function will shuffle your word list, which can be used to shuffle board.
# INPUTS:
# list - passed by assignment, which means it does not need to be returned.
# When the list is passed in, changes made to the list will persist outside
# of the function.
def shuffle(list):
    random.seed(10)
    n = len(list)
    new_list = []
    while len(list) != 0: # randomly select words until list is empty
        ind = random.randint(0, len(list) - 1)
        new_list.append(list[ind])
        list.pop(ind) # remove from original list
    for i in range(n): # since passed by assignment, we must update list
        list.append(new_list.pop())

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


# TODO:  Write out a file header comment, header comment should go above provided code but do not edit/remove anything above this line

print("Connections")
print("Group words that share a common thread.")
name = input("Enter your name: ")
print("\nWelcome,", name, end = "")
print("!")
enter = input("Press enter to start: ")


user_number = input("\nEnter number (0-99): ")
print()
filename = "Day" + user_number + ".txt"

gameboard, solution = readFile(filename)
shuffle(gameboard)
print("\nCreate four groups of four!")

print("|", "{:10}".format(gameboard[0]).upper(), "|", "{:10}".format(gameboard[1]).upper(), "|", "{:10}".format(gameboard[2]).upper(), "|", "{:10}".format(gameboard[3]).upper(), "|")
print("|", "{:10}".format(gameboard[4]).upper(), "|", "{:10}".format(gameboard[5]).upper(), "|", "{:10}".format(gameboard[6]).upper(), "|", "{:10}".format(gameboard[7]).upper(), "|")
print("|", "{:10}".format(gameboard[8]).upper(), "|", "{:10}".format(gameboard[9]).upper(), "|", "{:10}".format(gameboard[10]).upper(), "|", "{:10}".format(gameboard[11]).upper(), "|")
print("|", "{:10}".format(gameboard[12]).upper(), "|", "{:10}".format(gameboard[13]).upper(), "|", "{:10}".format(gameboard[14]).upper(), "|", "{:10}".format(gameboard[15]).upper(), "|")
