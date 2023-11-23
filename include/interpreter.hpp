
#pragma once

    #include "database.hpp"

    class Interpreter
    {
        public:
            Interpreter(Database *);
            ~Interpreter();

            void Interpret(std::string);

        private:
            Database *db;
    };
