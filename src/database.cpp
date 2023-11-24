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

bool Database::Locked()
{
    if (this->instance == nullptr) {
        this->logger.Warning("no table selected");
        return (true);
    }

    return (false);
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
    std::map<std::string, std::string>::iterator it;
    
    if (this->Locked() == false) {
        it = this->instance->content.find(id);
        if (it != this->instance->content.end()) {
            return (it->second);
        }
    }

    return (nullptr);
}

void Database::Update(std::string id, std::string value)
{
    std::map<std::string, std::string>::iterator it;

    if (this->Locked() == false) {
        it = this->instance->content.find(id);
        if (it != this->instance->content.end()) {
            it->second = value;
        } else {
            this->logger.Ko("Record not found");
        }
    }
}

void Database::Delete(std::string id)
{
    std::map<std::string, std::string>::iterator it;
    
    if (this->Locked() == false) {
        it = this->instance->content.find(id);
        if (it != this->instance->content.end()) {
            this->instance->content.erase(it);
        } else {
            this->logger.Ko("Record not found");
        }
    }
}

void Database::Display()
{
    if (this->Locked() == false) {
        for (const auto &entry : this->instance->content) {
            this->logger.Pair(entry.first, entry.second);
        }
    }
}

void Database::SerializeTables(std::ostream &os, const std::list<Table*> &tables)
{
    for (const auto &table : tables) {
        os.write(table->name.data(), table->name.size() + 1);
        os.write(table->id.data(), table->id.size() + 1);
        for (const auto& entry : table->content) {
            os.write(entry.first.data(), entry.first.size() + 1);
            os.write(entry.second.data(), entry.second.size() + 1);
        }
        char nullTerminator = '\0';
        os.write(&nullTerminator, 1);
    }
}

std::string Database::TerminatedString(std::istream &is)
{
    char ch;
    std::string result;

    while (is.get(ch) && ch != '\0') {
        result.push_back(ch);
    }

    return result;
}

void Database::Save()
{
    std::ofstream file(path, std::ios::binary);

    if (file.is_open()) {
        this->SerializeTables(file, tables);
        file.close();
        this->logger.Success("Database saved");
    } else {
        this->logger.Fail("Unable to open database");
    }
}

void Database::Load()
{
    Table *table;
    std::string id;
    std::string key;
    std::string name;
    std::string value;
    std::ifstream file(this->path, std::ios::binary);

    if (file.is_open() == true) {
        while (file.peek() != EOF) {
            name = this->TerminatedString(file);
            id = this->TerminatedString(file);
            table = new Table(id, name);
            while (file.peek() != '\0') {
                key = this->TerminatedString(file);
                value = this->TerminatedString(file);
                table->content[key] = value;
            }
            file.ignore();
            this->tables.push_back(table);
        }
        file.close();
        this->logger.Success("Database loaded");
    } else {
        this->logger.Fail("Database not loaded");
    }
}

bool Database::Exists()
{
    std::ifstream f(this->path);

    return (f.good());
}
