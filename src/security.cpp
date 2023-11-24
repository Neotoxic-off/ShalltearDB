#include "security.hpp"

Security::Security()
{

}

Security::~Security()
{

}

void Security::XOR(std::vector<char> &data, const std::string &key)
{
    size_t keyIndex = 0;

    for (char &byte : data) {
        byte ^= key[keyIndex];
        keyIndex = (keyIndex + 1) % key.size();
    }
}
