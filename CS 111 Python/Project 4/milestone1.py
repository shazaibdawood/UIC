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

print("Testing getProductCategories")
print(getProductCategories(testProducts))

print("Testing getProductPrice")
print(getProductPrice(testProducts, "ABC"))
print(getProductPrice(testProducts, "DEF"))

print("Testing getProductsByCategory")
print(getProductsByCategory(testProducts, "electronics"))
print(getProductsByCategory(testProducts, "food"))
print(getProductsByCategory(testProducts, "computers"))

print("Testing getProductsBySearch")
print(getProductsBySearch(testProducts, "features"))
print(getProductsBySearch(testProducts, "laptop"))
print(getProductsBySearch(testProducts, "tv"))

testingComplete = True