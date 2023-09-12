/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()){
        while (getline(wordsFile, word)){
            string sortedWord = word;
            std::sort(sortedWord.begin(), sortedWord.end());
            dict[sortedWord].push_back(word);
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (string word : words){
        string sortedWord = word;
        std::sort(sortedWord.begin(), sortedWord.end());
        dict[sortedWord].push_back(word);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    vector<string> anags;
    std::string key = word;
    std::sort(key.begin(), key.end());
    if (dict.find(key) != dict.end()){
        for (auto trav : dict.find(key)->second){
           anags.push_back(trav);
        }
    }
    return anags;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> anags;
    for (auto keys : dict){
        vector<string> anag;
        if (keys.second.size() < 2) continue;
        for (auto words : keys.second){
            anag.push_back(words);
        }
        anags.push_back(anag);
    }
    return anags;
}
