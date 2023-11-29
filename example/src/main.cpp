#include "shalltearDB.hpp"

int main(int argc, char **argv)
{
    ShalltearDB *shalltearDB = new ShalltearDB("key");
    std::string find;
    std::vector<std::string> all = std::vector<std::string>();

    if (shalltearDB->database->Exists() == true) {
        shalltearDB->database->Load();
        shalltearDB->database->SelectByName("table_1");
        shalltearDB->interpreter->Display();
        shalltearDB->database->SelectByName("table_2");
        shalltearDB->interpreter->Display();
    }
    shalltearDB->interpreter->Create("tbl_1", "table_1");
    shalltearDB->interpreter->Create("tbl_2", "table_2");
    shalltearDB->interpreter->SelectByID("tbl_1");
    shalltearDB->interpreter->Insert("100", "9");
    for (size_t i = 0; i < 10; i++) {
        shalltearDB->interpreter->Insert(std::to_string(i), std::to_string(i));
    }
    find = shalltearDB->interpreter->FindFirst("9");
    all = shalltearDB->interpreter->FindAll("9");
    shalltearDB->database->SelectByName("table_2");
    for (size_t i = 10; i < 20; i++) {
        shalltearDB->interpreter->Insert(std::to_string(i), std::to_string(i));
    }
    shalltearDB->interpreter->Display();
    shalltearDB->interpreter->Save();

    std::cout << "First: " << find << std::endl;
    for (auto &it: all) {
        std::cout << it << std::endl;
    }

    return (0);
}
