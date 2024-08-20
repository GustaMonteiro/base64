#include "base64.h"

#include <sstream>

static std::string byte_to_bit_string(unsigned char byte)
{
    std::stringstream ss;

    for (int i = 7; i >= 0; i--)
        ss << (int)((byte >> i) & 1);

    return ss.str();
}

template <typename T>
static std::string internal_base64_encode(T input)
{
    int number_of_bits = input.size() * 8;
    int missing_bits = number_of_bits % 6;

    std::stringstream bit_string;
    for (auto byte : input)
        bit_string << byte_to_bit_string(byte);

    if (missing_bits)
        for (missing_bits = 6 - missing_bits; missing_bits--;)
            bit_string << '0';

    std::string final_bit_string = bit_string.str();

    std::stringstream encoded;

    for (int i = 0; i < final_bit_string.size(); i += 6)
        encoded << Base64::characters[std::stoi(final_bit_string.substr(i, 6), nullptr, 2)];

    std::string encoded_string = encoded.str();
    int missing_chars = encoded_string.size() % 4;

    if (missing_chars)
        for (missing_chars = 4 - missing_chars; missing_chars--;)
            encoded_string += '=';

    return encoded_string;
}

std::string Base64::encode(const std::string &input)
{
    return internal_base64_encode(input);
}

std::string Base64::encode(const std::vector<unsigned char> &input)
{
    return internal_base64_encode(input);
}

std::vector<unsigned char> Base64::decode(const std::string &encoded)
{
    std::string input = encoded.substr(0, encoded.find_last_not_of('=') + 1);

    std::stringstream recovered_bit_stream;

    for (auto byte : input)
        recovered_bit_stream << byte_to_bit_string(Base64::characters.find(byte)).substr(2);

    std::string recovered_bit_string = recovered_bit_stream.str();

    int excess_bytes = recovered_bit_string.size() % 8;
    if (excess_bytes)
        recovered_bit_string = recovered_bit_string.substr(0, recovered_bit_string.size() - excess_bytes);

    std::vector<unsigned char> original_bytes;

    for (int i = 0; i < recovered_bit_string.size(); i += 8)
        original_bytes.push_back(std::stoi(recovered_bit_string.substr(i, 8), nullptr, 2));

    return original_bytes;
}

const std::string Base64::characters =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";