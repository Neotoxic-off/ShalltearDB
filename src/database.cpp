#include "database.hpp"

Database::Database()
{

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
    for (const auto& entry : data) {
        std::cout << "ID: " << entry.first << ", Value: " << entry.second << std::endl;
    }
}
