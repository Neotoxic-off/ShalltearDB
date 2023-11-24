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
            void Save();
            bool Load();
            void Update(std::string, std::string);
            void Retrieve(std::string);
            void Delete(std::string);

        private:
            Database *db;
    };
