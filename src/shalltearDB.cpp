#include "shalltearDB.hpp"

ShalltearDB::ShalltearDB(std::string key)
{
    this->database = new Database(key);
    this->interpreter = new Interpreter(this->database);
}

ShalltearDB::~ShalltearDB()
{
    delete this->database;
    delete this->interpreter;
}
