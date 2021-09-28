#include <iostream>
#include <cstring>
#include <regex>

using namespace std;

// Forward Declaration
string delimit_VCCV(string str);

string delimit_VCV(string s);

string generate_abstract(string s, bool isVCV = false);

string unload_clusters(const string &str);

string load_clusters(string str, const vector<string> &found_clusters);

vector<std::string> generate_cluster_vector(string str);

char *convert_to_c_string(const std::string &s);


// CONSTANTS
const char DELIMITER = '-';

const string SYM = "*";
const string SYMBOLIC_VOWEL = "a";
const string SYMBOLIC_CONSONANT = "b";
const string SYMBOLIC_PATTERN_VCV = "(" + SYMBOLIC_VOWEL + SYMBOLIC_CONSONANT + SYMBOLIC_VOWEL + ")";
const string SYMBOLIC_PATTERN_VCCV =
        "(" + SYMBOLIC_VOWEL + SYMBOLIC_CONSONANT + SYMBOLIC_CONSONANT + SYMBOLIC_VOWEL + ")";

const regex REGEX_SYMBOL("[" + SYM + "]");
const regex REGEX_VOWELS("[aeiouy]", std::regex::icase);
const regex REGEX_CONSONANTS("[b-df-hj-np-tv-z]|[" + SYM + "]", std::regex::icase);
const regex REGEX_CLUSTERS("(str)|(qu)|(tr)|(br)|(st)|(sl)|(bl)|(cr)|(ph)|(ch)", std::regex::icase);
const regex REGEX_PATTERN_VCV(SYMBOLIC_PATTERN_VCV, std::regex::icase);
const regex REGEX_PATTERN_VCCV(SYMBOLIC_PATTERN_VCCV, std::regex::icase);


char *process(const char *input) {

    string org_str = input;
    string new_str = unload_clusters(org_str);

    vector<std::string> clusters = generate_cluster_vector(org_str);

    new_str = delimit_VCCV(new_str);
    new_str = delimit_VCCV(new_str);
    new_str = delimit_VCV(new_str);
    new_str = delimit_VCV(new_str);


    return convert_to_c_string(load_clusters(new_str, clusters));
}

char *convert_to_c_string(const std::string &s) {
    // Dynamically allocate memory for the returned string
    char *ptr = new char[s.size() + 1]; // +1 for terminating NUL

    // Copy source string in dynamically allocated string buffer
    strcpy(ptr, s.c_str());

    // Return the pointer to the dynamically allocated buffer
    return ptr;
}

string unload_clusters(const string &str) {
    return std::regex_replace(str, REGEX_CLUSTERS, SYM);
}

string load_clusters(string str, const vector<string> &found_clusters) {
    for (auto &found_cluster: found_clusters)
        str = std::regex_replace(str, REGEX_SYMBOL, found_cluster, std::regex_constants::format_first_only);
    return str;
}

vector<std::string> generate_cluster_vector(string str) {
    vector<std::string> found_clusters;
    auto it = std::sregex_iterator(str.begin(), str.end(), REGEX_CLUSTERS);

    for (; it != std::sregex_iterator(); ++it) {
        found_clusters.push_back(it->str());
    }
    return found_clusters;
}

string generate_abstract(string s, bool isVCV) {
    if (isVCV) {
        s = regex_replace(s, regex("(e(?=[\\s]))", std::regex::icase), "\b");
    }
    s = regex_replace(s, REGEX_VOWELS, SYMBOLIC_VOWEL);
    return regex_replace(s, REGEX_CONSONANTS, SYMBOLIC_CONSONANT);
}

string delimit_VCCV(string s) {
    string str = generate_abstract(s);

    vector<int> positions;
    auto it = std::sregex_iterator(str.begin(), str.end(), REGEX_PATTERN_VCCV);

    for (; it != std::sregex_iterator(); ++it) {
        positions.push_back(it->position());
    }

    int j = 0;
    for (int position: positions) {
        s.insert(position + 2 + j++, 1, DELIMITER);
    }
    return s;
}

string delimit_VCV(string s) {
    string str = generate_abstract(s, true);

    vector<int> positions;
    auto it = std::sregex_iterator(str.begin(), str.end(), REGEX_PATTERN_VCV);

    for (; it != std::sregex_iterator(); ++it) {
        positions.push_back(it->position());
    }

    int j = 0;
    for (int position: positions) {
        s.insert(position + 1 + j++, 1, DELIMITER);
    }
    return s;
}