//
//  SearchEngine.h
//  SearchEngineTable
//
//  Created by Nino Aguilar - A01875439 on 3/16/15.
//  Copyright (c) 2015 Nino Aguilar. All rights reserved.
//

#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <iostream>
#include <string>
#include <queue>

class SearchEngine
{

  private:
    static const int tableSize = 1999;

    /* 
     * Used to store document information 
     */
    struct doc
    {
        std::string name;
        int count;
        doc *next;
    };

    /*
     * Used to store information about word being searched
     */
    struct item
    {
        std::string name;
        doc *id;
        item *next;
    };

    item *HashTable[tableSize];

  public:
    SearchEngine();
    int hash(std::string key);
    void addItem(std::string name, std::string docName);
    int numIndex(int index);
    bool findItem(std::string name);
    bool findDoc(std::string name, std::string docName);
    std::queue<std::string> search(std::string keyword);
    void AND(std::queue<std::string> &a, std::queue<std::string> b);
    void OR(std::queue<std::string> &a, std::queue<std::string> b);
    void Search(std::string keyword);
    void printTable();
    void printItems(int index);
    void printMax();
    int docNum(std::string name);
};

#endif /* defined(SearchEngine_H) */
