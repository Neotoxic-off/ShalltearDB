#include "database.hpp"

Database::Database(std::string _key)
{
    this->logger = Logger();
    this->path = std::string("database.stdb");
    this->key = _key;
    this->security = Security();
    this->tables = std::vector<Table>();
    this->instance = Table();
}

Database::~Database()
{
    
}

bool Database::Select(std::string select_table)
{
    for (auto &table : this->tables) {
        if (table.name == select_table) {
            this->instance = table;
            return (true);
        }
    }

    return (false);
}

void Database::Insert(std::string id, const std::string value)
{
    this->instance.content[id] = value;
}

std::string Database::Retrieve(std::string id)
{
    auto it = this->instance.content.find(id);

    if (it != this->instance.content.end()) {
        return it->second;
    } else {
        return "Not found";
    }
}

void Database::Update(std::string id, std::string value)
{
    auto it = this->instance.content.find(id);

    if (it != this->instance.content.end()) {
        it->second = value;
    } else {
        this->logger.Ko("Record not found");
    }
}

void Database::Remove(std::string id)
{
    auto it = this->instance.content.find(id);

    if (it != this->instance.content.end()) {
        this->instance.content.erase(it);
    } else {
        this->logger.Ko("Record not found");
    }
}

void Database::Display()
{
    for (const auto &entry : this->instance.content) {
        this->logger.Pair(entry.first, entry.second);
    }
}

std::vector<char> serializeTables(const std::vector<Table>& tables)
{
    std::vector<char> serializedData;
    for (const auto& table : tables) {
        serializedData.insert(serializedData.end(), table.name.begin(), table.name.end());
        serializedData.push_back('\0');
        serializedData.insert(serializedData.end(), table.id.begin(), table.id.end());
        serializedData.push_back('\0');
        for (const auto& entry : table.content) {
            serializedData.insert(serializedData.end(), entry.first.begin(), entry.first.end());
            serializedData.push_back('\0');
            serializedData.insert(serializedData.end(), entry.second.begin(), entry.second.end());
            serializedData.push_back('\0');
        }
    }
    return serializedData;
}

// Function to XOR encode the data with a key
void xorEncode(std::vector<char>& data, const std::string& key)
{
    size_t keyIndex = 0;
    for (char& byte : data) {
        byte ^= key[keyIndex];
        keyIndex = (keyIndex + 1) % key.size();
    }
}

// Function to save the encoded data to a file
void saveEncodedDataToFile(const std::vector<char>& data, const std::string& filename)
{
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.write(data.data(), data.size());
        file.close();
        std::cout << "Data saved to " << filename << " encoded with XOR." << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}


void Database::Save()
{
    std::vector<char> serializedData = serializeTables(tables);

    xorEncode(serializedData, this->key);

    saveEncodedDataToFile(serializedData, this->path);
}

void Database::Load()
{
    
}

bool Database::Exists()
{
    std::ifstream f(this->path);

    return (f.good());
}
