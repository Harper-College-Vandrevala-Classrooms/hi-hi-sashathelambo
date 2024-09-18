#include <iostream>
#include <string>
#include <cctype>
#include <sstream>

// Function to perform case-insensitive comparison of two strings
int strcmp_case_insensitive(const std::string& str1, const std::string& str2, bool skip_spaces = false, int max_chars = -1) {
    auto normalize = [skip_spaces](const std::string& str) {
        std::string result;
        for (char c : str) {
            if (!skip_spaces || !std::isspace(c)) {
                result += std::tolower(c);
            }
        }
        return result;
    };

    auto compare_numbers = [](const std::string& s1, const std::string& s2, size_t& i, size_t& j) {
        size_t start1 = i, start2 = j;
        while (i < s1.length() && std::isdigit(s1[i])) ++i;
        while (j < s2.length() && std::isdigit(s2[j])) ++j;
        int num1 = std::stoi(s1.substr(start1, i - start1));
        int num2 = std::stoi(s2.substr(start2, j - start2));
        if (num1 < num2) return -1;
        if (num1 > num2) return 1;
        return 0;
    };

    std::string norm_str1 = normalize(str1);
    std::string norm_str2 = normalize(str2);

    size_t len1 = norm_str1.length();
    size_t len2 = norm_str2.length();
    size_t min_len = std::min(len1, len2);

    if (max_chars == 0) return 0;
    if (max_chars > 0) min_len = std::min(min_len, static_cast<size_t>(max_chars));

    size_t i = 0, j = 0;
    while (i < min_len && j < min_len) {
        if (std::isdigit(norm_str1[i]) && std::isdigit(norm_str2[j])) {
            int cmp = compare_numbers(norm_str1, norm_str2, i, j);
            if (cmp != 0) return cmp;
        } else {
            if (norm_str1[i] < norm_str2[j]) return -1;
            if (norm_str1[i] > norm_str2[j]) return 1;
            ++i;
            ++j;
        }
    }

    if (max_chars < 0) {
        if (len1 < len2) return -1;
        if (len1 > len2) return 1;
    }

    return 0;
}

// Driver program to test the strcmp_case_insensitive function
int main() {
    std::string str1, str2;

    // Test case 1
    str1 = "string one";
    str2 = "string two";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2) << ".\n";

    // Test case 2
    str1 = "string one";
    str2 = "string one";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2) << ".\n";

    // Test case 3
    str1 = "string two";
    str2 = "string one";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2) << ".\n";

    // Test case 4
    str1 = "Hello";
    str2 = "hello";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2) << ".\n";

    // Test case 5
    str1 = "abc";
    str2 = "abcd";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2) << ".\n";

    // Test case 6
    str1 = "abcd";
    str2 = "abc";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2) << ".\n";

    // Test case 7
    str1 = "my cool string";
    str2 = "mycoolstring";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2, true) << ".\n";

    // Test case 8
    str1 = "My Cool String";
    str2 = "MyCoolString";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2, true) << ".\n";

    // Test case 9
    str1 = "My Cool String";
    str2 = "mycoolstring";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2, true) << ".\n";

    // Test case 10
    str1 = "My Cool String ";
    str2 = "mycoolstring";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2, true) << ".\n";

    // Test case 11
    str1 = " My Cool String";
    str2 = "mycoolstring";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2, true) << ".\n";

    // Test case 12
    str1 = "Another string";
    str2 = "mycoolstring";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2, true) << ".\n";

    // Test case 13
    str1 = "2";
    str2 = "50";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2) << ".\n";

    // Test case 14
    str1 = "2";
    str2 = "10";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2) << ".\n";

    // Test case 15
    str1 = "20";
    str2 = "5";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2) << ".\n";

    // Test case 16
    str1 = "20";
    str2 = "1";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2) << ".\n";

    // Test case 17
    str1 = "100";
    str2 = "100";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2) << ".\n";

    // Test case 18
    str1 = "2 Some String";
    str2 = "50 Some String";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2) << ".\n";

    // Test case 19
    str1 = "2 Some String";
    str2 = "10 Some String";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2) << ".\n";

    // Test case 20
    str1 = "20 Some String";
    str2 = "5 Some String";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2) << ".\n";

    // Test case 21
    str1 = "20 Some String";
    str2 = "1 Some String";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2) << ".\n";

    // Test case 22
    str1 = "100 Some String";
    str2 = "100 Some String";
    std::cout << "The comparison of \"" << str1 << "\" and \"" << str2 << "\" returns " << strcmp_case_insensitive(str1, str2) << ".\n";

    return 0;
}
