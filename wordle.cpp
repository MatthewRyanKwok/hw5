#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void makeWords(std::string currWord,std::string floating, const std::set<std::string>& dict, std::set<std::string>& res, size_t ind);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> res;
    makeWords(in, floating, dict, res, 0); //recursion starts at idx 0
    return res;
}

// Define any helper functions here

void makeWords(std::string currWord, std::string floating, const std::set<std::string>& dict, std::set<std::string>& res, size_t ind)
{
    if (ind == currWord.size()) { //base case is if reached the end of the word
        if (floating.empty() && dict.find(currWord) != dict.end()) {
            res.insert(currWord);
        }
        return;
    }

    if (currWord[ind] != '-') { //if curr pos is filled, move on
        makeWords(currWord, floating, dict, res, ind + 1);
        return;
    }
    /*
    for (char ch = 'a'; ch <= 'z'; ch++) {
        currWord[ind] = ch; */

    size_t remainingDashes = 0; //if remaining blanks < floating letters, can't place all of them
    for (size_t i = ind; i < currWord.size(); ++i) {
        if (currWord[i] == '-') remainingDashes++;
    }
    if (remainingDashes < floating.size()) return;

    //try placing unused floating chars at pos
    std::set<char> tried;
    for (size_t i = 0; i < floating.size(); ++i) {
        char ch = floating[i];
        if (tried.count(ch)) continue; //skips repeated chars
        tried.insert(ch);

        currWord[ind] = ch;
        std::string newFloating = floating;
        newFloating.erase(newFloating.find(ch), 1); //remove used floating char
        makeWords(currWord, newFloating, dict, res, ind + 1); //recurse with new word
    }

   
    for (char ch = 'a'; ch <= 'z'; ++ch) { //try all other chars after recursing
        if (floating.find(ch) != std::string::npos) continue; //skip the floating letters
        currWord[ind] = ch;
        makeWords(currWord, floating, dict, res, ind + 1);
    }

    currWord[ind] = '-';
}