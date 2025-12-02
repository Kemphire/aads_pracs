#include <map>
#include <string>

std::map<int, int> faillure_function(std::string pattern) {
    int i = 1;
    int j = 0;

    std::map<int, int> f;
    while (i < pattern.length()) {
        if (pattern[i] == pattern[j]) {
            f[i] = j + 1;
            i++;
            j++;
        } else if (j > 0) {
            j = f[j - 1];
        } else {
            f[i] = 0;
            i++;
        }
    }
    return f;
}

int kmp_match(std::string haystack, std::string needle) {
    auto map = faillure_function(needle);
    map[0] = 0;

    int i = 0;
    int j = 0;
    while (i < needle.length()) {
        if (haystack[i] == needle[j]) {
            if (j == needle.length() - 1) {
                return i - needle.length() + 1;
            }
            i++;
            j++;
        } else if (j > 0) {
            j = map[j - 1];
        } else {
            i++;
        }
    }
    return -1;
}
