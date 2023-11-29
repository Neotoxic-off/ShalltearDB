#pragma once

    #include <iostream>
    #include <vector>
    #include <iomanip>
    #include <sstream>

    class Security
    {
        public:
            Security();
            ~Security();

            void XOR(std::vector<char> &, const std::string &);
            std::string Encode(const std::string &);
            std::string Decode(const std::string &);
    };
