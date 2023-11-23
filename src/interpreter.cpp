#include "interpreter.hpp"

Interpreter::Interpreter(Database *database)
{
    this->db = database;
}

Interpreter::~Interpreter()
{
    
}

void Interpreter::Interpret(std::string command)
{
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;

    if (cmd == "INSERT") {
        int id;
        std::string value;
        iss >> id >> value;
        this->db->Insert(id, value);
    } else if (cmd == "RETRIEVE") {
        int id;
        iss >> id;
        std::cout << "Retrieved: " << this->db->Retrieve(id) << std::endl;
    } else if (cmd == "UPDATE") {
        int id;
        std::string value;
        iss >> id >> value;
        this->db->Update(id, value);
    } else if (cmd == "DELETE") {
        int id;
        iss >> id;
        this->db->Remove(id);
    } else if (cmd == "DISPLAY") {
        this->db->Display();
    } else {
        std::cout << "Invalid command." << std::endl;
    }
}
