#pragma once

#include <vector>
#include <string>

class Base64
{
public:
    static std::string encode(const std::string &input);
    static std::string encode(const std::vector<unsigned char> &input);
    static std::vector<unsigned char> decode(const std::string &encoded);

private:
    static const std::string characters;

    template <typename T>
    friend std::string internal_base64_encode(T input);
};