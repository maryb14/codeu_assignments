#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Dictionary {
    //implementation with prefix trees
private:
    static const unsigned int EnglishChars = 27;
    struct Trie {
        bool hasWord; //is true if there is word finishing at this node in the trie
        vector <Trie*> children; //list of children, one for each letter of the English alphabet
        Trie() {
            hasWord = false;
            children.resize(EnglishChars);
        }
    };
    Trie *root;
    int charToIndex(char ch) {
        return (ch - 'A');
    }
    void deleteTrie(Trie *current){
        for(int i = 0; i < EnglishChars; ++i){
            if(current -> children[i] != NULL){
                deleteTrie(current -> children[i]);
            }
        }
        delete current;
    }
public:
    Dictionary(){
        root = new Trie;
    }
    ~Dictionary() {
        deleteTrie(root);
    }
    void addWord(string word){
        Trie *iter = root;
        for(int i = 0; i < word.length(); ++i){
            int index = charToIndex(word[i]);
            if(iter -> children[index] == NULL){
                iter -> children[index] = new Trie;
            }
            iter = iter -> children[index];
        }
        iter -> hasWord = true;
    }
    bool isPrefix(string input){
        Trie *iter = root;
        int i = 0;
        while(i < input.length() && iter -> children[charToIndex(input[i])] != NULL){
            iter = iter -> children[charToIndex(input[i])];
            i += 1;
        }
        return (i == input.length());
    }
    bool isWord(string input){
        Trie *iter = root;
        int i = 0;
        while(i < input.length() && iter -> children[charToIndex(input[i])] != NULL){
            iter = iter -> children[charToIndex(input[i])];
            i += 1;
        }
        return (i == input.length() && iter -> hasWord);
    }
};

class Grid {
public:
    int rows, columns;
    vector < vector<char> > elems; //contains the characters from the grid
    Grid(){
        rows = 0; columns = 0;
        elems.clear();
    }
    void allocateGrid(int r, int c){
        rows = r; columns = c;
        elems.resize(r);
    }
};

class StringSet {
    //contains a set of the string we found
    //implementation with hashTables as number of words is large and some could be found multiple times
private:
    static const int primeForHash = 666013;
    vector < vector <string> > hashTable;
public:
    StringSet() {
        hashTable.clear();
        hashTable.resize(primeForHash);
    }
    void addWord(string input){
        unsigned int hashValue = hashFunction(input);
        if(!isInHash(input, hashValue)){
            hashTable[hashValue].push_back(input);
        }
    }
    void getWords(vector <string> &listOfWords){
        for(int i = 0; i < hashTable.size(); ++i){
            listOfWords.insert(listOfWords.begin(), hashTable[i].begin(), hashTable[i].end());
        }
    }
private:
    unsigned int hashFunction(string &s){
        unsigned int h = 5381;
        for(int i = 0; i < s.length(); ++i){
            h = h * 31 + (s[i] - 'A');
        }
        return (h % 666013);
    }
    bool isInHash(string &s, int hashValue){
        int i = 0;
        while(i < hashTable[hashValue].size() && s.compare(hashTable[hashValue][i]) != 0){
            i += 1;
        }
        return (i < hashTable[hashValue].size());
    }
};

StringSet solution;

Dictionary dict;

Grid inputGrid;

vector < vector <bool> > passed; //array used in solution - to remember which cells we've been through

void getInputForDictionary() {
    //dictionary input is assumed valid
    ifstream infile("dictionary.in");
    int numberWords;
    string s;
    infile>>numberWords;
    infile.get();
    for(int i = 0; i < numberWords; ++i){
        getline(infile, s);
        dict.addWord(s);
    }
    infile.close();
}

void getGridInput(){
    //grid input is assumed to contain only English characters
    //lowercase letter are capitalized to correspond with the dictionary
    ifstream infile("grid.in");
    int rows, columns;
    char nextChar;
    infile>>rows>>columns;
    infile.get();
    inputGrid.allocateGrid(rows, columns);
    passed.resize(rows);
    for(int i = 0; i < inputGrid.rows; ++i){
        for(int j = 0; j < inputGrid.columns; ++j){
            infile>>nextChar;
            toupper(nextChar);
            inputGrid.elems[i].push_back(nextChar);
            passed[i].push_back(false);
        }
        infile.get();
    }
    infile.close();
}

void solveFromPosition(int r, int c, string &tempString){
    passed[r][c] = true;
    tempString += inputGrid.elems[r][c];
    if(dict.isPrefix(tempString)){
        passed[r][c] = true;
        if(dict.isWord(tempString)){
            solution.addWord(tempString);
        }
        //check the 8 neighbours of the cell, if they fit in the grid
        for(int i = (r - 1 > 0)?(r - 1):0; i <= r + 1 && i < inputGrid.rows; ++i){
            for(int j = (c - 1 > 0)?(c - 1):0; j <= c + 1 && j < inputGrid.columns; ++j){
                if(!passed[i][j]){
                    solveFromPosition(i, j, tempString);
                }
            }
        }
    }
    passed[r][c] = false;
    tempString.erase(tempString.length() - 1);
}

void solveGrid(){
    //solution uses a DFS through the grid
    //we advance to a following position if that position has not been passed through
    //we then check if the string corresponding to the positions we have been through is a prefix
    //if not, we leave the cell immediately
    //if yes, we continue exploration
    string tempString = ""; //string corresponding to the explored positions
    for(int i = 0; i < inputGrid.rows; ++i){
        for(int j = 0; j < inputGrid.columns; ++j){
            solveFromPosition(i, j, tempString);
        }
    }
}

void outputStrings(vector <string> &listOfWords){
    ofstream outfile("answer.out");
    for(int i = 0; i < listOfWords.size(); ++i){
        outfile<<listOfWords[i]<<"\n";
    }
    outfile.close();
}

int main()
{
    vector <string> listOfWords;
    getInputForDictionary();
    getGridInput();
    solveGrid();
    solution.getWords(listOfWords);
    outputStrings(listOfWords);
    return 0;
}

/* Some tests:

dictionary.in:
4
CAR
CARD
CART
CAT

grid.in:

5 5
CARDT
ARCTD
CAARC
CARDT
RRART

words.out:

CART
CARD
CAT
CAR

dictionary.in:

4
CAR
CARD
CART
CAT

grid.in:

2 3
AAR
TCD

answer.out:
CARD
CAT
CAR

dictionary.in:

11
CAR
CARD
CART
CAT
MAMA
ANA
BANANA
UNIVERSITY
RAW
TERM
EXAM

grid.in:

10 10
ARMTCBKVBE
EXAMBVEGRB
UNIVERJAID
NVDBFISCRT
BCJDIFHINC
CIDRNRIRTY
CNENIFBFEB
NDEIFEOABF
BRJGHRIOGG
CNFIEBAIFB

answer.out:

EXAM
CART
CARD
CAR
UNIVERSITY

*/
