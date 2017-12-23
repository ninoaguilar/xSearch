//
//  hash.cpp
//  HashTable
//
//  Created by Nino Aguilar - A01875439 on 3/16/15.
//  Copyright (c) 2015 Nino Aguilar. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <queue>
#include <iomanip>
#include <string>

#include "searchengine.h"

/*
 *  Hash constructor
 */
SearchEngine::SearchEngine()
{
    for (int i = 0; i < tableSize; i++)
    {
        HashTable[i] = new item;
        HashTable[i]->name = "empty";
        HashTable[i]->id = NULL;
        HashTable[i]->next = NULL;
    }
}

/*
 *  Adds item into hash table,
 *  passes two variables:
 *  name = word being hashed
 *  docName = name of document that word is found it
 */
void SearchEngine::addItem(std::string name, std::string docName)
{
    int index = hash(name);

    // Checks if index item name is set to "empty"
    // and overides all information
    if (HashTable[index]->name == "empty")
    {
        HashTable[index]->name = name;
        HashTable[index]->id = new doc;
        HashTable[index]->id->name = docName;
        HashTable[index]->id->count = 1;
        HashTable[index]->id->next = NULL;
    }
    else
    {
        item *itemPtr = HashTable[index];
        doc *docPtr;

        // Checks if item is in the hash table
        if (findItem(name))
        {
            // Looks for item location
            while (itemPtr->name != name)
            {
                itemPtr = itemPtr->next;
            }

            docPtr = itemPtr->id;

            // Checks if document is alread stored
            // If yes, increase document count
            if (findDoc(name, docName))
            {
                while (docPtr->name != docName)
                {
                    docPtr = docPtr->next;
                }

                docPtr->count++;
            }
            else
            {
                // Creates new document struct
                // and links at the end
                doc *d = new doc;
                d->name = docName;
                d->count = 1;
                d->next = NULL;

                while (docPtr->next != NULL)
                {
                    docPtr = docPtr->next;
                }

                docPtr->next = d;
            }
        }
        else
        {
            // If item is not in hash table
            // it creates a new pointer
            // and links to the end of the last pointer
            item *n = new item;
            doc *d = new doc;

            n->name = name;
            n->next = NULL;

            d->name = docName;
            d->count = 1;
            d->next = NULL;

            while (itemPtr->next != NULL)
            {
                itemPtr = itemPtr->next;
            }

            n->id = d;
            itemPtr->next = n;
        }
    }
}

/*
 * bool function that looks for word in hash table
 * true if found, false if not found
 */
bool SearchEngine::findItem(std::string name)
{
    int index = hash(name);
    item *itemPtr = HashTable[index];

    if (HashTable[index]->name != "empty")
    {
        do
        {
            if (itemPtr->name == name)
            {
                return true;
            }
            itemPtr = itemPtr->next;
        } while (itemPtr != NULL);
    }

    return false;
}

/*
 * bool function that looks for document struct in hash table
 * true if found, false if not found
 */
bool SearchEngine::findDoc(std::string name, std::string docName)
{
    int index = hash(name);
    item *itemPtr = HashTable[index];
    doc *docPtr;

    if (HashTable[index]->name != "empty")
    {
        do
        {
            if (itemPtr->name == name)
            {
                docPtr = itemPtr->id;
                while (docPtr->name != docName)
                {
                    if (docPtr->next == NULL)
                    {
                        return false;
                    }
                    docPtr = docPtr->next;
                }
                return true;
            }
            itemPtr = itemPtr->next;
        } while (itemPtr != NULL);
    }

    return false;
}

/*
 *  Calulates number of items in a single index
 */
int SearchEngine::numIndex(int index)
{
    int count = 0;

    if (HashTable[index]->name == "empty")
    {
        return count;
    }
    else
    {
        count++;
        item *itemPtr = HashTable[index];
        while (itemPtr->next != NULL)
        {
            count++;
            itemPtr = itemPtr->next;
        }
    }

    return count;
}

/*
 *  Main search function
 *  Implements std::queue to store keywords
 *  and to store search results
 */
void SearchEngine::Search(std::string keyword)
{
    std::queue<std::string> keys;
    std::queue<std::string> a;
    std::queue<std::string> b;
    std::string word1;
    std::string word2;
    bool prevTerms = false;

    // Tranforms std::string keyword to all lowercase
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

    std::cout << "Searching for: " << keyword << std::endl
              << std::endl;

    for (uint64_t i = 0; i < keyword.length(); i++)
    {
        if (keyword[i] == '-')
            keyword[i] = ' ';
    }

    std::istringstream iss(keyword);

    // Pushes individual words from keyword std::string
    // to the keys std::queue
    while (iss >> keyword)
    {
        keys.push(keyword);
    }

    // This is here all the searching is proccessed
    while (!keys.empty())
    {
        // pops first word to word1 variable for later searching
        word2 = "";
        word1 = keys.front();
        keys.pop();

        // pops second word to word2 variable for later comparison
        if (!keys.empty())
        {
            word2 = keys.front();
            keys.pop();
        }

        /*
         * checks if first search term is "AND" or "OR" This occures when
         * search keywords had multiple "AND's" e.g. "flow AND stream AND chart"
         * and searching is in the second interation of searching
         * e.g. after dequeueing "flow and stream and chart" the
         * std::queue make look like "and chart"
         */
        if (word1 == "and" || word1 == "or")
        {
            // checks if this is the second iteration of searching
            if (prevTerms)
            {
                // Stores results in b std::queue
                b = search(word2);
            }
            else
                break;
        }
        else
        {
            /*
             * first search term was not "AND"/"OR'
             * now checking for search terms is no bool
             * e.g. a search for "flow stream"
             */
            if (prevTerms)
                b = search(word1);
            else
            {
                a = search(word1);
                b = search(word2);
                if (word2 == "")
                    break;
            }
        }

        /*
         * Here is where the bool are check
         * is the second term is "AND"/"OR"
         * pass it to the appropriate function
         */
        if (word2 == "and")
        {
            // Looks for word after "AND"
            // e.g. "flow AND stream",
            // stream would be passed to word2
            word2 = keys.front();
            keys.pop();

            b = search(word2);

            //Passes to AND function for comparison
            AND(a, b);
        }
        else if (word2 == "or")
        {
            // Looks for word after "OR"
            // e.g. "flow OR stream",
            // stream would be passed to word2
            word2 = keys.front();
            keys.pop();

            b = search(word2);

            //Passes to AND function for comparison
            OR(a, b);
        }
        else
        {
            /*
             * If search function is in the second iteration
             * of search, it will check for cases "AND chart"
             * and "OR chart"
             */

            if (word1 == "or")
                OR(a, b);
            else
                AND(a, b);
        }

        prevTerms = true;
    }

    // Prints out search results
    if (a.empty())
    {
        std::cout << "No Results Found...\n\n";
    }
    else
    {
        std::cout << "Found in document(s): " << std::endl;

        while (!a.empty())
        {
            std::cout << a.front() << std::endl;
            a.pop();
        }
    }
}

/*
 * AND function
 * In this function two queues are passed but
 * only the first std::queue is passed by reference
 *
 * document name must be found in both queues
 * being passed to end up in the final result
 */
void SearchEngine::AND(std::queue<std::string> &a, std::queue<std::string> b)
{
    //Attempt to reset "a" std::queue for later comparison
    if (!a.empty())
    {
        std::queue<std::string> temp = a;

        //Dequeue a until empty
        while (!a.empty())
        {
            a.pop();
        }

        // Continues until one of the queues are empty
        while (!temp.empty() && !b.empty())
        {
            // Function used to get document numbers
            // for easier comparison
            int aNum = docNum(temp.front());
            int bNum = docNum(b.front());

            if (aNum == bNum)
            {
                // Doc numbers for both queues are the same
                // add to "a" std::queue
                a.push(temp.front());
                temp.pop();
                b.pop();
            }
            // If doc number of one std::queue is greater
            // it will dequeue for later comparison
            else if (aNum < bNum)
                temp.pop();
            else
                b.pop();
        }
    }
}

/*
 * OR function
 * In this fuction two queues are passed but
 * only the a std::queue is passed by reference
 *
 * Document names from both queues will be sent to
 * the final result, this function checks that a duplicate
 * document name is not created
 */
void SearchEngine::OR(std::queue<std::string> &a, std::queue<std::string> b)
{
    // Checks that both queues are not empty
    if (!a.empty() || !b.empty())
    {
        std::queue<std::string> temp;

        while (!a.empty() || !b.empty())
        {
            // If "a" becomes empty, all of "b's"
            // documents names will be passed to final result
            // else vic vera
            if (a.empty())
            {
                while (!b.empty())
                {
                    temp.push(b.front());
                    b.pop();
                }
                break;
            }
            else if (b.empty())
            {
                while (!a.empty())
                {
                    temp.push(a.front());
                    a.pop();
                }
                break;
            }
            else
            {
                // Gets document names for better comparison
                int aNum = docNum(a.front());
                int bNum = docNum(b.front());

                // Check to make sure that document names are
                // only passed once
                if (aNum == bNum)
                {
                    temp.push(a.front());
                    a.pop();
                    b.pop();
                }
                else if (aNum < bNum)
                {
                    temp.push(a.front());
                    a.pop();
                }
                else
                {
                    temp.push(b.front());
                    b.pop();
                }
            }
        }
        a = temp;
    }
}

/*
 *  Helper function that returns std::queue of
 *  document names of keyword
 */
std::queue<std::string> SearchEngine::search(std::string keyword)
{
    std::queue<std::string> s;

    if (findItem(keyword))
    {
        int index = hash(keyword);
        item *itemPtr = HashTable[index];
        doc *docPtr;

        do
        {
            if (itemPtr->name == keyword)
            {
                docPtr = itemPtr->id;
                do
                {
                    s.push(docPtr->name);
                    docPtr = docPtr->next;
                } while (docPtr != NULL);
            }
            itemPtr = itemPtr->next;
        } while (itemPtr != NULL);
    }

    return s;
}

/*
 *  Prints out hash table and all times
 */
void SearchEngine::printTable()
{
    int num;
    for (int i = 0; i < tableSize; i++)
    {
        num = numIndex(i);
        std::cout << "---------------\n";
        std::cout << "index = " << i << std::endl;
        std::cout << HashTable[i]->name << std::endl;
        std::cout << "# of items = " << num << std::endl;
        std::cout << "---------------\n";
    }
}

/*
 *  Finds hash item with largest bucket
 *  and prints out largest count
 */
void SearchEngine::printMax()
{
    int temp;
    int maxIndex = 0;
    int max = 0;
    for (int i = 0; i < tableSize; i++)
    {
        temp = numIndex(i);
        if (temp > max)
        {
            max = temp;
            maxIndex = i;
        }
    }

    item *itemPtr = HashTable[maxIndex];
    std::cout << itemPtr->name << std::endl;
    std::cout << "Count: " << numIndex(maxIndex) << std::endl;
}

/*
 *  Prints all items in hash table index item
 */
void SearchEngine::printItems(int index)
{
    item *itemPtr = HashTable[index];
    doc *docPtr = HashTable[index]->id;

    if (itemPtr->name == "empty")
    {
        std::cout << "index = " << index << " is empty" << std::endl;
    }
    else
    {
        std::cout << "index = " << index << " contains the following items" << std::endl;

        while (itemPtr != NULL)
        {
            std::cout << "---------------\n";
            std::cout << itemPtr->name << std::endl;

            while (docPtr != NULL)
            {
                std::cout << "     ---------------\n";
                std::cout << "      " << docPtr->name << std::endl;
                std::cout << "      " << "Count: " << docPtr->count << std::endl;
                std::cout << "     ---------------\n";

                docPtr = docPtr->next;
            }

            std::cout << "---------------\n";

            itemPtr = itemPtr->next;
            if (itemPtr != NULL)
                docPtr = itemPtr->id;
        }
    }
}

/*
 *  passes document name to function
 *  and returns the document number
 */
int SearchEngine::docNum(std::string name)
{
    for (uint64_t i = 0; i < name.size(); i++)
    {
        if (isalpha(name[i]))
        {
            name[i] = ' ';
        }
    }

    int q = atoi(name.c_str());

    return q;
}

/*
 *  Hash function
 */
int SearchEngine::hash(std::string key)
{
    unsigned int hash = 5381;
    int index;

    for (uint64_t i = 0; i < key.length(); i++)
    {
        hash = (33 * hash) + (int)key[i];
    }

    index = hash % tableSize;

    return index;
}