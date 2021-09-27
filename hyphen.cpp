#include <iostream>
#include <cstring>
#include <regex>

using namespace std;

// Forward Declaration
bool isVowel(char c);
bool isConsonant(char c);
string generate_abstract(string s);
string unload_clusters(string str);
string load_clusters(string str, vector<string> found_clusters);
vector<std::string> generate_cluster_vector (string str);
char * convert_to_c_string(std::string s);


// CONSTANTS
const string SYM = "*";
const string SYMBOLIC_VOWEL = "a";
const string SYMBOLIC_CONSONANT = "b";
const string SYMBOLIC_PATTERN_VCV = "(" + SYMBOLIC_VOWEL+ SYMBOLIC_CONSONANT+ SYMBOLIC_VOWEL + ")";
const string SYMBOLIC_PATTERN_VCCV = "(" + SYMBOLIC_VOWEL+ SYMBOLIC_CONSONANT+ SYMBOLIC_CONSONANT + SYMBOLIC_VOWEL + ")";
const char DELIMITER = '-';

const regex REGEX_SYMBOL("[" + SYM + "]");
const regex REGEX_VOWELS("[aeiouy]", std::regex::icase);
const regex REGEX_CONSONANTS("[b-df-hj-np-tv-z]|[" + SYM + "]", std::regex::icase);
const regex REGEX_CLUSTERS("(qu)|(tr)|(br)|(st)|(sl)|(bl)|(cr)|(ph)|(ch)|(str)", std::regex::icase);

const regex REGEX_PATTERN_VCV(SYMBOLIC_PATTERN_VCV, std::regex::icase);
const regex REGEX_PATTERN_VCCV(SYMBOLIC_PATTERN_VCCV, std::regex::icase);


char *process(const char *input) {

    string org_str = input;
    string new_str = unload_clusters(org_str);
    string abs_str = generate_abstract(new_str);
    vector<std::string> clusters = generate_cluster_vector (org_str);





    string str = abs_str;
    vector<int> positions;
    auto it = std::sregex_iterator(str.begin(), str.end(), REGEX_PATTERN_VCCV);
    for (; it != std::sregex_iterator(); ++it) {
        positions.push_back(it->position() + 2);
    }

    for (int i = 0; i < positions.size(); i++){
        new_str.insert(positions[i], 1, DELIMITER);
    }

    return convert_to_c_string(load_clusters(new_str, clusters));
}

char* convert_to_c_string(std::string s){
    // Dynamically allocate memory for the returned string
    char* ptr = new char[s.size() + 1]; // +1 for terminating NUL

    // Copy source string in dynamically allocated string buffer
    strcpy(ptr, s.c_str());

    // Return the pointer to the dynamically allocated buffer
    return ptr;
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

string unload_clusters(string str){
    return std::regex_replace(str, REGEX_CLUSTERS, SYM);
}

string load_clusters(string str, vector<string> found_clusters){
    for (int i = 0; i < found_clusters.size(); i++)
        str = std::regex_replace(str, REGEX_SYMBOL, found_clusters[i], std::regex_constants::format_first_only);
    return str;
}

vector<std::string> generate_cluster_vector (string str){
    vector<std::string> found_clusters;
    auto it = std::sregex_iterator(str.begin(), str.end(), REGEX_CLUSTERS);

    for(; it != std::sregex_iterator(); ++it) {
        found_clusters.push_back(it->str());
    }
    return found_clusters;
}

string generate_abstract(string s) {
    s = regex_replace(s, REGEX_VOWELS, SYMBOLIC_VOWEL);
    return regex_replace(s, REGEX_CONSONANTS, SYMBOLIC_CONSONANT);
}