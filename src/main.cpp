#include "database.hpp"
#include "interpreter.hpp"

int main()
{
    Database *instance = new Database();
    Interpreter *interpreter = new Interpreter(instance);

    // Example commands
    interpreter->Interpret("INSERT 1 John");
    interpreter->Interpret("INSERT 2 Jane");
    interpreter->Interpret("DISPLAY");
    interpreter->Interpret("RETRIEVE 1");
    interpreter->Interpret("UPDATE 1 Mike");
    interpreter->Interpret("DISPLAY");
    interpreter->Interpret("DELETE 2");
    interpreter->Interpret("DISPLAY");

    return 0;
}
