#pragma once

    #include <iostream>

    class Security
    {
        public:
            Security();
            ~Security();

            std::string XOR(const std::string &, const std::string &);
    };

    