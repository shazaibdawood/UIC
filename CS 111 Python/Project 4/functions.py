# function uses the requests module
import requests
def getExchangeRate(currencyCode):
    ''' retrieve current exchange rate
   
        return -1 if code is invalid
    
	   usage:
		returned value is divisor to get USD value
		e.g. if price is in CAD, 
			price / getExchangeRate("CAD") is the USD price


    '''
   
    # default to a value that will indicate an error
    exchangeRate = -1
   
    if (currencyCode == "USD"):
        # don't need to make API call
        exchangeRate = 1
    else:
        # address for API that returns exchange rate data
        url = "https://v6.exchangerate-api.com/v6/add9f6398d00f2d51dc0511b/latest/USD"
       
        # make the request
        response = requests.get(url)


        # convert the response from JSON to Python object(s)
        data = response.json()


        rates = data["conversion_rates"]


        if (currencyCode in rates):
            exchangeRate = float(rates[currencyCode])


    return exchangeRate


def getProductsBySearch (products, searchTerm):
    """
    # searches name and notes for presence of searchTerm
    # search is case-insensitive
    # returns a list of product codes, or an empty list
    """
    
    productCodes = []

    for i in products:
        if((searchTerm).upper() in (products[i]["name"]).upper() or (searchTerm).upper() in (products[i]["notes"]).upper()):
            productCodes.append(i)
        
    return productCodes

def getProductsByCategory(products, categoryName):
    """
    # returns a list of product codes for the category name, or an empty list
    """
    
    productCodes = []

    for i in products:
        if(categoryName in products[i]["categories"]):
            productCodes.append(i)
    
    return productCodes


def getProductCategories(products):
    """
    # returns a list of category names, sorted 
    """

    categories = []
    
    for i in products:
        #print(products[i])
        for j in products[i]:
            #print(products[i][j])
            if(j == "categories"):
                for k in products[i][j]:
                    categories.append(k)
    categories = set(categories)
    categories = list(categories)
    categories.sort()
    return categories

def getProductWeight (products, productCode):
    """
    # return weight as float
    """
    
    weight = products[productCode]["weight"]

    return weight

def getProductCurrency (products, productCode):
    """
    # return currency exchange rate into USD as float
    """
    
    currency = products[productCode]["currency"]

    return currency

def getProductPrice (products, productCode):
    """
    # return price in USD as float
    """
    
    price = products[productCode]["price"]

    currency = getProductCurrency(products, productCode)
    exchangeRate = getExchangeRate(currency)

    priceUSD = round(price / exchangeRate, 1)

    return priceUSD

def setCartItemQuantity(cart, productCode, quantity):
    """
	# update cart products dictionary
	# quantity is the new quantity, not the change in quantity
	# quantity value <= 0 should remove productCode from dictionary
	# productsTotalCost, productsTotalWeight, cartTotal are set to 0
	# returns count of productCodes in the cart
    """

    if(quantity <= 0):
        cart["products"].pop(productCode)
    else:
        cart["products"][productCode] = quantity
    
    cart["productsTotalCost"] = 0
    cart["productsTotalWeight"] = 0
    cart["cartTotal"] = 0

    countCodes = len(cart["products"])

    return countCodes

def updateCartTotals(products, cart):
    """
    # update productsTotalCost, productsTotalWeight, cartTotal
    # return cartTotal
    """
    
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

