#pragma once

    #include <iostream>
    #include <vector>

    class Security
    {
        public:
            Security();
            ~Security();

            void XOR(std::vector<char> &, const std::string &);
    };

    