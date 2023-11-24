#pragma once

    #include <iostream>

    class Security
    {
        public:
            Security();
            ~Security();

            void XOR(std::vector<char> &, const std::string &);
    };

    