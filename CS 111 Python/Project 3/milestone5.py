import driver # you need to this call draw_panel -- do not remove

import math

file = open("districts.txt")
list = file.readlines()
districts = {}

# split list of districts into a disctionary of lists
for i in range(50):
    temp = list[i].split(",")
    key = temp[0]
    temp.pop(0)

    string = temp[-1]
    # remove newline from last element
    last = ""
    for i in range(len(string) - 1):
        last += string[i]
    temp[-1] = last
    
    districts[key] = temp

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

# void function
# takes user entered state as input
def voteCalc(state):
    districtInfo = districts[state]
    districtNum = 0
    list_of_tuples = [] # empty list

    wastedDVotes = 0
    wastedRVotes = 0

    totalVotes = 0

    # district numbers are evry 3 elements
    # 2 elements after district number are democratic and republican votes in order
    for i in range(0, len(districts[state]) - 1, 3):
        districtNum += 1

        dVotes = int(districtInfo[i + 1])
        rVotes = int(districtInfo[i + 2])
        districtVotes = dVotes + rVotes

        winVoteNum = round(((districtVotes / 2) + 1))

        if(dVotes > rVotes):
            winPercent = round((dVotes / districtVotes) * 100)
            losePercent = 100 - winPercent
            winString = ("D" * winPercent)
            loseString = ("R" * losePercent)

            displayString = winString + loseString
            percentTuple = (winPercent, losePercent)
            list_of_tuples.append(percentTuple)

            wastedRVotes += rVotes
            wastedDVotes += (dVotes - winVoteNum)

        elif(rVotes > dVotes):
            winPercent = round((rVotes / districtVotes) * 100)
            winString = ("R" * winPercent)
            losePercent = 100 - winPercent
            loseString = ("D" * losePercent)

            displayString = loseString + winString
            percentTuple = (losePercent, winPercent)
            list_of_tuples.append(percentTuple)

            wastedDVotes += dVotes
            wastedRVotes += (rVotes - winVoteNum)
        elif(districtVotes == 0):
            displayString = ""

        totalVotes += districtVotes

        print("District", (districtNum), end = "")
        print(":", displayString)

    eGap = math.fabs((wastedDVotes - wastedRVotes) / totalVotes)
    eGap = round(eGap * 100, 2)


    print()
    if(eGap < 7 or districtNum <= 3):
        print("Gerrymandered? No")
    else:
        print("Gerrymandered? Yes")

        if(wastedDVotes > wastedRVotes):
            print("Gerrymandered against: Democrats")
        else:
            print("Gerrymandered against: Republicans")

        print("Efficiency Factor:", eGap, end = "")
        print("%")

    print()
    print("Wasted Democratic votes:", wastedDVotes)
    print("Wasted Republican votes:", wastedRVotes)

    eligibleVoters = [state, str(voterCount[state])]
    driver.draw_panel(eligibleVoters, list_of_tuples, districtNum)

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
    voteCalc(state)
    print("Eligible voters:", voterCount[state])