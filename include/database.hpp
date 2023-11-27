#pragma once

    #include <iostream>
    #include <vector>
    #include <map>
    #include <sstream>
    #include <algorithm>
    #include <list>
    #include <fstream>

    #include "logger.hpp"
    #include "table.hpp"
    #include "security.hpp"

    class Database
    {
        public:
            Database(std::string);
            ~Database();

            bool SelectByName(std::string);
            bool SelectByID(std::string);
            void Create(std::string, std::string);
            void Insert(std::string, std::string);
            std::string Retrieve(std::string);
            void Update(std::string, std::string);
            void Delete(std::string);
            void Display();
            void Save();
            void Load();
            
            bool Exists();
            bool FindTableByName(std::string);
            bool FindTableByID(std::string);
            bool ValidateTable(std::string, std::string);
            bool Locked();

            void Dumper(std::ostream &);
            char *Serialize(char *, char);

        private:
            Logger logger;
            Security security;
            Table *instance;
            std::list<Table *> tables;

            std::string path;
            std::string key;

            char db_s;
            char t_s;
            char tc_s;
    };
