/*
 Kevin Jin
 
 lab number: final project
 authors: Kevin Jin, Lance Carrido, Jaymen Luther, Nguyen Nhat Cong Le
 description: The project is a house listing service providing the address, price, beds, baths, type, and area of houses in San Jose, with options to filter by address and price.
 */
/*
 assumptions:
 1. The CSV file taken in has a header line.
 
 pseudocode:
 initialize the constant NUM_FIELDS to be read from csv as 6
 initialize the numData read from csv as 0
 initialize dataHash to its default
 declare the dataTree
 initialize inventory as an array of House objects
 initialize an empty dataInv with a size of 25, taking in inventory
 
 define clearInput function to clear the cin object and ignore extraneous input
 define createDataFromSCV function:
    initialize CSVParser object to take in 1 entry from csv file with NUM_FIELDS
    initialize newHouse to store temporary house pointers to nullptr
    declare csvFile ifstream object
    declare filePath string object to take in filePath
    prompt user to enter the csv file path
    do:
        set filePath to user input
        open csvFile with filePath
        if the csvFile is not open, prompt user to enter again
        clearInput
    while csvFile is not open
    open ifstream helperCSVFile object, initialize helperCntData string object, initialize totalData
    while getline function executes to retrieve line from file:
        increment totalData
    decrement totalData to account for header line in csv
    prompt user to enter number of houses to read from csv file
    while the input is not within the number of houses in the csv or the input is not a number:
        state the input is invalid, and prompt the user to try again
        clearInput
    set the house data in the inventory by passing the filePath
    for the time i is less than numData + 1, increment i:
        try:
            declare inputStr string to store entry from csvFile from getline
            if i equals 0, continue
            CSVParser takes in 1 line of data from inputStr and splits it
            an array of strings curData stores the data the CSVParser split
            newHouse is dynamically allocated with a house object of the data in curData
            dataHash takes in newHouse pointer given the address as the key
            dataTree takes in newHouse pointer
            dataInv takes in newHouse object, set to false to prevent premature rewriting of file
        catch when invalid argument of house:
            output the error and the data not added
    update csv file data with what data is taken in using inventory object
    delete CSVParser object
    clearInput
 
    define main function:
        call createDataFromCSV
        set numInserted (number of data inserted) to the global numData
        set the while loop flag to true
        while flag is true
            print the menu options
            declare userResponse int variable
            while the input cannot be taken to an int:
                prompt the user to input a number
                clearInput
            clearInput
            declare string objects key and type
            declare int variables price, beds, baths, and area
            switch userResponse:
                case 1:
                    prompt user to enter address, store it in key
                    if the address matches a house already stored:
                        print to the user that it's already stored
                        break out of switch
                    else:
                        prompt user to enter price
                        while the input cannot be taken into an int:
                            print that input is invalid
                            clearInput
                        prompt user to enter beds
                        while the input cannot be taken into an int:
                            print that input is invalid
                            clearInput
                        prompt user to enter baths
                        while the input cannot be taken into an int:
                            print that input is invalid
                            clearInput
                        prompt user to enter property type
                        prompt user to enter area
                        while the input cannot be taken into an int:
                            print that input is invalid
                            clearInput
                        create pointer to house toInsert with user given attributes
                        insert the item in the dataHash, dataTree, and dataInv
                case 2:
                    prompt the user to enter the address, store it in key
                    if the address matches a house already stored:
                        print to the user that it's already stored
                        break out of switch
                    else:
                        assign the user input to key
                        initialize result to the pointer to the node in the hash table with given key
                        if result is not nullptr:
                            declare House tmp
                            set the price of tmp by retrieving the price from the pointer to the node
                            remove the
                    
    
 */

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <limits>
#include "hash.h"
#include "BST.h"
#include "Parser.h"
#include "Inventory.h"

using namespace std;

const int NUM_FIELDS = 6;
int numData = 0;
Hash<House>* dataHash = new Hash<House>();
BST<House> dataTree;

// The following array is for the inventory:
// - doesn't matter what House array size initialized to since addHouse function automatically increments the size, similar to a vector
// - dataInv has empty string which will be changed to filePath in the createData function
House* inventory = new House[25];
Inventory dataInv(25, inventory, 0, "");

/*
 Clears the input and ignores excess input.
 Pre: None
 Post: input stream skips to next line
 Return: None
 */
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/*
 Reads data from CSV into hash table and bst, skipping the header line.
 Pre: None
 Post: data from CSV in hash table and bst
 Return: None
 */
void createDataFromCSV() {
    Parser* CSVParser = new Parser(1, NUM_FIELDS);  // 1 indicates 1 entry from csv file taken
    House* newHouse = nullptr;
    ifstream csvFile;
    string filePath;
    
    cout << "Enter CSV file path: ";
   
    do {
        cin >> filePath;
        csvFile.open(filePath);
        if (!csvFile.is_open())
            cout << "Invalid file path. Please try again: ";
        clearInput();
    } while (!csvFile.is_open());

    // counts total number of houses in file
    ifstream helperCSVFile;
    helperCSVFile.open(filePath);
    string helperCntData;
    int totalData = 0;
    while (getline(helperCSVFile, helperCntData))
        ++totalData;
    --totalData;
    
    cout << "Enter the number of houses to read from the CSV file: ";
    while (!(cin >> numData) || numData > totalData || numData < 0) {
        cout << "Invalid input. Please try again: ";
        clearInput();
    }
    
    dataInv.setHouseData(filePath);
    
    // look over header line that takes up one from numData
    for (int i = 0; i < numData + 1; i++) {
        try {
            // read line and set it to inputStr
            string inputStr;
            getline(csvFile, inputStr);
            
            // skip the header line of csv file
            if (i == 0) continue;

            CSVParser->setData(0, inputStr);    // 0 signifies 1 data entry set
            string* curData = CSVParser->getData(0);
            newHouse = new House(curData[0], stoll(curData[1]), stoi(curData[2]), stoi(curData[3]), curData[4], stoi(curData[5]));
            
            /*
             adding house to hash table:
             - integer precision loss okay because price only used as key
             - when truncating long long to int, deletes excess 32 bits
            */
            dataHash->addItem(newHouse->getAddress(), newHouse);
            
            // adding house to BST
            dataTree.insert(newHouse);
            
            // adding house to inventory's array: set to false to prevent rewriting of file
            dataInv.addHouse(*newHouse, false);
        } catch (const std::invalid_argument& e) {
            cout << "Error parsing data " << i + 1 << " (" << e.what() << "). Data is not added." << endl;
        }
    }
    
    dataInv.updateHouseData();
    
    delete CSVParser;
    clearInput();
}

int main() {
    // loading data
    createDataFromCSV();
    
    // numData and numSearches used to find efficiency
    int numInserted = numData;

    // flag for menu
    bool flag = true;
    
    // main menu
    while (flag)
    {
        // menu options
        cout << endl;
        cout << "San Jose Housing Listing Service" << endl;
        cout << "--------------------------------" << endl;
        cout << "1. Add house" << endl;
        cout << "2. Delete house" << endl;
        cout << "3. Search house by address" << endl;
        cout << "4. List houses in hash table sequence" << endl;
        cout << "5. List house price in ascending order" << endl;
        cout << "6. List house price in given range" << endl;
        cout << "7. Print house price indented tree" << endl;
        cout << "8. Efficiency" << endl;
        cout << "9. Quit" << endl << endl;
        cout << "Enter your choice: ";

        int userResponse;
        while (!(cin >> userResponse)) {
            cout << "Invalid input. Please enter a number: ";
            clearInput();
        }
        
        clearInput();
        
        string key, type;
        int price, beds, baths, area;
        
        switch (userResponse) {
            case 1: { // adding data to hash table
                // address
                cout << "Enter the address: ";
                while (!(cin >> key))
                    clearInput();
                if (dataInv.searchHouse(key).getAddress() == key) {
                    cout << "House at " << key << " already in inventory!" << endl;
                    break;
                } else {
                    // price
                    cout << "Enter the price: ";
                    while (!(cin >> price)) // while loop to ensure user puts in int values
                    {
                        cout << "Invalid input. Please enter a whole number: ";
                        clearInput();
                    }

                    // beds
                    cout << "Enter the number of beds: ";
                    while (!(cin >> beds)) // while loop to ensure user puts in int values
                    {
                        cout << "Invalid input. Please enter a whole number: ";
                        clearInput();
                    }

                    // baths
                    cout << "Enter the number of baths: ";
                    while (!(cin >> baths)) // while loop to ensure user puts in int values
                    {
                        cout << "Invalid input. Please enter a whole number: ";
                        clearInput();
                    }
                    
                    clearInput();
                    
                    // prop type
                    cout << "Enter the property type: ";
                    getline(cin, type);
                    
                    // area
                    cout << "Enter the area (sq. ft.): ";
                    while (!(cin >> area)) // while loop to ensure user puts in int values
                    {
                        cout << "Invalid input. Please enter a whole number: ";
                        clearInput();
                    }
                    
                    clearInput();

                    // add item to hash table, bst, and inventory
                    House* toInsert = new House(key, price, beds, baths, type, area);
                    dataHash->addItem(key, toInsert);
                    dataTree.insert(toInsert);
                    dataInv.addHouse(*toInsert);
                    
                    ++numInserted;
                    break;
                }
            } case 2: {
                cout << "Enter the address: ";
                while (!(cin >> key))
                    clearInput();
                if (dataInv.searchHouse(key).getAddress() != key) {
                    cout << "House at " << key << " not found!" << endl;
                    break;
                } else {
                    // remove from bst
                    Node<House>* result = dataHash->getNode(key);
                    if (result) {
                        House tmp;
                        tmp.setPrice(result->data->getPrice());
                        tmp.setAddress(result->data->getAddress());
                        dataTree.remove(&tmp);
                        std::cout << "House at " << key << " deleted." << std::endl;
                    }
                    
                    // remove from hash
                    dataHash->removeItem(key);
                    
                    // remove from inventory
                    dataInv.deleteHouse(key);
                    break;
                }
            } case 3: {
                cout << "Enter the address: ";
                getline(cin, key);
                
                dataHash->searchItem(key);
                break;
            } case 4: {
                bool innerFlag = true;
                while (innerFlag != false) {
                    // printing options
                    cout << endl;
                    cout << "1. Print bucket index, number of items, and key\n2. Print specified bucket\n3. Print entire hash table\n4. Return to main menu" << endl << endl;
                    cout << "Enter your choice: ";

                    int userResponse;
                    while (!(cin >> userResponse)) {
                        cout << "Invalid input. Please enter a number (1-9): ";
                        clearInput();
                    }
                    
                    // nested menu
                    switch(userResponse) {
                        // print the whole hash table
                        case 1:
                            dataHash->printTable();
                            break;
                        case 2:
                            // print the table by searching for bucket
                            cout << "Input the bucket key: ";
                            clearInput();
                            getline(cin, key);
                            dataHash->printItemsInBucket(key);
                            break;
                        case 3:
                            dataHash->printEntireTable();
                            break;
                        case 4:
                            innerFlag = false;
                            break;
                        default:
                            cout << "Input not valid! Number out of range." << endl;
                            break;
                    }
                }
                break;
            } case 5: {
                dataTree.printBySortedKey(cout);
                break;
            } case 6: {
                // initialize min and max
                long min, max;
                cout << "Enter the minimum price in the range: ";
                while (!(cin >> min)) {
                    cout << "Invalid input. Please try again: ";
                    clearInput();
                }
                cout << "Enter the maximum price in the range: ";
                while (!(cin >> max)) {
                    cout << "Invalid input. Please try again: ";
                    clearInput();
                }
                // create min and max housing objects
                House minHouse;
                minHouse.setPrice(min);
                House maxHouse;
                maxHouse.setPrice(max);
                // pass min and max housing objects into printInRange
                dataTree.printInRange(minHouse, maxHouse);
                clearInput();
                break;
            } case 7: {
                dataTree.printIndentedTree(cout);
                break;
            } case 8: {
                cout << endl << setprecision(2) << fixed
                    << "Load factor: " << dataHash->getLoadFactor() << endl
                    << "Longest linked list: " << dataHash->getLongestListSize() << endl
                    << "Average number of nodes in linked lists: " << dataHash->getAverageListSize() << endl
                    << "Number of collisions in hash table: " << dataHash->getNumCollisions() << endl
                    << "Average number of operations to insert in BST: " << static_cast<int>(dataTree.getInsertCnt() / double(numInserted) + 0.9) << endl;
                break;
            } case 9: {
                flag = false;
                break;
            } default: {
                cout << "Input not valid! Number out of range." << endl;
                break;
            }
        }
    }
    
    string x = "";
    while (x != "x") {
        cout << "Enter <x> to quit the program: ";
        cin >> x;
    }
    
    return 0;
}
