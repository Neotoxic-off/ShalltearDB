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

            bool Select(std::string);
            void Create(std::string, std::string);
            void Insert(std::string, std::string);
            std::string Retrieve(std::string);
            void Update(std::string, std::string);
            void Remove(std::string);
            void Display();

            void Save();
            bool Exists();
            void Load();

        private:
            Security security;
            Logger logger;
            std::list<Table *> tables;
            Table *instance;

            std::string path;
            std::string key;

    };
