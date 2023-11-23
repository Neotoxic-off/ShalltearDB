#pragma once

    #include <iostream>
    #include <vector>
    #include <map>
    #include <sstream>
    #include <algorithm>
    #include <fstream>

    class Database
    {
        public:

            Database();
            ~Database();

            void Insert(int, std::string);
            std::string Retrieve(int);
            void Update(int, std::string);
            void Remove(int);
            void Display();

            void Save();
            bool Exists();
            void Load();

        private:
            std::string path;
            std::map<int, std::string> data;
    };
