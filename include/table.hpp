#pragma once

    #include <iostream>
    #include <map>

    class Table
    {
        public:
            std::string name;
            std::string id;
            std::map<std::string, std::string> content;
    };