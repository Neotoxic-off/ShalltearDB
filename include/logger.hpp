#pragma once

    #include <iostream>
    #include <cstdarg>

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
            void Build(std::string, std::string);
    };
