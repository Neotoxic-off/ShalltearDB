#pragma once

    #include <iostream>
    #include <cstdarg>

    #define RESET "\033[0m"
    #define RED "\033[31m"
    #define GREEN "\033[32m"
    #define YELLOW "\033[33m"
    #define BLUE "\033[34m"

    class Logger
    {
        public:
            Logger();
            ~Logger();

            void Error(std::string);
            void Wait(std::string);
            void Done(std::string);
            void Fail(std::string);
            void Success(std::string);
            void Ok(std::string);
            void Ko(std::string);
            void Warning(std::string);
            void Pair(std::string, std::string);

        private:
            void Build(std::string, std::string, std::string);
    };
