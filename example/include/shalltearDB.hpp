#pragma once

    #include "database.hpp"
    #include "interpreter.hpp"

    class ShalltearDB
    {
        public:
            Database *database;
            Interpreter *interpreter;

            ShalltearDB(std::string);
            ~ShalltearDB();

        private:
    };
