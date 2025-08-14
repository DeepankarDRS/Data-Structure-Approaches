# C++ String Cheat Sheet (Interview Quick-Ref)

Covers std::string (C++ STL) + C-Strings (char[]) in one place.
1. String Types

| Type          | Description               | Example                   |
| ------------- | ------------------------- | ------------------------- |
| `std::string` | Safe, flexible, dynamic   | `string s = "Hello";`     |
| `char[]`      | Fixed size, C-style       | `char c[10] = "Hi";`      |
| `const char*` | Pointer to string literal | `const char* p = "Test";` |
'''
    string s1 = "Hello";               // std::string (safe)
    char c1[] = "Hello";               // C-string (mutable)
    const char* p1 = "Hello";          // C-string literal (read-only)
'''

# 2. Constructors
3. string s1;                  // empty
string s2("Hello");         // from const char*
string s3(5, 'x');          // "xxxxx"
string s4(s2);              // copy
string s5(s2, 1, 3);        // "ell"
# basic info
| Function              | Purpose            | Example             |
| --------------------- | ------------------ | ------------------- |
| `size()` / `length()` | Get length         | `s.size()` → 5      |
| `empty()`             | Check if empty     | `if(s.empty())`     |
| `capacity()`          | Current alloc size | `s.capacity()`      |
| `shrink_to_fit()`     | Free unused mem    | `s.shrink_to_fit()` |
# access
s[0]       // char by index (no bounds check)
s.at(2)    // char with bounds check
s.front()  // first char
s.back()   // last char
# modifiers
| Function               | Action      | Example                |
| ---------------------- | ----------- | ---------------------- |
| `append(str)`          | Add end     | `s.append("abc");`     |
| `operator+`            | Concatenate | `s = s + "abc";`       |
| `push_back(c)`         | Add char    | `s.push_back('x');`    |
| `insert(pos,str)`      | Insert      | `s.insert(2,"YY");`    |
| `erase(pos,len)`       | Remove      | `s.erase(1,3);`        |
| `replace(pos,len,str)` | Replace     | `s.replace(1,3,"hi");` |
| `clear()`              | Empty       | `s.clear();`           |
| `pop_back()`           | Remove last | `s.pop_back();`        |

# find/search
| Function                   | Finds                | Example                      |
| -------------------------- | -------------------- | ---------------------------- |
| `find(str)`                | First match          | `s.find("lo")`               |
| `rfind(str)`               | Last match           | `s.rfind("l")`               |
| `find_first_of(chars)`     | Any of set           | `s.find_first_of("aeiou")`   |
| `find_last_of(chars)`      | Any of set (reverse) | `s.find_last_of("aeiou")`    |
| `find_first_not_of(chars)` | First not in set     | `s.find_first_not_of("abc")` |

string s = "Hello World";
if(s.find("World") != string::npos) cout << "Found!\n";
## Best Use: Always compare with string::npos to check "not found".

# substring
string sub = s.substr(pos, len);
    string s = "Interview";
    cout << s.substr(0,5); // Inter
Best Use: Great for extracting tokens after parsing.
# compare
s.compare(s2) // returns 0 if equal
if(s.compare("Hello") == 0) cout << "Match!";
Best Use: Works well for lexicographic sorting.
# conversion
    stoi("123");       // → int 123
    stof("3.14");      // → float
    to_string(123);    // → "123"
#  cstring interop
| Function  | Purpose            | Example                    |
| --------- | ------------------ | -------------------------- |
| `c_str()` | Get `const char*`  | `printf("%s", s.c_str());` |
| `data()`  | Get buffer pointer | `auto p = s.data();`       |
# common function
| Function          | Purpose        |
| ----------------- | -------------- |
| `strlen(s)`       | Length         |
| `strcpy(dst,src)` | Copy           |
| `strcat(a,b)`     | Append         |
| `strcmp(a,b)`     | Compare        |
| `strchr(s,c)`     | Find char      |
| `strstr(s,sub)`   | Find substring |
    Best Use: Only in low-level code; prefer std::string otherwise.
# case & utlis
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    reverse(s.begin(), s.end());




