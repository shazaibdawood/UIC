# user name rules:
# Must be exactly 8 characters
# Must start with a letter

print("Connections")
print("Group words that share a common thread.")

userName = input("Enter your username: ")

if(len(userName) != 8):
    userName = input("\nUsername must be 8 characters, please try again: ")
elif(not userName[0].isalpha()):
    userName = input("\nUsername must start with a letter, please try again: ")

if(len(userName) != 8 or (not userName[0].isalpha())):
    print("\nGoodbye.")
else:
    print("\nWelcome,", userName, end = "")
    print("!")