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

int kmp_match(std::string our_strings, std::string pattern) {
    auto map = faillure_function(pattern);
    map[0] = 0;

    int i = 0;
    int j = 0;
    while (i < our_strings.length()) {
        if (our_strings[i] == pattern[j]) {
            if (j == pattern.length() - 1) {
                return i - pattern.length() + 1;
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
