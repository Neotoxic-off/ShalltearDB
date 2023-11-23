#include "database.hpp"

Database::Database()
{
    this->path = std::string("database.stdb");
}

Database::~Database()
{
    
}

void Database::Insert(int id, const std::string value) {
    data[id] = value;
}

std::string Database::Retrieve(int id) {
    auto it = data.find(id);

    if (it != data.end()) {
        return it->second;
    } else {
        return "Not found";
    }
}

void Database::Update(int id, std::string value) {
    auto it = data.find(id);

    if (it != data.end()) {
        it->second = value;
    } else {
        std::cout << "Record not found." << std::endl;
    }
}

void Database::Remove(int id) {
    auto it = data.find(id);

    if (it != data.end()) {
        data.erase(it);
    } else {
        std::cout << "Record not found." << std::endl;
    }
}

void Database::Display() {
    for (const auto &entry : data) {
        std::cout << "ID: " << entry.first << ", Value: " << entry.second << std::endl;
    }
}

void Database::Save()
{
    std::ofstream file(this->path);

    if (file.is_open()) {
        for (const auto &pair : this->data) {
            file << pair.first << ' ' << pair.second << '\n';
        }
        file.close();
        std::cout << "Map saved to " << this->path << std::endl;
    } else {
        std::cerr << "Unable to open file: " << this->path << std::endl;
    }
}

void Database::Load()
{
    int key;
    std::string value;
    std::ifstream file(this->path);
    
    if (file.is_open()) {
        while (file >> key >> value) {
            this->data[key] = value;
        }
        file.close();
        std::cout << "Map loaded from " << this->path << std::endl;
    } else {
        std::cerr << "Unable to open file: " << this->path << std::endl;
    }
}
