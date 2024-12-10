# Opening file
# checking if entered state is a state
# display voter count

file = open("eligible_voters.txt")
list = file.readlines()
voterCount = {}

for i in list:
    temp = i.split(",")
    key = temp[0]

    string = temp[-1]
    last = ""
    for i in range(len(string) - 1):
        last += string[i]
    temp[-1] = last

    voterCount[key] = int(temp[-1])

print("This program allows you to search through")
print("data about congressional voting districts")
print("and determine whether a particular state is") 
print("gerrymandered.")
print()

state = (input("Which state do you want to look up? ")).title()
print()
if(not state in voterCount):
    print(state, "not found.")
else:
    print("Eligible voters:", voterCount[state])