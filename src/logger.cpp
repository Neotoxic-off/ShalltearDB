#include "logger.hpp"

Logger::Logger()
{

}

Logger::~Logger()
{

}

void Logger::Build(std::string _type, std::string message, std::string color)
{
    std::cout << "==> " << color << _type << RESET << ": " << message << std::endl;
}

void Logger::Error(std::string message)
{
    this->Build("error", message, RED);
}

void Logger::Wait(std::string message)
{
    this->Build("wait", message, YELLOW);
}

void Logger::Done(std::string message)
{
    this->Build("done", message, GREEN);
}

void Logger::Fail(std::string message)
{
    this->Build("fail", message, RED);
}

void Logger::Ok(std::string message)
{
    this->Build("ok", message, GREEN);
}

void Logger::Ko(std::string message)
{
    this->Build("ko", message, RED);
}

void Logger::Success(std::string message)
{
    this->Build("success", message, GREEN);
}

void Logger::Pair(std::string key, std::string value)
{
    this->Build("pair", (key + " " + value), BLUE);
}

void Logger::Warning(std::string message)
{
    this->Build("warning", message, YELLOW);
}
