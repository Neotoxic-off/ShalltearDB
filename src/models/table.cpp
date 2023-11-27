#include "table.hpp"

Table::Table(std::string _id, std::string _name)
{
    this->name = _name;
    this->id = _id;
    this->content = std::map<std::string, std::string>();
}

Table::~Table()
{

}
