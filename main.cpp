#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <cassert>

#include "base64.h"

void test_string_encoding()
{
    std::map<std::string, std::string> tests = {
        {"ABC", "QUJD"},
        {"hello", "aGVsbG8="},
        {"hello world!", "aGVsbG8gd29ybGQh"},
        {"", ""},
        {"a", "YQ=="},
        {"ab", "YWI="},
    };

    for (auto [input, expected] : tests)
        assert(Base64::encode(input) == expected);
}

void test_vector_encoding()
{
    std::vector<std::pair<std::vector<unsigned char>, std::string>> tests = {
        {{'A', 'B', 'C'}, "QUJD"},
        {{'h', 'e', 'l', 'l', 'o'}, "aGVsbG8="},
        {{'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!'}, "aGVsbG8gd29ybGQh"},
        {{}, ""},
        {{'a'}, "YQ=="},
        {{'a', 'b'}, "YWI="}};

    for (auto [input, expected] : tests)
        assert(Base64::encode(input) == expected);
}

void test_vector_decoding()
{
    std::vector<std::pair<std::string, std::vector<unsigned char>>> tests = {
        {"QUJD", {'A', 'B', 'C'}},
        {"aGVsbG8=", {'h', 'e', 'l', 'l', 'o'}},
        {"aGVsbG8gd29ybGQh", {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!'}},
        {"", {}},
        {"YQ==", {'a'}},
        {"YWI=", {'a', 'b'}},
        {"AQIDBAU=", {1, 2, 3, 4, 5}}};

    for (auto [input, expected] : tests)
        assert(Base64::decode(input) == expected);
}

void run_all_tests()
{
    test_string_encoding();
    test_vector_encoding();
    test_vector_decoding();
    std::cout << "All tests passed!\n";
}

int main()
{
    run_all_tests();
}