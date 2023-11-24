#include "database.hpp"

Database::Database(std::string _key)
{
    this->path = std::string("database.stdb");
    this->key = _key;
    this->security = Security();
}

Database::~Database()
{
    
}

void Database::Insert(std::string id, const std::string value)
{
    data[id] = value;
}

std::string Database::Retrieve(std::string id)
{
    auto it = data.find(id);

    if (it != data.end()) {
        return it->second;
    } else {
        return "Not found";
    }
}

void Database::Update(std::string id, std::string value)
{
    auto it = data.find(id);

    if (it != data.end()) {
        it->second = value;
    } else {
        std::cout << "Record not found." << std::endl;
    }
}

void Database::Remove(std::string id)
{
    auto it = data.find(id);

    if (it != data.end()) {
        data.erase(it);
    } else {
        std::cout << "Record not found." << std::endl;
    }
}

void Database::Display()
{
    for (const auto &entry : data) {
        std::cout << "ID: " << entry.first << ", Value: " << entry.second << std::endl;
    }
}

void Database::Save()
{
    std::string mapString;

    for (const auto &pair : this->data) {
        mapString += pair.first + '\0';
        mapString += std::string(pair.second) + '\0';
    }

    std::string encryptedData = this->security.XOR(mapString, this->key);
    std::ofstream file(this->path, std::ios::binary | std::ios::out);
    if (file.is_open()) {
        file.write(encryptedData.c_str(), encryptedData.length());
        file.close();
        std::cout << "Encrypted map saved to " << this->path << " with password protection." << std::endl;
    } else {
        std::cerr << "Unable to open file: " << this->path << std::endl;
    }
}

void Database::Load()
{
    size_t pos = 0;
    std::ifstream file(this->path, std::ios::binary | std::ios::in);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << this->path << std::endl;
    }

    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string encryptedData(fileSize, '\0');
    file.read(&encryptedData[0], fileSize);
    file.close();

    std::string decryptedData = this->security.XOR(encryptedData, this->key);
    while (pos < decryptedData.length()) {
        size_t nullPos = decryptedData.find('\0', pos);
        if (nullPos == std::string::npos) {
            break;
        }

        std::string key = decryptedData.substr(pos, nullPos - pos);

        pos = nullPos + 1;
        nullPos = decryptedData.find('\0', pos);
        if (nullPos == std::string::npos) {
            break;
        }

        std::string value = decryptedData.substr(pos, nullPos - pos);

        this->data[key] = value;
        pos = nullPos + 1;
    }

    std::cout << "Encrypted map loaded from " << this->path << " with password protection." << std::endl;
}

bool Database::Exists()
{
    std::ifstream f(this->path);

    return (f.good());
}
