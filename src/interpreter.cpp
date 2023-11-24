#include "interpreter.hpp"

Interpreter::Interpreter(Database *database)
{
    this->db = database;
}

Interpreter::~Interpreter()
{
    
}

// void Interpreter::Query(std::string command)
// {
//     std::istringstream iss(command);
//     std::vector<std::string> tokens
//     {
//         std::istream_iterator<std::string>{iss},
//         std::istream_iterator<std::string>{}
//     };
//     for (auto &command : this->commands) {
//         if (command.name == tokens.at(0))
//             command.Execute(tokens);
//     }
//     if (cmd == "INSERT") {
//         int id;
//         std::string value;
//         iss >> id >> value;
//         this->db->Insert(id, value);
//     } else if (cmd == "RETRIEVE") {
//         int id;
//         iss >> id;
//         std::cout << "Retrieved: " << this->db->Retrieve(id) << std::endl;
//     } else if (cmd == "UPDATE") {
//         int id;
//         std::string value;
//         iss >> id >> value;
//         this->db->Update(id, value);
//     } else if (cmd == "DELETE") {
//         int id;
//         iss >> id;
//         this->db->Remove(id);
//     } else if (cmd == "DISPLAY") {
//         this->db->Display();
//     } else {
//         std::cout << "Invalid command." << std::endl;
//     }
// }

void Interpreter::Insert(std::string id, std::string value)
{
    this->db->Insert(id, value);
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
