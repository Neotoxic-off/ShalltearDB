#include "database.hpp"
#include "interpreter.hpp"

int main()
{
    Database *database = new Database();
    Interpreter *interpreter = new Interpreter(database);

    if (database->Exists() == true) {
        database->Load();
        interpreter->Insert(2, "load");
    } else {
        interpreter->Insert(1, "sample");
    }

    interpreter->Display();

    interpreter->Save();

    return 0;
}
