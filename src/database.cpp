#include "database.hpp"

Database::Database(std::string _key)
{
    this->logger = Logger();
    this->path = std::string("database.stdb");
    this->key = _key;
    this->security = Security();
    this->tables = std::list<Table *>();
    this->instance = nullptr;
}

Database::~Database()
{
    
}

bool Database::Select(std::string select_table)
{
    for (auto &table : this->tables) {
        if (table->name == select_table) {
            this->instance = table;
            return (true);
        }
    }

    return (false);
}

void Database::Create(std::string table_id, std::string table_name)
{
    Table *table = new Table(table_id, table_name);
    size_t size = std::distance(this->tables.begin(), this->tables.end());

    this->tables.push_back(table);
}

void Database::Insert(std::string id, const std::string value)
{
    this->instance->content[id] = value;
}

std::string Database::Retrieve(std::string id)
{
    auto it = this->instance->content.find(id);

    if (it != this->instance->content.end()) {
        return it->second;
    } else {
        return "Not found";
    }
}

void Database::Update(std::string id, std::string value)
{
    auto it = this->instance->content.find(id);

    if (it != this->instance->content.end()) {
        it->second = value;
    } else {
        this->logger.Ko("Record not found");
    }
}

void Database::Remove(std::string id)
{
    auto it = this->instance->content.find(id);

    if (it != this->instance->content.end()) {
        this->instance->content.erase(it);
    } else {
        this->logger.Ko("Record not found");
    }
}

void Database::Display()
{
    if (this->instance != nullptr) {
        for (const auto &entry : this->instance->content) {
            this->logger.Pair(entry.first, entry.second);
        }
    }
}

void serializeTable(std::ostream& os, const Table& table) {
    // Serialize table properties
    os.write(table.name.data(), table.name.size() + 1);  // Include null terminator
    os.write(table.id.data(), table.id.size() + 1);

    // Serialize content
    for (const auto& entry : table.content) {
        os.write(entry.first.data(), entry.first.size() + 1);
        os.write(entry.second.data(), entry.second.size() + 1);
    }
    // Null terminator to indicate the end of content
    char nullTerminator = '\0';
    os.write(&nullTerminator, 1);
}

void serializeAndSaveTables(std::ostream& os, const std::list<Table*>& tables) {
    for (const auto& table : tables) {
        serializeTable(os, *table);
    }
}

std::string readNullTerminatedString(std::istream& is)
{
    std::string result;
    char ch;
    while (is.get(ch) && ch != '\0') {
        result.push_back(ch);
    }
    return result;
}

void Database::Save()
{
    std::ofstream file(path, std::ios::binary);
    if (file.is_open()) {
        serializeAndSaveTables(file, tables);
        file.close();
        std::cout << "Data saved to " << path << " in binary format." << std::endl;
    } else {
        std::cerr << "Unable to open file: " << path << std::endl;
    }
}

void Database::Load()
{
    std::string name;
    std::string id;
    std::ifstream file(this->path, std::ios::binary);
    Table *table;
    std::string key;
    std::string value;

    if (file.is_open() == true) {
        while (file.peek() != EOF) {
            name = readNullTerminatedString(file);
            id = readNullTerminatedString(file);
            table = new Table(id, name);
            while (file.peek() != '\0') {
                key = readNullTerminatedString(file);
                value = readNullTerminatedString(file);
                table->content[key] = value;
            }
            file.ignore();
            this->tables.push_back(table);
        }
        file.close();
        std::cout << "Data loaded from " << this->path << " in binary format." << std::endl;
    } else {
        std::cerr << "Unable to open file: " << this->path << std::endl;
    }
}

bool Database::Exists()
{
    std::ifstream f(this->path);

    return (f.good());
}
