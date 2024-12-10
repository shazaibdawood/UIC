file = open("shippingRatesAndTimes.csv")

shippingList = file.readlines()
shippingList.pop(0)
file.close()

# Abbreviation - two-letter state code
# State - state name
# Standard Delivery Base Rate - base cost for method
# Standard Delivery Estimated Days - estimated number of days (after checkout) to deliver
# Overnight Delivery Base Rate - base cost for method
# Overnight Delivery Estimated Days - estimated number of days (after checkout) to deliver

shippingCost = {}
for i in range(len(shippingList)):
    tempList = shippingList[i].split(",")

    key = tempList[0]
    tempList.pop(0)

    stateName = tempList[0]
    tempList.pop(0)

    for i in range(len(tempList)):
        tempList[i] = int(tempList[i])

    valuesList = [stateName]
    valuesList.extend(tempList)



    shippingCost[key] = valuesList

# Testing

for i in shippingCost:
    print(i, shippingCost[i])

testingComplete = True