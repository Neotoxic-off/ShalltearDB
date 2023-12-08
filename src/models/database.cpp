#include "database.hpp"

Database::Database(std::string _key)
{
    this->logger = Logger();
    this->path = std::string("database.stdb");
    this->key = _key;
    this->security = Security();
    this->tables = std::list<Table *>();
    this->instance = nullptr;

    this->db_s = '\r';
    this->t_s = '\a';
    this->tc_s = '\b';
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
    return (true);
}

bool Database::SelectByName(std::string select_table)
{
    std::string select_table_e = this->security.Encode(select_table);

    if (this->FindTableByName(select_table) == true) {
        for (auto &table : this->tables) {
            if (table->name == select_table_e) {
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
    std::string select_table_e = this->security.Encode(select_table);

    if (this->FindTableByID(select_table) == true) {
        for (auto &table : this->tables) {
            if (table->id == select_table_e) {
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
    std::string table_id_e = this->security.Encode(table_id);
    std::string table_name_e = this->security.Encode(table_name);

    if (this->FindTableByName(table_name) == false) {
        if (this->FindTableByID(table_id) == false) {
            if (this->ValidateTable(table_id_e, table_name_e) == true) {
                table = new Table(table_id_e, table_name_e);
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
    std::string table_name_e = this->security.Encode(table_name);

    for (const auto &table : this->tables) {
        if (table->name == table_name_e) {
            return (true);
        }
    }

    return (false);
}

std::map<std::string, std::string> Database::FindAllStartWith(std::string starter)
{
    std::string starter_e = this->security.Encode(starter);
    std::map<std::string, std::string> result = std::map<std::string, std::string>();

    for (const auto &data : this->instance->content) {
        if (data.second.rfind(starter_e, 0) == 0) {
            result[this->security.Decode(data.first)] = this->security.Decode(data.second);
        }
    }

    return (result);
}

bool Database::FindTableByID(std::string table_id)
{
    std::string table_id_e = this->security.Encode(table_id);

    for (const auto &table : this->tables) {
        if (table->id == table_id_e) {
            return (true);
        }
    }

    return (false);
}

void Database::Insert(std::string id, const std::string value)
{
    std::string id_e = this->security.Encode(id);
    std::string value_e = this->security.Encode(value);
    auto it = this->instance->content.find(id_e);

    if (it == this->instance->content.end()) {
        this->instance->content[id_e] = value_e;
        this->logger.Ok("record inserted");
    } else {
        this->logger.Ko("record already present, use update instead");
    }
}

std::string Database::FindById(std::string id)
{
    std::map<std::string, std::string>::iterator it;
    std::string id_e = this->security.Encode(id);

    if (this->Locked() == false) {
        it = this->instance->content.find(id_e);
        if (it != this->instance->content.end()) {
            this->logger.Ok("record found");
            return (it->second);
        }
    }

    return (nullptr);
}

std::string Database::FindFirst(std::string value)
{
    std::string result;
    std::string value_e = this->security.Encode(value);

    if (this->Locked() == false) {
        for (auto &it: this->instance->content) {
            if (it.second == value_e) {
                this->logger.Ok("record found");
                result = this->security.Decode(it.first);
                return (result);
            }
        }
        this->logger.Ko("record not found");
    }

    return (result);
}

std::vector<std::string> Database::FindAll(std::string value)
{
    std::string value_e = this->security.Encode(value);
    std::vector<std::string> result = std::vector<std::string>();

    if (this->Locked() == false) {
        for (auto &it: this->instance->content) {
            if (it.second == value_e) {
                result.push_back(this->security.Decode(it.first));
            }
        }
    }

    return (result);
}


void Database::Update(std::string id, std::string value)
{
    std::map<std::string, std::string>::iterator it;
    std::string id_e = this->security.Encode(id);
    std::string value_e = this->security.Encode(value);

    if (this->Locked() == false) {
        it = this->instance->content.find(id_e);
        if (it != this->instance->content.end()) {
            it->second = value_e;
            this->logger.Ok("record updated");
        } else {
            this->logger.Ko("record not found");
        }
    }
}

int Database::Count()
{
    int size = 0;

    if (this->Locked() == false) {
        size = this->instance->content.size();
    }

    return (size);
}

void Database::Delete(std::string id)
{
    std::map<std::string, std::string>::iterator it;
    std::string id_e = this->security.Encode(id);
    
    if (this->Locked() == false) {
        it = this->instance->content.find(id_e);
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
            this->logger.Pair(this->security.Decode(entry.first), this->security.Decode(entry.second));
        }
    }
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
    Table *table = nullptr;
    std::string line;
    std::ifstream file(this->path, std::ios::binary);
    size_t pos = 0;
    std::istringstream iss;
    std::string id;
    std::string name;
    std::string pair;

    if (file.is_open() == true) {
        while (std::getline(file, line, this->db_s))
        {
            iss = std::istringstream(line);

            std::getline(iss, id, this->tc_s);
            std::getline(iss, name, this->tc_s);

            table = new Table(id, name);

            while (std::getline(iss, pair, this->tc_s))
            {
                pos = pair.find(this->t_s);
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
