#pragma once

    #include <iostream>
    #include <map>
    #include <functional>
    #include <string>
    #include <chrono>

    class Table
    {
        public:
            std::string id;
            std::string name;
            std::map<std::string, std::string> content;

            Table(std::string, std::string);
            ~Table();
    };