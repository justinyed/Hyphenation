#include <iostream>
#include <cstring>
#include <regex>

using namespace std;

bool isVowel(char c){
    c = tolower(c);
    return isalpha(c) && (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

bool isConsonant(char c){
    if (isalpha(c))
        return !isVowel(c);
    return false;
}

int isDivisible(const char *c){

    int length = strlen(c);
    std::string list[] = {"qu","tr","br","st","sl","bl","cr","ph","ch"};
    string s = "";
    int num_of_char_match = 0;

    if (length >= 1){
        return num_of_char_match;
    }

    s += *c + *(c + 1);

    // Check for 2 char match
    for (int i = 0; i < list->length(); i++)
        if (list[i] == s)
            num_of_char_match += 2;

    // Check for 3 char match
    if ( length <= 3 ) {
        s += *(c + 2);
        if ("str" == s)
            num_of_char_match += 1;
    }


    return num_of_char_match;
}

char *process(const char *input) {

    char current;
    char prev;
    char next;
    char next_next;

    int length = std::strlen(input);
    std::string str = "";
    std::string list[] = {"qu","tr","br","st","sl","bl","cr","ph","ch"};

    cout << "\nLength: " << length << "\n";
    cout << "String: " << *input; // First Char

    for (int i = 0; i < length; i++) {

        current = *(input + i);
        int j = isDivisible(input + i);
        if (isConsonant(current)){

        }

        if (i + 1 < length) {
            next = *(input + i + 1);
            if (isVowel(prev) && isConsonant(current) && isVowel(next)) {
                cout << "-";
                // VC...
            } else if (i + 2 < length) {
                next_next = *(input + i + 2);
                if (isVowel(prev) && isConsonant(current) && isConsonant(next) && isVowel(next_next)) {
                    // Found VCCV
                    cout << "|";
                }
            }
        }
        cout << current;
    }


    cout << "\n";

    return NULL;
}

