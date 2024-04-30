# In a file called main.py, implement a program that reads and prints the sequence files. 
# The program should have one or two input prompts, depending on the first input provided by the user. 
# If the input is small.txt, your program should open the DNA sequence files 1-4 and print their contents one by one. 
# If the input is large.txt, your program should open the DNA sequence file based on the second integer input and print its contents.

fileSize = input()

if(fileSize == "large"):
    filename = input()
    filename = filename + ".txt"

    file = open(filename)
    print(file.readline())
    file.close()
else:
    for i in range(1,5):
        filename = str(i) + ".txt"

        file = open(filename)
        print(file.readline(), end = "")
        file.close()