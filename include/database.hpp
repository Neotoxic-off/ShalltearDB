#pragma once

    #include <iostream>
    #include <vector>
    #include <map>
    #include <sstream>
    #include <algorithm>
    #include <fstream>

    #include "security.hpp"

    class Database
    {
        public:
            Database(std::string);
            ~Database();

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

            std::string path;
            std::string key;
            std::map<std::string, std::string> data;

    };
