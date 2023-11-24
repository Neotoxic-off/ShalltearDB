#include "database.hpp"
#include "interpreter.hpp"

int main()
{
    std::string key = std::string("secure_key");
    Database *database = new Database(key);
    Interpreter *interpreter = new Interpreter(database);

    if (database->Exists() == true) {
        database->Load();
        // database->Select("table_1");
        // interpreter->Insert("2", "load");
    } else {
        database->Create("0", "table_1");
        database->Select("table_1");
        interpreter->Insert("1", "sample");
    }

    interpreter->Display();

    interpreter->Save();

    return 0;
}
