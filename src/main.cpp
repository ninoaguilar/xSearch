//
//  main.cpp
//  hashTable
//
//  Created by Nino Aguilar - A01875439 on 3/16/15.
//  Copyright (c) 2015 Nino Aguilar. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <chrono>
#include <thread>
#include "searchengine.h"

void f()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

SearchEngine parseStopWords(std::string stopWordsFile)
{
    std::string text;
    SearchEngine stopWords;

    std::ifstream fileIn(stopWordsFile);

    if (fileIn.fail())
    {
        std::cout << "Error: could not open file\n";
    }

    while (getline(fileIn, text))
    {
        stopWords.addItem(text, "stopwords.txt");
    }

    fileIn.close();

    return stopWords;
}

int main()
{
    std::cout << "███████╗███████╗ █████╗ ██████╗  ██████╗██╗  ██╗\n";
    std::cout << "██╔════╝██╔════╝██╔══██╗██╔══██╗██╔════╝██║  ██║\n";
    std::cout << "███████╗█████╗  ███████║██████╔╝██║     ███████║\n";
    std::cout << "╚════██║██╔══╝  ██╔══██║██╔══██╗██║     ██╔══██║\n";
    std::cout << "███████║███████╗██║  ██║██║  ██║╚██████╗██║  ██║\n";
    std::cout << "╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝\n";

    std::cout << "By: Nino Aguilar" << std::endl
              << std::endl;

    std::string searchTerms;

    /*
     * Open stopwords file and adds words to hash table
     */
    SearchEngine stopWords = parseStopWords("../src/stopwords.txt");

    //Variables for creating file names
    std::string doc = "cranfield00";
    int docNum = 1;
    std::string ext = ".txt";
    std::ostringstream oss;
    std::string textFile;
    std::string fileAddress;
    const int NUM_DOCUMENTS = 50; //Number of documents that are being read in

    //Variables for reading in words from files
    std::string line;
    std::string word;

    //Variables for seach engine hash table
    SearchEngine searchEngine;

    /*
     *  Concatinates file name variables
     *  and loops to create all file names
     */
    while (docNum <= NUM_DOCUMENTS)
    {
        oss.str("");

        //text file name concatination
        oss << doc << std::setfill('0') << std::setw(2) << docNum;
        docNum++;

        // passes file name concatination to variable
        textFile = oss.str();

        // concatinates variables to create file address
        fileAddress = "../src/TextDocuments/" + textFile + ext;

        //Opens text files
        std::ifstream fin2(fileAddress);

        if (fin2.fail())
        {
            std::cout << "Error: could not open file\n";
        }
        else
        {
            while (getline(fin2, line))
            {
                for (uint64_t i = 0; i < line.size(); i++)
                {
                    if (!isalpha(line[i]) || isupper(line[i]))
                    {
                        if (line[i] != '-') line[i] = ' ';
                    }
                }

                //Used to loop through single words after using getline
                std::istringstream iss(line);

                while (iss >> word)
                {
                    //Looks for word in stopwords file and doesn't add if found
                    if (!stopWords.findItem(word) && word.size() > 2 && word != "and" && word != "or")
                    {
                        searchEngine.addItem(word, textFile);
                    }
                }
            }
        }

        fin2.close();
        fin2.clear();
    }

    while (searchTerms != "quit")
    {
        std::cout << std::endl;
        std::cout << "------------------------------" << std::endl;
        std::cout << "Enter search term: ";
        std::getline(std::cin, searchTerms);
        std::cout << "------------------------------\n";

        auto t1 = std::chrono::high_resolution_clock::now();
        searchEngine.Search(searchTerms);
        auto t2 = std::chrono::high_resolution_clock::now();

        std::cout << std::endl;
        std::cout << " -- search took 0."
                  << std::setw(3) << std::setfill('0')
                  << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()
                  << " milliseconds --\n";
    }

    return 0;
}