#include <iostream>
#include <cstring>
#define DIM 127

using namespace std;

bool validInput(string s1, string s2){
    //method for validating input
    //input is valid if both strings contain only printable characters,
    // i.e. with their ASCII code between 32 (' ') and 126 ('~')
    int l1 = s1.length(), l2 = s2.length();
    for(int i = 0; i < l1; ++i){
        if(s1[i] < ' ' || s1[i] > '~') return false;
    }
    for(int i = 0; i < l2; ++i){
        if(s2[i] < ' ' || s2[i] > '~') return false;
    }
    return true;
}

void setTo0(int a[DIM]){
    //sets all the elements of array a to 0
    for(int i = 0; i < DIM; ++i) a[i] = 0;
}

void toLowerS(string &s){
    //all upper case characters in the string s are converted to lower case
    int length = s.length();
    for(int i = 0; i < length; ++i){
        if('A' <= s[i] && s[i] <= 'Z')
            s[i] = tolower(s[i]);
    }
}

bool permutations(string s1, string s2){
    //v1[i] and v2[i] will retain the number of occurrences of the character with ASCII code i in s1, and s2 respectively
    int v1[DIM], v2[DIM];
    int l1 = s1.length(), l2 = s2.length();
    if(l1 != l2) return false;
    setTo0(v1); setTo0(v2);
    toLowerS(s1); toLowerS(s2);
    for(int i = 0; i < l1; ++i){
        v1[(int)s1[i]]++;
    }
    for(int i = 0; i < l2; ++i){
        v2[(int)s2[i]]++;
    }
    for(int i = 32; i < 127; ++i){
        if(v1[i] != v2[i]) return false;
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
    if(validInput(s1, s2)) {
        cout<<toString(permutations(s1, s2))<<"\n";
    }
    else {
        cout<<"Input is invalid\n";
    }
    return 0;
}
