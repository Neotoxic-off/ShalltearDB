#pragma once

    #include <iostream>
    #include <vector>
    #include <map>
    #include <sstream>
    #include <algorithm>

    #include "database.hpp"

    class Interpreter
    {
        public:
            Interpreter(Database *);
            ~Interpreter();

            void Insert(std::string, std::string);
            void Display();
            int Count();
            void Save();
            bool Load();
            void Update(std::string, std::string);
            void Delete(std::string);

            void FindById(std::string);
            std::string FindFirst(std::string);
            std::map<std::string, std::string> FindAll(std::string);
            std::map<std::string, std::string> FindAllStartWith(std::string);

            void Create(std::string, std::string);
            void SelectByID(std::string);
            void SelectByName(std::string);

        private:
            Database *db;
    };
