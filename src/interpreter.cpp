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

void Interpreter::Create(std::string id, std::string value)
{
    this->db->Create(id, value);
}

void Interpreter::SelectByID(std::string id)
{
    this->db->SelectByID(id);
}

void Interpreter::SelectByName(std::string name)
{
    this->db->SelectByName(name);
}

void Interpreter::FindById(std::string id)
{
    this->db->RetrieveById(id);
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
