#include <iostream>
#include <string>
#include "hash.h"

int Hash::hashFunction(std::string key)
{
    // get int value of key
    int hash_value = key.length();
    // return hash_value mod tablesize to get our hash key
    return hash_value % tableSize;
}
void Hash::addItem(std::string key, int price, int beds, int baths, std::string prop_type, int area)
{
    // get hash Key
    int hash_value = hashFunction(key);
    // make table entry
    Node* entry = table[hash_value];

    // check if entry is NULL and there nodes in the bucket
    if (entry == NULL)
    {
        // create a new node and assign values
        entry = new Node;
        entry->key = key;
        entry->price = price;
        entry->beds = beds;
        entry->baths = baths;
        entry->prop_type = prop_type;
        entry->area = area;
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
        entry = new Node;
        entry->key = key;
        entry->price = price;
        entry->beds = beds;
        entry->baths = baths;
        entry->prop_type = prop_type;
        entry->area = area;
        entry->next = NULL;
        entry->prev = top[hash_value];
        top[hash_value]->next = entry;
        top[hash_value] = entry;
    } // display information
    std::cout << "Value " << entry->price << " was added at key " << key << std::endl;
    std::cout << "Value " << entry->beds << " was added at key " << key << std::endl;
    std::cout << "Value " << entry->baths << " was added at key " << key << std::endl;
    std::cout << "Value " << entry->prop_type << " was added at key " << key << std::endl;
    std::cout << "Value " << entry->area << " was added at key " << key << std::endl;
}
void Hash::removeItem(std::string key)
{
    // get hash key
    int hash_value = hashFunction(key);
    // create a new node
    Node* entry = table[hash_value];
    Node* head_ref = table[hash_value];

    // if the nodes key is not equal to the key or the entry is NULL then we can't find the key
    if (entry == NULL)
    {
        std::cout << "Key not found" <<std::endl;
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
                //3279 Trebol Ln
                //1944 Scenic Sq
                entry->prev->next = entry->next;
            }
            std::cout << "entry deleted" << std::endl;
            delete entry;
            return;
        }
        // move to next node
        entry = entry->next;
    }
}
void Hash::searchItem(std::string key)
{
    // create hash key
    int hash_value = hashFunction(key);
    // make an entry node
    Node* entry = table[hash_value];
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
                std::cout << "Element found at key " << key << " is " << entry->price << std::endl;
                std::cout << "Element found at key " << key << " is " << entry->beds << std::endl;
                std::cout << "Element found at key " << key << " is " << entry->baths << std::endl;
                std::cout << "Element found at key " << key << " is " << entry->prop_type << std::endl;
                std::cout << "Element found at key " << key << " is " << entry->area << std::endl;
                return;
            }
            // move to the next node
            entry = entry->next;
        }
    }
    // if the check is false then you didn't find the node and let the user know
    if (!check)
    {
        std::cout << "No element found at key" << key << std::endl;
    }
}
// get the amount of items in each bucket
int Hash::itemsAtIndex(int index)
{
    // create a temp node equal to the table at the index
    Node* temp = table[index];
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
void Hash::printItemsInBucket(std::string key)
{
    // get hash key
    int hash_value = hashFunction(key);
    // create temp node equal to the bucket you are looking for
    Node* temp = table[hash_value];
    // if the temp is empty let the user know theres nothing in that bucket
    if (temp == NULL)
    {
        std::cout << "Nothing in this bucket" << std::endl;
    }
    else
    // other wise print the bucket
    {
        std::cout << "Bucket has the following items: " << std::endl;
        while (temp != NULL)
        {
            std::cout << "Key " << temp->key << std::endl;
            std::cout << "Price: " << temp->price << std::endl;
            std::cout << "Beds: " << temp->beds << std::endl;
            std::cout << "Baths: " << temp->baths << std::endl;
            std::cout << "Prop_type: " << temp->prop_type << std::endl;
            std::cout << "Area: " << temp->area << std::endl;
            std::cout << std::endl;
            temp = temp->next;
        }
    }
}
// print the hash table
void Hash::printTable()
{
    // create a temp node
    Node* temp = new Node;
    
    // loop through and print the table contents
    for(int i = 0; i < tableSize; i++)
    {
        temp = table[i];
        if (temp != NULL)
        {
            std::cout << "Index " << i << std::endl;
            std::cout << "Key: " << temp->key << std::endl;
            std::cout << "Price: " << temp->price << std::endl;
            std::cout << "Beds: " << temp->beds << std::endl;
            std::cout << "Baths: " << temp->baths << std::endl;
            std::cout << "Prop_type: " << temp->prop_type << std::endl;
            std::cout << "Area: " << temp->area << std::endl;
            std::cout << "Number of items in this bucket: " << itemsAtIndex(i) << std::endl;
            std::cout << std::endl;
        }
    }
}
// constructor 
Hash::Hash()
{
    table = new Node* [tableSize];
    top = new Node* [tableSize];

    for(int i = 0; i < tableSize; i++)
    {
        table[i] = NULL;
        top[i] = NULL;
    }
}
//destructor 
Hash::~Hash()
{
    Node* temp;
    Node* temp_next;
    for(int i = 0; i < tableSize; i++)
    {
        temp = table[i];
        while (temp != NULL)
        {
            temp_next = temp->next;
            delete temp;
            temp = temp_next;
        }
        table[i] = NULL;
    }
}