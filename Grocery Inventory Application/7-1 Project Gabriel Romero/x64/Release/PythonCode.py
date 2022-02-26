import re
import string
from collections import Counter

# Reads txt file data and saves info into a list
with open("CS210_Project_Three_Input_File.txt", "r") as data_file:
    content_list = []                           # Declare content list for use in other functions
    for line in data_file:
            line = line.strip()                 # Removes \n character at the end of the line
            content_list.append(line)           # Appends into the list for easy access for other functions
data_file.close()

# Declaring global unique list for use in other functions
list_set = set(content_list)                # Grab unique values from main data list
unique_item_list = (list(list_set))         # return unique values into a list
item_count = Counter(content_list)          # Use counter to count the occurences of unique items

# creates data file for c++ to use in histogram function
def creatDataFile():
    with open("frequency.dat", "w") as frequency_file:
        for item in unique_item_list:
         frequency_file.write(item + " " + str(item_count[item]) + "\n")
    frequency_file.close()

# Prints out unique items in the list and their frequencies
def printAllItemsCount():
    print('{0: <12}| {1: <12}'.format('Item', 'Amount Purchased'))
    print('-------------------------------------')
    for item in unique_item_list:
        print('{0: <12}: {1: <5}'.format(item, item_count[item]))

# Prints out specific item that is passed to function
def printSpecificItemCount(itemName):
    if itemName in unique_item_list:        # Checks for item in the unique item list made above
        print('{0: <12}| {1: <12}'.format('Item', 'Amount Purchased'))
        print('-------------------------------------')
        print('{0: <12}: {1: <5}'.format(itemName, item_count[itemName]))
        return item_count[itemName]
    else:
        print("List of Items for Today")
        print("-----------------------")
        for item in unique_item_list:           # If item was not found on list print items that are IN list
            print(item)
        print("")                               # used for spacing
        print('Item not found in list, please try again')
        return -1       




    
