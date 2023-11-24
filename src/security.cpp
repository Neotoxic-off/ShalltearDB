#include "security.hpp"

Security::Security()
{

}

Security::~Security()
{

}

std::string Security::XOR(const std::string &data, const std::string &key)
{
    std::string result = data;
    size_t length = key.length();

    for (size_t i = 0; i < data.length(); i++) {
        result[i] ^= key[i % length];
    }

    return (result);
}
