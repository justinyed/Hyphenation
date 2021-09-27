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

//std::map<int, int> indivisible_positions(const char *c) {
//
//    std::vector<std::string> indivisible_positions = { };
//    std::string list[] = {"qu", "tr", "br", "st", "sl", "bl", "cr", "ph", "ch", "str"};
//    int length = list->length();
//
//    // convert to lower case
//    string txt = c;
//
//
//
//    for (int i = 0; i < length; i++) {
//        int found = txt.find(list[i]);
//
//        while (found != string::npos) {
//            m[found] = list[i].length();
//            found = txt.find(list[i], found + 1);
//        }
//    }
//
//    return m;
//}




char *process(const char *input) {

    regex vowels("[aeiouy]", std::regex::icase);
    regex consonants("[b-df-hj-np-tv-z]|[\a]", std::regex::icase);
    regex clusters("(qu)|(tr)|(br)|(st)|(sl)|(bl)|(cr)|(ph)|(ch)|(str)", std::regex::icase);

    regex vcv("vcv", std::regex::icase);
    regex vccv("vccv", std::regex::icase);

    const char temp_character = '\a';

    string org_str = input;
    string new_str = input;


    vector<int> found_cluster_positions;
    vector<std::string> found_clusters;

    auto it = std::sregex_iterator(new_str.begin(), new_str.end(), clusters);

    for(; it != std::sregex_iterator(); ++it) {
        found_cluster_positions.push_back(it->position());
        found_clusters.push_back(it->str());
    }










    // Create Abstract String
    string abs_str = input;
    abs_str = regex_replace(abs_str, vowels, "a");
    abs_str = regex_replace(abs_str, consonants, "b");

//    cout << abs_str << "\n";



    return NULL;
}

