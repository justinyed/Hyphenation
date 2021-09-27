#include <iostream>
#include <cstring>
#include <regex>

using namespace std;

// CONSTANTS
const string SYM = "*";

const regex REGEX_SYMBOL("[" + SYM + "]");
const regex REGEX_VOWELS("[aeiouy]", std::regex::icase);
const regex REGEX_CONSONANTS("[b-df-hj-np-tv-z]|[" + SYM + "]", std::regex::icase);
const regex REGEX_CLUSTERS("(qu)|(tr)|(br)|(st)|(sl)|(bl)|(cr)|(ph)|(ch)|(str)", std::regex::icase);

const regex REGEX_PATTERN_VCV("vcv", std::regex::icase);
const regex REGEX_PATTERN_VCCV("vccv", std::regex::icase);

string unload_clusters(string str){
    return std::regex_replace(str, REGEX_CLUSTERS, SYM);
}

string load_clusters(string str, vector<string> found_clusters){
    for (int i = 0; i < found_clusters.size(); i++)
        str = std::regex_replace(str, REGEX_SYMBOL, found_clusters[i], std::regex_constants::format_first_only);
    return str;
}

char *process(const char *input) {

    string org_str = input;
    string new_str = input;


    // Generate Cluster vectors
    vector<int> found_cluster_positions;
    vector<std::string> found_clusters;

    auto it = std::sregex_iterator(new_str.begin(), new_str.end(), REGEX_CLUSTERS);

    for(; it != std::sregex_iterator(); ++it) {
        found_cluster_positions.push_back(it->position());
        found_clusters.push_back(it->str());
    }

    cout << "\nOriginal:\t" << new_str;

    // Unload REGEX_CLUSTERS from string replace with REGEX_SYMBOL

    new_str = unload_clusters(new_str);
    cout << "\nUnloaded:\t" << new_str;

    // Generate Abstract String
    string abs_str = input;
    abs_str = regex_replace(new_str, REGEX_VOWELS, "a");
    abs_str = regex_replace(abs_str, REGEX_CONSONANTS, "b");




    // Reload REGEX_CLUSTERS from vectors into string.
    new_str = load_clusters(new_str, found_clusters);
    cout << "\nReloaded:\t" << new_str << "\n";



    cout << abs_str << "\n";



    return NULL;
}

bool isVowel(char c) {
    c = tolower(c);
    return isalpha(c) && (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

bool isConsonant(char c) {
    if (isalpha(c))
        return !isVowel(c);
    return false;
}