#include <iostream>
#include <cstring>
#include <regex>

using namespace std;

bool isVowel(char c) {
    c = tolower(c);
    return isalpha(c) && (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

bool isConsonant(char c) {
    if (isalpha(c))
        return !isVowel(c);
    return false;
}

bool isCluster(std::map<int, int> cluster_positions, int current_position){
    return cluster_positions.find(current_position) != cluster_positions.end();
}

string getCluster(std::map<int, int> cluster_positions, int current_position, const char *c){
    string str = "";
    // Skip past cluster
    int cluster_length = cluster_positions[current_position];
    for (int j = 0; j < cluster_length; j++) {
        str += *(c + j); // I think this is right???
    }
    return str;
}

std::map<int, int> indivisible_positions(const char *c) {

    std::string list[] = {"qu", "tr", "br", "st", "sl", "bl", "cr", "ph", "ch", "str"};
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
    string group = "";

    char previous;
    char current;
    char next;
    char next_next;

    bool is_prev_vowel = false;
    bool is_prev_consonant = false;

    for (int i = 0; i < length; i++) {
        current = *(input + i);

        // Check if current is a letter, else skip
        if (isalpha(current)) {


            if (isVowel(current) && i + 2 < length) {
                // true, then make it previous
                // prev=V
                is_prev_vowel = isVowel(current);
                previous = current;
                group += previous;


                current = *(input + ++i);
                // current=?
                if (isConsonant(current)) {
                    // Check if cluster
                    if (isCluster(cluster_positions, i)) {
                        // Skip past cluster
                        int cluster_length = cluster_positions[i];
                        for (int j = 0; j < cluster_length; j++) {
                            group += *(input + i++); // I think this is right???
                        }
                    }

                    // Check next
                    next = *(input + i + 1);
                    if (isalpha(next)) {

                        if (isVowel(next)) {
                            // vowel = true
                            // found Pattern !!!
                            cout << "pattern found";
                            group += previous + "-" + current + next;
                        } else {
                            // vowel = false; must be consonant
                            // time to check next_next
                            if (i + 3 < length) {
                                next_next = *(input + 3);

                                if (isConsonant(current)) {

                                    // Check if cluster
                                    if (isCluster(cluster_positions, i)) {

                                        // Skip past cluster
//                                        group += getCluster();
                                        int cluster_length = cluster_positions[i];
                                        for (int j = 0; j < cluster_length; j++) {
                                            group += *(input + i++); // I think this is right???
                                        }
                                        // Pattern found
                                    }
                                }
                            }
                        }
                    }


                    // end
                }
            }
        } else {
            // Not a letter so both must be false
            new_str += current;
            is_prev_vowel = false;
            is_prev_consonant = false;
        }

        return NULL;
    }
}

