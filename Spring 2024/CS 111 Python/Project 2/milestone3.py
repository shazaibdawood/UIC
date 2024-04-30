# user name rules:
# Must be exactly 8 characters
# Must start with a letter

# number input rules
# The input is an integer
# The input is an integer between 0 and 99 exclusive

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

print("Connections")
print("Group words that share a common thread.")

userName = input("Enter your username: ")

if(len(userName) != 8):
    userName = input("\nUsername must be 8 characters, please try again: ")
elif(not userName[0].isalpha()):
    userName = input("\nUsername must start with a letter, please try again: ")

start = True

if(len(userName) != 8 or (not userName[0].isalpha())):
    print("\nGoodbye.")
    start = False

if(start):
    print("\nWelcome,", userName, end = "")
    print("!")

    enter = input("Press enter to start: ")

    num = (input("\nEnter number (0-99): "))

    filename = "Day" + num + ".txt"
    import os

    if(not num.isnumeric() or int(num) < 0 or int(num) > 99):
        num = (input("\nEnter number (0-99), please try again: "))
        filename = "Day" + num + ".txt"
        if(not num.isnumeric() or int(num) < 0 or int(num) > 99 or not os.path.exists(filename)):
            print("\nSorry, that board is unavailable, setting up the default board.")
            gameboard, solution = readFile("Day0.txt")
            shuffle(gameboard)
        else:
            gameboard, solution = readFile(filename)
            shuffle(gameboard)
    elif(not os.path.exists(filename)):
        print("\nSorry, that board is unavailable, setting up the default board.")
        gameboard, solution = readFile("Day0.txt")
        shuffle(gameboard)
    else:
        gameboard, solution = readFile(filename)
        shuffle(gameboard)

    print("\nCreate four groups of four!")

    print("|", "{:10}".format(gameboard[0]).upper(), "|", "{:10}".format(gameboard[1]).upper(), "|", "{:10}".format(gameboard[2]).upper(), "|", "{:10}".format(gameboard[3]).upper(), "|")
    print("|", "{:10}".format(gameboard[4]).upper(), "|", "{:10}".format(gameboard[5]).upper(), "|", "{:10}".format(gameboard[6]).upper(), "|", "{:10}".format(gameboard[7]).upper(), "|")
    print("|", "{:10}".format(gameboard[8]).upper(), "|", "{:10}".format(gameboard[9]).upper(), "|", "{:10}".format(gameboard[10]).upper(), "|", "{:10}".format(gameboard[11]).upper(), "|")
    print("|", "{:10}".format(gameboard[12]).upper(), "|", "{:10}".format(gameboard[13]).upper(), "|", "{:10}".format(gameboard[14]).upper(), "|", "{:10}".format(gameboard[15]).upper(), "|")
    
    word1 = ""
    word2 = ""
    word3 = ""
    word4 = ""

    usedWords = set([])   
    
    word1 = input("\nEnter first word: ").strip().lower()
    if(not word1 in gameboard):
        word1 = input("\nNot a valid game board word, try again: ").strip().lower()
        if(not word1 in gameboard):
            print("\nGoodbye.")
            start = False
        else: 
            usedWords.add(word1)
            word2 = input("\nEnter second word: ").strip().lower()
    else:
        usedWords.add(word1)
        word2 = input("\nEnter second word: ").strip().lower()

    if(start and (not word2 in gameboard or word2 == "" or word2 in usedWords)):
        word2 = input("\nNot a valid game board word, try again: ").strip().lower()
        if(not word2 in gameboard or word2 == "" or word2 in usedWords):
            print("\nGoodbye.")
            start = False
        else:
            usedWords.add(word2)
            word3 = input("\nEnter third word: ").strip().lower()
    elif(start and word2 in gameboard):
        usedWords.add(word2)
        word3 = input("\nEnter third word: ").strip().lower()

    if(start and (not word3 in gameboard or word3 == "" or word3 in usedWords)):
        word3 = input("\nNot a valid game board word, try again: ").strip().lower()
        if(not word3 in gameboard or word3 == "" or word3 in usedWords):
            print("\nGoodbye.")
            start = False
        else: 
            usedWords.add(word3)
            word4 = input("\nEnter fourth word: ").strip().lower()
    elif(start and word3 in gameboard):
        usedWords.add(word3)
        word4 = input("\nEnter fourth word: ").strip().lower()

    if(start and (not word4 in gameboard or word4 == "" or word4 in usedWords)):
        word4 = input("\nNot a valid game board word, try again: ").strip().lower()
        if(not word4 in gameboard or word4 == "" or word4 in usedWords):
            print("\nGoodbye.")
            start = False
        else: 
            usedWords.add(word4)
            print("\nChecking solution.")
    elif(start and word4 in gameboard):
        usedWords.add(word4)
        print("\nChecking solution.")