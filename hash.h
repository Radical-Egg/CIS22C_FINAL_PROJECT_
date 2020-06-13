// Jaymen Luther

#include <iostream>
#include <string>

const int tableSize = 50;

// linked list
struct Node
{
    // address key
    std::string key;
    // data
    int price;
    int beds;
    int baths;
    std::string prop_type;
    int area;
    
    // pointer to next
    Node* next;
    // pointer to prev
    Node* prev;
};

class Hash
{
    public:
        // table
        Node** table;
        // pointer to top
        Node** top;
		/*
			
			int hashFunction(std::string key);

			get hash key

			Pre:	key.
			Post:	None.
			Return:	hash key
		*/
        int hashFunction(std::string);
		/*
			
			void addItem(std::string key, int price, int beds, int baths, std::string prop_type, int area);

			add item to hash table

			Pre:	std::string key, int price, int beds, int baths, std::string prop_type, int area
			Post:	None.
			Return:	None.
		*/
        void addItem(std::string, int, int, int, std::string, int);
		/*
			
			void removeItem(std::string key);

			remove item from hash table

			Pre:	std::string key
			Post:	None.
			Return:	None.
		*/
        void removeItem(std::string);
		/*
			
			void searchItem(std::string key);

			search for key in hash table and display data found

			Pre:	std::string key
			Post:	None.
			Return:	None.
		*/
        void searchItem(std::string);
		/*
			
			int itemsAtIndex(int index);

			get amount of items in a given bucket

			Pre:	int index
			Post:	None.
			Return:	index
		*/
        int itemsAtIndex(int);
        /*
			
			void printItemsInBucket(std::string key);

			print the items in any given bucket

			Pre:	std::string key
			Post:	None.
			Return:	None.
		*/
        void printItemsInBucket(std::string);
        /*
			
			void printTable();

			print the hash table

			Pre:	None.
			Post:	None.
			Return:	None.
		*/
        void printTable();

        // constructor 
        Hash();
        // destructor
        ~Hash();

};