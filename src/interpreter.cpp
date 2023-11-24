#include "interpreter.hpp"

Interpreter::Interpreter(Database *database)
{
    this->db = database;
}

Interpreter::~Interpreter()
{
    
}

void Interpreter::Insert(std::string id, std::string value)
{
    this->db->Insert(id, value);
}

void Interpreter::Update(std::string id, std::string value)
{
    this->db->Update(id, value);
}

void Interpreter::Retrieve(std::string id)
{
    this->db->Retrieve(id);
}

void Interpreter::Delete(std::string id)
{
    this->db->Delete(id);
}

void Interpreter::Display()
{
    this->db->Display();
}

void Interpreter::Save()
{
    this->db->Save();
}

bool Interpreter::Load()
{
    if (this->db->Exists() == true) {
        this->db->Load();
        return (true);
    }

    return (false);
}
