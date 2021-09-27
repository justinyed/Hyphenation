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

std::map<int, int> indivisible_positions(const char *c){

    std::string list[] = {"qu","tr","br","st","sl","bl","cr","ph","ch","str"};
    int length = list->length();
    string txt = c;
    std::transform(txt.begin(), txt.end(), txt.begin(), ::tolower);
    std::map<int, int> m;

    for (int i = 0; i < length; i++) {
        int found = txt.find(list[i]);

        while (found != string::npos) {
            m[found] = list[i].length();
            found = txt.find(list[i], found + 1);
        }
    }

    return m;
}

char *process(const char *input) {


    std::map<int, int> cluster_positions = indivisible_positions(input);
    int length = strlen(input);

    string org_str = input;
    string new_str = "";

    char current;
    bool does_cur_begin_cluster;

    char next;
    bool does_next_begin_cluster;

    bool is_prev_vowel = false;
    bool is_prev_consonant = false;

    for (int i = 0; i < length; i++){
        current = *(input + i);
        does_cur_begin_cluster = cluster_positions.find(i) != cluster_positions.end();

        // Check if current is a letter, else skip
        if (isalpha(current)) {
            if (isVowel(current)){


                // end
                is_prev_vowel = true;
                is_prev_consonant = false;
            }
            // current isConsonant
            else {
                // check if not a cluster
                if (! (cluster_positions.find(i) != cluster_positions.end())){


                    if (i + 2 < length) {
                        next = *(input + i + 1);
                        does_next_begin_cluster = cluster_positions.find(i + 1) != cluster_positions.end();

                    }
                }
                // current is a cluster
                else {
                    i += cluster_positions[i];

                }
                // end
                is_prev_vowel = false;
                is_prev_consonant = true;
            }

        } else {
            // Not a letter so both must be false
            is_prev_vowel = false;
            is_prev_consonant = false;
        }
    }

    return NULL;
}

