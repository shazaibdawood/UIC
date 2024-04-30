testProducts = {
    "ABC": {
        "categories": ["food", "electronics"],
        "name": "laptop",
        "weight": 5.0,
        "price": 650.00,
	    "currency" : "USD",
        "notes": "lots of features"
    },
    "DEF": {
        "categories": ["electronics"],
        "name": "TV",
        "weight": 15.0,
        "price": 550.00,
	    "currency" : "USD",
        "notes": "lots of features"
    }
}

def getProductsBySearch (products, searchTerm):
    # searches name and notes for presence of searchTerm
    # search is case-insensitive
    # returns a list of product codes, or an empty list
    
    productCodes = []

    for i in products:
        if((searchTerm).upper() in (products[i]["name"]).upper() or (searchTerm).upper() in (products[i]["notes"]).upper()):
            productCodes.append(i)
        
    return productCodes

def getProductsByCategory(products, categoryName):
    # returns a list of product codes for the category name, or an empty list
    
    productCodes = []

    for i in products:
        if(categoryName in products[i]["categories"]):
            productCodes.append(i)
    
    return productCodes


def getProductCategories(products):
    # returns a list of category names, sorted 

    categories = []
    
    for i in products:
        #print(products[i])
        for j in products[i]:
            #print(products[i][j])
            if(j == "categories"):
                for k in products[i][j]:
                    categories.append(k)
    categories.sort()
    return categories

def getProductPrice (products, productCode):
    # return price in USD as float
    
    price = products[productCode]["price"]

    return price

def getProductWeight (products, productCode):
    # return weight as float
    
    weight = products[productCode]["weight"]

    return weight


cart = {
    "products": {},
    "productsTotalCost": 0.00,
    "productsTotalWeight": 0.00,
    "deliveryState": "",
"taxAmount": 0.00, 
    "deliveryMethod": "",   
    "deliveryCost": 0.00,
	"deliveryDaysEstimate": 0,
	"cartTotal": 0.00
}

# products
# dictionary of productCode:quantity pairs, e.g. {"ABC":5, "DEF":3}

# productsTotalCost
# total of product prices * quantity (USD)

# productsTotalWeight
# total of product weights * quantity

# deliveryState
# two-letter state code for delivery

# taxAmount
# taxes for this cart, based on deliveryState (USD)

# deliveryMethod
# name of delivery method (e.g., overnight)

# deliveryCost
# amount of delivery charges based on method and state (USD)

# deliveryDaysEstimate
# estimated number of days until items are delivered

# cartTotal
# productsTotalCost + taxAmount + deliveryCost  (USD)

def setCartItemQuantity(cart, productCode, quantity):
	# update cart products dictionary
	# quantity is the new quantity, not the change in quantity
	# quantity value <= 0 should remove productCode from dictionary
	# productsTotalCost, productsTotalWeight, cartTotal are set to 0
	# returns count of productCodes in the cart

    if(quantity <= 0):
        cart["products"].remove(productCode)
    else:
        cart["products"][productCode] = quantity
    
    cart["productsTotalCost"] = 0
    cart["productsTotalWeight"] = 0
    cart["cartTotal"] = 0

    countCodes = len(cart["products"])

    return countCodes

def updateCartTotals(products, cart):
    # update productsTotalCost, productsTotalWeight, cartTotal
    # return cartTotal
    
    productsTotalCost = 0
    productsTotalWeight = 0
    for i in cart["products"]:
        price = getProductPrice(products, i)
        weight = getProductWeight(products, i)
        quantity = cart["products"][i]

        productCost = price * quantity
        productsTotalCost += productCost

        productWeight = weight * quantity
        productsTotalWeight += productWeight
    
    cart["productsTotalCost"] = productsTotalCost
    cart["productsTotalWeight"] = productsTotalWeight

    cart["cartTotal"] = productsTotalCost

    return productsTotalCost


print(setCartItemQuantity(cart, "ABC", 4))
print(updateCartTotals(testProducts, cart))

print(setCartItemQuantity(cart, "DEF", 2))
print(updateCartTotals(testProducts, cart))

testingComplete = True