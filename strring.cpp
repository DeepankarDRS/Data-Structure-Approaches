/*
    C++ STRING CHEAT SHEET WITH EXAMPLES
    Covers std::string (C++ STL) and C-strings (<cstring>)
    Ready for interview revision + practice
*/

#include <bits/stdc++.h> // For simplicity in example (includes string, cstring, algorithm, etc.)
using namespace std;

int main() {

    /*==============================
      1. CONSTRUCTORS & INITIALIZATION
    ==============================*/
    string s1;                  // Empty string
    string s2("Hello");         // From const char*
    string s3(5, 'x');          // "xxxxx"
    string s4(s2);              // Copy constructor
    string s5(s2, 1, 3);        // "ell" (start=1, length=3)

    cout << "Constructed strings:\n";
    cout << s2 << " | " << s3 << " | " << s5 << "\n\n";

    /*==============================
      2. BASIC INFO
    ==============================*/
    cout << "Length of s2: " << s2.size() << "\n"; // length()
    cout << "Is s1 empty? " << s1.empty() << "\n";
    cout << "Capacity of s2: " << s2.capacity() << "\n";
    s2.shrink_to_fit(); // Reduce unused capacity

    /*==============================
      3. ACCESSING CHARACTERS
    ==============================*/
    cout << "First char of s2: " << s2[0] << "\n";   // No bounds check
    cout << "Third char of s2: " << s2.at(2) << "\n"; // Safe access with bounds check
    cout << "Front: " << s2.front() << ", Back: " << s2.back() << "\n\n";

    /*==============================
      4. MODIFIERS
    ==============================*/
    string mod = "Hello";
    mod.append(" World");             // Append string
    mod.push_back('!');                // Add single char
    mod.insert(5, " C++");              // Insert at position
    mod.erase(5, 4);                    // Erase 4 chars starting pos=5
    mod.replace(6, 5, "Planet");        // Replace from pos=6, len=5
    mod.pop_back();                     // Remove last char
    cout << "Modified string: " << mod << "\n\n";

    /*==============================
      5. SEARCH
    ==============================*/
    string search = "Hello World, Welcome to C++";
    size_t pos = search.find("World");
    if (pos != string::npos) {
        cout << "'World' found at index " << pos << "\n";
    }
    cout << "First vowel at index: " << search.find_first_of("aeiou") << "\n";
    cout << "Last vowel at index: " << search.find_last_of("aeiou") << "\n";
    cout << "First non-abc char at: " << string("aaabbcxyz").find_first_not_of("abc") << "\n\n";

    /*==============================
      6. SUBSTRING
    ==============================*/
    string subs = search.substr(0, 5); // First 5 chars
    cout << "Substring: " << subs << "\n\n";

    /*==============================
      7. COMPARE
    ==============================*/
    string cmp1 = "Apple", cmp2 = "Banana";
    if (cmp1.compare(cmp2) < 0) cout << cmp1 << " comes before " << cmp2 << "\n\n";

    /*==============================
      8. CONVERSIONS
    ==============================*/
    int num = stoi("123");
    float f = stof("3.14");
    string snum = to_string(456);
    cout << "stoi: " << num << ", stof: " << f << ", to_string: " << snum << "\n\n";

    /*==============================
      9. C-STRING INTEROP
    ==============================*/
    string inter = "C++ String";
    const char* cstr1 = inter.c_str(); // Get const char*
    cout << "As C-string: " << cstr1 << "\n";

    /*==============================
      10. C-STRING FUNCTIONS (<cstring>)
    ==============================*/
    char cA[20] = "Hello";
    char cB[] = " World";
    strcat(cA, cB);                    // Append
    cout << "strcat: " << cA << "\n";
    cout << "strlen: " << strlen(cA) << "\n";
    cout << "strcmp(Hello, Hello): " << strcmp("Hello", "Hello") << "\n";
    cout << "strchr: " << strchr(cA, 'W') << "\n"; // Pointer to first 'W'
    cout << "strstr: " << strstr(cA, "World") << "\n"; // Pointer to "World"

    /*==============================
      11. CASE CONVERSION & UTILS
    ==============================*/
    string util = "Case Test";
    transform(util.begin(), util.end(), util.begin(), ::toupper);
    cout << "Uppercase: " << util << "\n";
    transform(util.begin(), util.end(), util.begin(), ::tolower);
    cout << "Lowercase: " << util << "\n";
    reverse(util.begin(), util.end());
    cout << "Reversed: " << util << "\n";

    return 0;
}
// 1. REGEX: Pattern matching in strings
    regex pattern("[A-Z][a-z]+"); // Capitalized word
    string text = "Hello there, My name is ChatGPT";
    cout << "\nRegex matches:\n";
    for (sregex_iterator it(text.begin(), text.end(), pattern), end_it; it != end_it; ++it) {
        cout << " - " << it->str() << "\n";
    }

    // 2. STRINGSTREAM: Converting & parsing
    stringstream ss("123 45.6 Hello");
    int i; float fl; string word;
    ss >> i >> fl >> word;
    cout << "\nParsed via stringstream: " << i << ", " << fl << ", " << word << "\n";

    // 3. SPLITTING STRINGS
    string splitStr = "apple,banana,cherry";
    vector<string> fruits;
    string token;
    stringstream ss2(splitStr);
    while (getline(ss2, token, ',')) {
        fruits.push_back(token);
    }
    cout << "Split result: ";
    for (auto &fruit : fruits) cout << fruit << " ";
    cout << "\n";

    // 4. TRIMMING WHITESPACE
    string trimStr = "   spaced text   ";
    auto ltrim = [](string &s){ s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch){ return !isspace(ch); })); };
    auto rtrim = [](string &s){ s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch){ return !isspace(ch); }).base(), s.end()); };
    ltrim(trimStr); rtrim(trimStr);
    cout << "Trimmed: '" << trimStr << "'\n";

    // 5. EFFICIENT CONCATENATION: ostringstream
    ostringstream oss;
    oss << "Hello " << 123 << " World";
    string built = oss.str();
    cout << "Concatenated via ostringstream: " << built << "\n";

    // 6. CUSTOM SORTING STRINGS
    vector<string> words = {"apple", "Banana", "grape", "Apricot"};
    sort(words.begin(), words.end(), [](const string &a, const string &b){
        string la = a, lb = b;
        transform(la.begin(), la.end(), la.begin(), ::tolower);
        transform(lb.begin(), lb.end(), lb.begin(), ::tolower);
        return la < lb; // case-insensitive sort
    });
    cout << "Case-insensitive sort: ";
    for (auto &w : words) cout << w << " ";
    cout << "\n";

    // 7. RESERVE() for performance
    string perf;
    perf.reserve(1000); // avoid reallocations
    for (int j = 0; j < 100; j++) perf += "x";
    cout << "Perf string size: " << perf.size() << "\n";

    // 8. MOVE SEMANTICS
    string src = "Move me";
    string dest = move(src); // src becomes empty
    cout << "After move, dest: " << dest << ", src: '" << src << "'\n";

    return 0;
}
