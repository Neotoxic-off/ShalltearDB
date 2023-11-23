#pragma once

    #include <iostream>
    #include <vector>
    #include <map>
    #include <sstream>
    #include <algorithm>

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

        private:
            std::map<int, std::string> data;
    };
