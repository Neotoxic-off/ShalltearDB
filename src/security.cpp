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

std::string Security::Encode(const std::string &data)
{
    std::stringstream stream;

    stream << std::hex << std::setfill('0');
    for (unsigned char c : data) {
        stream << std::setw(2) << static_cast<int>(c);
    }

    return (stream.str());
}

std::string Security::Decode(const std::string &data)
{
    std::string decoded;
    unsigned char byte = 0;

    for (size_t i = 0; i < data.length(); i += 2) {
        std::string byteString = data.substr(i, 2);
        byte = static_cast<unsigned char>(std::stoul(byteString, nullptr, 16));
        decoded.push_back(byte);
    }

    return (decoded);
}
