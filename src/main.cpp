#include "database.hpp"
#include "interpreter.hpp"

int main()
{
    Database *instance = new Database();
    Interpreter *interpreter = new Interpreter(instance);

    interpreter->Insert(1, "John");
    interpreter->Insert(2, "Jane");

    interpreter->Display();

    interpreter->Save();

    return 0;
}
