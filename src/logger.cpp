#include "logger.hpp"

Logger::Logger()
{

}

Logger::~Logger()
{

}

void Logger::Build(std::string _type, std::string message)
{
    std::cout << "==> " << _type << ": " << message << std::endl;
}

void Logger::Error(std::string message)
{
    this->Build("error", message);
}

void Logger::Wait(std::string message)
{
    this->Build("wait", message);
}

void Logger::Done(std::string message)
{
    this->Build("done", message);
}

void Logger::Fail(std::string message)
{
    this->Build("fail", message);
}

void Logger::Ok(std::string message)
{
    this->Build("ok", message);
}

void Logger::Ko(std::string message)
{
    this->Build("ko", message);
}

void Logger::Success(std::string message)
{
    this->Build("success", message);
}

void Logger::Pair(std::string key, std::string value)
{
    this->Build("pair", (key + " " + value));
}

void Logger::Warning(std::string message)
{
    this->Build("warning", message);
}
