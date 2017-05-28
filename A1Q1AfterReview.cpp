#include <iostream>
#include <cstring>
#include <vector>
#define DIM 127

using namespace std;

bool isStringPrintable(string &s){
    for(int i = 0; i < s.length(); ++i){
        if(s[i] < ' ' || s[i] > '~') return false;
    }
    return true;
}

void toLowerS(string &s){
    //all upper case characters in the string s are converted to lower case
    int length = s.length();
    for(int i = 0; i < length; ++i){
        if('A' <= s[i] && s[i] <= 'Z')
            s[i] = tolower(s[i]);
    }
}

void characterHistogram(string &s, vector <int> &letterCount){
    for(int i = 0; i < s.length(); ++i){
            letterCount[(int)s[i]]++;
    }
}

bool permutations(string s1, string s2){
    //v1[i] and v2[i] will retain the number of occurrences of the character with ASCII code i in s1, and s2 respectively
    vector <int> letterCount1(DIM, 0), letterCount2(DIM, 0);
    if(s1.length() != s2.length()) return false;
    toLowerS(s1); toLowerS(s2);
    characterHistogram(s1, letterCount1); characterHistogram(s2, letterCount2);
    for(char c = ' '; c < '~'; ++c){
        if(letterCount1[(int)c] != letterCount2[(int)c]) return false;
    }
    return true;
}

string toString(bool b){
    //convert a boolean to string for printing
    if (b) return "True";
    else "False";
}

int main()
{
    string s1, s2;
    cin>>s1; cin>>s2;
    if(isStringPrintable(s1) && isStringPrintable(s2)) {
        cout<<toString(permutations(s1, s2))<<"\n";
    }
    else {
        cout<<"Input is invalid\n";
    }
    return 0;
}
