// Jaymen Luther

#include <iostream>
#include <string>
#include "House.h"

#ifndef HASH_H
#define HASH_H

const int tableSize = 50;

// linked list
template<class T>
struct Node
{
    // address key
    std::string key;
    // data
    T* data;
    // pointer to next
    Node<T>* next;
    // pointer to prev
    Node<T>* prev;
};

template<class T>
class Hash
{
    private:
        int nodeCnt = 0;
        double loadFactorLimit = 0.75;
        int tableSize = 50;
        // table
        Node<T>** table;
        // pointer to top
        Node<T>** top;
        /*
            
            int hashFunction(std::string key);
            get hash key
            Pre:    key.
            Post:    None.
            Return:    hash key
        */
        int hashFunction(std::string);
    
    public:
        double getLoadFactor() {
            return getNodeCnt() / double(tableSize);
        }
        Hash(int size, double lfLimit){
            tableSize = size;
            loadFactorLimit = lfLimit;
            table = new Node<T>* [tableSize];
            top = new Node<T>* [tableSize];

            for(int i = 0; i < tableSize; i++)
            {
                table[i] = NULL;
                top[i] = NULL;
            }
        }
        int getNodeCnt() {
            return nodeCnt;
        }
        int getLongestListSize();
        double getAverageListSize();
        int getNumCollisions();
        /*
            void addItem(std::string key, int price, int beds, int baths, std::string prop_type, int area);
            add item to hash table
            Pre:    std::string key, int price, int beds, int baths, std::string prop_type, int area
            Post:    None.
            Return:    None.
        */
        void addItem(std::string, T*);
        /*
            
            void removeItem(std::string key);
            remove item from hash table
            Pre:    std::string key
            Post:    None.
            Return:    None.
        */
        void removeItem(std::string);
    
        /*
         Returns the node with the given key.
         Pre: std::string key - the string used to identify the wanted node
         Post: None
         Return: Node - the node with the given key
         */
        Node<T>* getNode(std::string);
        /*
            
            void searchItem(std::string key);
            search for key in hash table and display data found
            Pre:    std::string key
            Post:    None.
            Return:    None.
        */
        void searchItem(std::string);
        /*
            
            int itemsAtIndex(int index);
            get amount of items in a given bucket
            Pre:    int index
            Post:    None.
            Return:    index
        */
        int itemsAtIndex(int);
        /*
            
            void printItemsInBucket(std::string key);
            print the items in any given bucket
            Pre:    std::string key
            Post:    None.
            Return:    None.
        */
        void printItemsInBucket(std::string);
        /*
            
            void printTable();
            print the hash table
            Pre:    None.
            Post:    None.
            Return:    None.
        */
        void printTable();
    
        void printEntireTable();
    
//         void reHash() {
//             tableSize *= 2;
//             Node<T>** newTable = new Node<T>*[tableSize];
//             delete []top;
//             top = new Node<T>*[tableSize];
//             for (int i = 0; i < tableSize/2; i++) {
//                 Node<T>* temp = table[i];
//                 if (temp != nullptr) {
//                     int hash_value = hashFunction(temp->key);
//                     newTable[hash_value] = temp;
//                     if(temp != nullptr)
//                         while (temp->next != nullptr)
//                             temp = temp->next;
//                     top[hash_value] = temp;
//                 }
//             }
//             Node<T>** tempTable = table;
//             table = newTable;
//             delete []tempTable;
//         }
        void reHash() {
            std::cout << "rehash" << std::endl;
            tableSize *= 2;
            Node<T>** newTable = new Node<T>*[tableSize];
            for (int i = 0; i < tableSize; i++)
                newTable[i] = nullptr;
            Node<T>** tempTable = table;
            table = newTable;
            delete[]top;
            top = new Node<T>*[tableSize];
            for (int i = 0; i < tableSize / 2; i++) {
                Node<T>* temp = tempTable[i];
                while (temp != nullptr)
                {
                    addItem(temp->key, temp->data);
                    temp = temp->next;
                }
            }
            for (int i = 0; i < tableSize / 2; i++) {
                Node<T>* temp = tempTable[i];
                while (temp != nullptr)
                {
                    Node<T>*temp2 = temp->next;
                    delete temp;
                    temp = temp2;
                }
            }
            delete[]tempTable;
        }

        // constructor
        Hash();
        // destructor
        ~Hash();

};

template<class T>
int Hash<T>::getLongestListSize()
{
    int longestListSize = 0;
    int tempSize = 0;;
   // create a temp node
    Node<T>* temp = new Node<T>();
    
    // loop through and print the table contents
    for(int i = 0; i < tableSize; i++)
    {
        temp = table[i];
        if (temp != NULL)
        {
            int itemsAtList = itemsAtIndex(i);
            tempSize = itemsAtList;

            if(tempSize > longestListSize)
            {
                longestListSize = tempSize;
            }
        }
    }
    delete temp;
    return longestListSize;
}

template<class T>
double Hash<T>::getAverageListSize()
{
    double average = 0;
    int total = 0;
    double counter = 0;
    // create a temp node
    Node<T>* temp = new Node<T>();
    
    // loop through and print the table contents
    for(int i = 0; i < tableSize; i++)
    {
        temp = table[i];
        if (temp != NULL)
        {
            int numOfItems = itemsAtIndex(i);
            total += numOfItems;
            counter++;
        }
    }
    average = total / counter;
    delete temp;
    return average;
}

template<class T>
int Hash<T>::getNumCollisions()
{
    int numColl = 0;
    int tmpListSize = 0;

    // create a temp node
    Node<T>* temp = new Node<T>();
    
    // loop through and print the table contents
    for(int i = 0; i < tableSize; i++)
    {
        temp = table[i];
        if (temp != NULL)
        {
            int num = itemsAtIndex(i);

            if(num > 1)
            {
                numColl += num - 1;
            }
        }
    }
    delete temp;
    return numColl;
}

template<class T>
int Hash<T>::hashFunction(std::string key)
{
    // get int value of key
    int charSum = 0;
    for (int i = 0; i < key.length()/2; ++i)
        charSum += static_cast<char>(key[i]);
    
    int hash_value = charSum;
    // return hash_value mod tablesize to get our hash key
    return hash_value % tableSize;
}
template<class T>
void Hash<T>::addItem(std::string key, T* data) {
    // get hash Key
    int hash_value = hashFunction(key);
    // make table entry
    Node<T>* entry = table[hash_value];

    // check if entry is NULL and there nodes in the bucket
    if (entry == NULL)
    {
        // create a new node and assign values
        entry = new Node<T>;
        entry->key = key;
        entry->data = data;
        // set the next and prev to NULL
        entry->next = NULL;
        entry->prev = NULL;
        // set the table[hash_value] and top equal to the new node entry
        table[hash_value] = entry;
        top[hash_value] = entry;
    }
    else
    { // if the entry is not equal to NULL then move to the next node until we find a NULL value
        while (entry != NULL)
        {
            entry = entry->next; // move to next
        }
        // once we find a NULL create a new item and assign values
        entry = new Node<T>;
        entry->key = key;
        entry->data = data;
        entry->next = NULL;
        entry->prev = top[hash_value];
        top[hash_value]->next = entry;
        top[hash_value] = entry;
    }
    ++nodeCnt;
    
    double currLF = nodeCnt / double(tableSize);
    if(currLF >= loadFactorLimit)
        reHash();
}
template<class T>
void Hash<T>::removeItem(std::string key)
{
    // get hash key
    int hash_value = hashFunction(key);
    // create a new node
    Node<T>* entry = table[hash_value];
    Node<T>* head_ref = table[hash_value];

    // if the nodes key is not equal to the key or the entry is NULL then we can't find the key
    if (entry == NULL)
    {
        // removed cout line since already taken care of by inventory class function in main
        return;
    }
    // while the entry isnt NULL we need to move to check the next and previous node are NULL
    while (entry != NULL)
    {
        // checking to see if the keys match
        if(entry->key == key)
        {
            // if the node is alone, i.e not in a linked list
            if (entry->next == NULL && entry->prev == NULL)
            {
                // set the table and top to NULL and delete the entry and break so we can move to the next node
                table[hash_value] = NULL;
                head_ref = NULL;
                delete entry;
                break;
            }
            // if the node is the first entry in the linked list
            if (head_ref == entry)
            {
               head_ref = entry->next;
               table[hash_value] = entry->next;
               delete entry;
               break;

            }
            // if the next node is not null
            if(entry->next != NULL)
            {
                entry->next->prev = entry->prev;
            }
            // if the prev node is not null
            if(entry->prev != NULL)
            {
                entry->prev->next = entry->next;
            }
            delete entry;
            return;
        }
        // move to next node
        entry = entry->next;
    }
    --nodeCnt;
}
template<class T>
Node<T>* Hash<T>::getNode(std::string key) {
    // create hash key
    int hash_value = hashFunction(key);
    // make an entry node
    Node<T>* entry = table[hash_value];
    // check flag set to false for when we find matches
    bool check = false;

    if (entry != nullptr) {
        while (entry != nullptr) {
            if (entry->key == key)
                check = true;
            if (check)
                return entry;
            entry = entry->next;
        }
    }
    
    return nullptr;
}
template<class T>
void Hash<T>::searchItem(std::string key)
{
    // create hash key
    int hash_value = hashFunction(key);
    // make an entry node
    Node<T>* entry = table[hash_value];
    // check flag set to false for when we find matches
    bool check = false;

    // if the entry isn't empty
    if (entry != NULL)
    {
        // loop while the entry is not empty
        while (entry != NULL)
        {
            // check to see if the key is matching
            if(entry->key == key)
            {
                // set to true if you find a match
                check = true;
            }
            // if the check is true let the user know the values assosicated with that key
            if (check)
            {
                std::cout << "Price: " << entry->data->getPrice() << std::endl;
                std::cout << "Beds: " << entry->data->getBeds() << std::endl;
                std::cout << "Baths: " << entry->data->getBaths() << std::endl;
                std::cout << "Type: " << entry->data->getType() << std::endl;
                std::cout << "Area: " << entry->data->getArea() << std::endl;
                return;
            }
            // move to the next node
            entry = entry->next;
        }
    }
    // if the check is false then you didn't find the node and let the user know
    if (!check)
    {
        std::cout << "No house found." << std::endl;
    }
}
// get the amount of items in each bucket
template<class T>
int Hash<T>::itemsAtIndex(int index)
{
    // create a temp node equal to the table at the index
    Node<T>* temp = table[index];
    // counter variable
    int counter = 0;
    // if temp is NULL then return the counter
    if (temp == NULL)
    {
        return counter;
    }
    else
    {
        // when the counter is not NULL loop through each node and counter++
        while (temp != NULL)
        {
            counter++;
            temp = temp->next;
        }
    }
    return counter;
    
}

// print any given bucket
template<class T>
void Hash<T>::printItemsInBucket(std::string key)
{
    // get hash key
    int hash_value = hashFunction(key);
    // create temp node equal to the bucket you are looking for
    Node<T>* temp = table[hash_value];
    // if the temp is empty let the user know theres nothing in that bucket
    if (temp == NULL)
    {
        std::cout << "Empty bucket!" << std::endl;
    }
    else
    // otherwise print the bucket
    {
        while (temp != NULL)
        {
            std::cout << "Address: " << temp->key << std::endl;
            std::cout << "Price: " << temp->data->getPrice() << std::endl;
            std::cout << "Beds: " << temp->data->getBeds() << std::endl;
            std::cout << "Baths: " << temp->data->getBaths() << std::endl;
            std::cout << "Type: " << temp->data->getType() << std::endl;
            std::cout << "Area: " << temp->data->getArea() << std::endl;
            std::cout << std::endl;
            temp = temp->next;
        }
    }
}
// print the hash table
template<class T>
void Hash<T>::printTable() {
    std::cout << std::left
        << std::setw(10) << "Index"
        << std::setw(10) << "Items"
        << std::setw(10) << "Key" << std::endl << std::endl;
    
    // print table contents
    for (int i = 0; i < tableSize; i++) {
        Node<T>* temp = table[i];
        if (temp != nullptr) {
            std::cout << std::left
                << std::setw(10) << i
                << std::setw(10) << itemsAtIndex(i)
                << std::setw(10) << temp->key << std::endl;
        }
    }
}
template<class T>
void Hash<T>::printEntireTable() {
    for (int i = 0; i < tableSize; i++) {
        Node<T>* temp = table[i];
        while (temp != nullptr) {
            std::cout << temp->data->getAddress() << ", "
                << temp->data->getPrice() << ", "
                << temp->data->getBeds() << ", "
                << temp->data->getBaths() << ", "
                << temp->data->getType() << ", "
                << temp->data->getArea() << std::endl;
            temp = temp->next;
        }
    }
}

// constructor
template<class T>
Hash<T>::Hash()
{
    table = new Node<T>* [tableSize];
    top = new Node<T>* [tableSize];

    for(int i = 0; i < tableSize; i++)
    {
        table[i] = NULL;
        top[i] = NULL;
    }
}
//destructor
template<class T>
Hash<T>::~Hash()
{
    Node<T>* temp;
    Node<T>* temp_next;
    for(int i = 0; i < tableSize; i++)
    {
        temp = table[i];
        while (temp != NULL)
        {
            temp_next = temp->next;
            delete temp->data;
            delete temp;
            temp = temp_next;
        }
        table[i] = NULL;
    }
}

#endif
