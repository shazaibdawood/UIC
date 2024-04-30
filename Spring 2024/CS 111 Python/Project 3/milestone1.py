# Opening file
# checking if entered state is a state
# display districts info

file = open("districts.txt")
list = file.readlines()
districts = {}

for i in range(50):
    temp = list[i].split(",")
    key = temp[0]
    temp.pop(0)

    string = temp[-1]
    last = ""
    for i in range(len(string) - 1):
        last += string[i]
    temp[-1] = last
    
    districts[key] = temp

print("This program allows you to search through")
print("data about congressional voting districts")
print("and determine whether a particular state is") 
print("gerrymandered.")
print()

state = (input("Which state do you want to look up? ")).title()
print()
if(not state in districts):
    print(state, "not found.")
else:
    print("Districts info:", districts[state])