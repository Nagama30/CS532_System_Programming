
# Requirements

+ Windows - https://code.visualstudio.com/docs/cpp/config-mingw 
+ Mac - https://code.visualstudio.com/docs/cpp/config-clang-mac

# Compilation Instructions

## For compiling the code through VS code terminal- 

#### Below command will compile the filename and return an executable file with the executable_name
  gcc -o <executable_name> <filename.c>
  
Example:

  gcc -o listing listing.c
#### Above command will compile listing.c file and returns listing executable
## For executing the executable file-

  .\executable_name <command line arguments>
  
  Example:
  
  .\listing

# My Files

## main()

The main function opens listing.csv file, read the records from the file, store it into the structure. It uses the quick sort function to sort the data using Host_name & the Price and write the sorted data into the files. The program contains below functions:

### getfields()
### displayStruct()
### compareByHostName()
### compareByPrice()
### writeToFile()


# getfields() 
This function parses the input .csv file and reads the records from the file one by one and store it into the structure.

# displayStruct()
This function displays the records in the listing structure.

# compareByHostName()
This function compared the two records by host_name using strcmp function and returns the result to quick sort library function.

# compareByPrice()
This function compares the two records by Price and returns the result to quick sort library function.

# writeToFile()
This function write the sorted records into a .csv file.
  
# Output screenshots

![image](https://github.com/Nagama30/CS332-532/assets/60808524/fb6c2f65-b823-44e4-a103-1562271d9e80)

![image](https://github.com/Nagama30/CS332-532/assets/60808524/23e91158-3e1c-46fd-a65a-0334680e00fd)

![image](https://github.com/Nagama30/CS332-532/assets/60808524/22d04712-123b-47a4-b535-88fbfa11fcec)


# Link to github repository
https://github.com/Nagama30/CS332-532

