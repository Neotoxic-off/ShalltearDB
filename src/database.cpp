#include "database.hpp"

Database::Database(std::string _key)
{
    this->logger = Logger();
    this->path = std::string("database.stdb");
    this->key = _key;
    this->security = Security();
    this->tables = std::list<Table *>();
    this->instance = nullptr;

    this->db_s = '\01';
    this->t_s = '\02';
    this->tc_s = '\03';
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

bool Database::ValidateTable(std::string table_id, std::string table_name)
{
    std::list<bool> checks = {
        table_id.find(this->db_s) != std::string::npos,
        table_name.find(this->db_s) != std::string::npos
    };

    for (bool check : checks) {
        if (check == true) {
            this->logger.Error("Database creation failed");
            return (false);
        }
    }

    return (true);
}

bool Database::SelectByName(std::string select_table)
{
    if (this->FindTableByName(select_table) == true) {
        for (auto &table : this->tables) {
            if (table->name == select_table) {
                this->instance = table;
                this->logger.Ok("table selected");
                return (true);
            }
        }
    }

    this->logger.Ko("table name to select not found");

    return (false);
}

bool Database::SelectByID(std::string select_table)
{
    if (this->FindTableByID(select_table) == true) {
        for (auto &table : this->tables) {
            if (table->id == select_table) {
                this->instance = table;
                this->logger.Ok("table selected");
                return (true);
            }
        }
    }

    this->logger.Ko("table id to select not found");

    return (false);
}

void Database::Create(std::string table_id, std::string table_name)
{
    Table *table = nullptr;
    size_t size = 0;

    if (this->FindTableByName(table_name) == false) {
        if (this->FindTableByID(table_id) == false) {
            if (this->ValidateTable(table_id, table_name) == true) {
                table = new Table(table_id, table_name);
                size = std::distance(this->tables.begin(), this->tables.end());
                this->tables.push_back(table);
                this->logger.Ok("table created");
            } else {
                this->logger.Ko("table not created");
            }
        } else {
            this->logger.Ko("table id already present");
        }
    } else {
        this->logger.Ko("table name already present");
    }
}

bool Database::FindTableByName(std::string table_name)
{
    for (const auto &table : this->tables) {
        if (table->name == table_name) {
            return (true);
        }
    }

    return (false);
}

bool Database::FindTableByID(std::string table_id)
{
    for (const auto &table : this->tables) {
        if (table->id == table_id) {
            return (true);
        }
    }

    return (false);
}

void Database::Insert(std::string id, const std::string value)
{
    auto it = this->instance->content.find(id);

    if (it == this->instance->content.end()) {
        this->instance->content[id] = value;
        this->logger.Ok("record inserted");
    } else {
        this->logger.Ko("record already present, use update instead");
    }
}

std::string Database::Retrieve(std::string id)
{
    std::map<std::string, std::string>::iterator it;
    
    if (this->Locked() == false) {
        it = this->instance->content.find(id);
        if (it != this->instance->content.end()) {
            this->logger.Ok("record found");
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
            this->logger.Ok("record updated");
        } else {
            this->logger.Ko("record not found");
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
            this->logger.Ok("record deleted");
        } else {
            this->logger.Ko("record not found");
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

std::string Database::ExtractTable(std::istream &is)
{
    char ch;
    std::string result;

    while (is.get(ch) && ch != this->t_s) {
        result.push_back(ch);
    }

    return (result);
}

std::string Database::ExtractContent(std::istream &is)
{
    char ch;
    std::string result;

    while (is.get(ch) && ch != this->tc_s && ch != this->t_s) {
        result.push_back(ch);
    }

    return (result);
}

bool Database::Exists()
{
    std::ifstream f(this->path);

    return (f.good());
}

void Database::Save()
{
    std::ofstream file(path, std::ios::binary);

    if (file.is_open()) {
        for (const auto &table : tables)
        {
            file << table->id << this->tc_s << table->name << this->tc_s;

            for (const auto &entry : table->content)
            {
                file << entry.first << this->t_s << entry.second << this->tc_s;
            }

            file << this->db_s;
        }
        this->logger.Success("Database saved");
    } else {
        this->logger.Fail("Unable to open database");
    }
}

void Database::Load()
{
    std::string line;
    std::ifstream file(this->path, std::ios::binary);

    if (file.is_open() == true) {
        while (std::getline(file, line, this->db_s))
        {
            std::istringstream iss(line);
            std::string id, name, pair;

            std::getline(iss, id, this->tc_s);
            std::getline(iss, name, this->tc_s);

            Table *table = new Table(id, name);

            while (std::getline(iss, pair, this->tc_s))
            {
                size_t pos = pair.find(this->t_s);
                if (pos != std::string::npos)
                {
                    std::string key = pair.substr(0, pos);
                    std::string value = pair.substr(pos + 1);
                    table->content[key] = value;
                }
            }

            tables.push_back(table);
        }
        this->logger.Success("Database loaded");
    } else {
        this->logger.Fail("Database not loaded");
    }
}
