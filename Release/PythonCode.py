import re
import string


def read_File():
    # Reads sppecified file and outputs a display of the number of occurence of each word

    accessedFile = open("project_three_input_file.txt") # Opens text file
    listOfProducts = accessedFile.read().split() # Creates a list of words it finds in the file
    sortedProducts = sorted(set(listOfProducts)) # Sorts to an ascending list of every word
    
    for product in sortedProducts: # Displays the quantity of the word in the file
       print("")
       print(" ", listOfProducts.count(product), " ",  product)
       print("")
       print("************************************")
    
    accessedFile.close() # Closes file

def locate_Total_Product_Amount(requestedProduct):
   # Takes a string from C++ user input
   # Searches through text file to count the total occurance of item
   # will print to console

   accessedFile = open("project_three_input_file.txt")
   listOfProducts = accessedFile.read().split() # Creates a list of words it finds in the file
   sortedProducts = sorted(set(listOfProducts)) # Sorts the words into an ascending list 
   accessedFile.close() # Closes file

   number_of_requested_product = 0 # Number to be sent back to C++
   number_of_all_products = 0 # Counts the amount of times loop iterates
   total_entries_in_file = 0 # Holds total inventory in document file

   for product in sortedProducts: # Gets total amount of items in list
       total_entries_in_file += 1

   for product in sortedProducts: # Finds the element in sortedProduct that matches the requested string from user
       temp_Product = product
       number_of_all_products += 1
       if (temp_Product == requestedProduct): # Adds 1 to number_of_all_products for everytime the loop finds a match
           number_of_requested_product = listOfProducts.count(product)
           number_of_all_products -= 1 
       if ((temp_Product != requestedProduct) and (number_of_all_products == total_entries_in_file)):
           return -1 # Exits with -1 if user input was not present in file

   return number_of_requested_product 


def read_And_Write_File():

   # Reads information from text file
   # Counts product and sorts/counts items
   # Takes the sorted and counted items and writes to a dat file
   # Calls histogram function to output to console

   productFile = open("project_three_input_file.txt") # Open file for reading
   data = open("frequency.dat", "w") # Open file for writing
   products = productFile.read().split() # List of every word in the read file
   sortedProducts = sorted(set(products)) # Sorts the items in ascending order

   # Writes the data to the .dat file
   for product in sortedProducts:
       data.write(product)
       data.write(" ")
       data.write(str(products.count(product))) # Converts the frequency of the selected word/item/product to string to write into .dat file
       data.write("\n")

   data.close() # Close write file, later opened for reading

   histogram_data = open("frequency.dat", "r") # Reads the .dat file
   product_data = histogram_data.readlines() # Read lines so each product matches with frequency amount

   # Temporary variables used for nested for loops
   temp_frequency = 0
   temp_product = ""

   # Reads and prepares data from .dat file for histogram
   for line in product_data:
       temp_int = 0
       temp_string = line.split() # Splits product name and frequency
       for product in temp_string:
           temp_int += 1
           if (temp_int == 1):
               temp_product = product # This is the product name
               print(temp_product, end = " ")
           if (temp_int == 2):
               temp_frequency = int(product) # This is the frequency of the product

       # Creates Histogram -- EXAMPLE: Carrots *******
       for i in range(temp_frequency):
           print("*", end = "")
       print("\n")
       print("------------------------------------")

