# ShalltearDB
🩸 No SQL database made for C++

Simple database management system implemented in C++. It includes classes for managing tables (**Table**), a database (**Database**), and an interpreter (**Interpreter**) that provides a command interface for interacting with the database.

## Table Class
Represents a table in the database, with a name, an ID, and content (key-value pairs).
```CPP
class Table {
public:
    std::string name;
    std::string id;
    std::map<std::string, std::string> content;
};
```

## Database Class
Manages a collection of tables, supports operations like creating tables, inserting, updating, retrieving, and deleting records. It also provides methods for data serialization and deserialization for persistence.

```CPP
class Database {
public:
    // Constructor and Destructor
    Database(std::string _key);
    ~Database();

    // Database Operations
    bool Locked();
    bool Select(std::string select_table);
    void Create(std::string table_id, std::string table_name);
    void Insert(std::string id, const std::string value);
    std::string Retrieve(std::string id);
    void Update(std::string id, std::string value);
    void Delete(std::string id);
    void Display();

    // Serialization and Persistence
    void SerializeTables(std::ostream &os, const std::list<Table*> &tables);
    std::string TerminatedString(std::istream &is);
    void Save();
    void Load();
    bool Exists();
    
private:
    // Private Members
    Logger logger;
    std::list<Table*> tables;
    Table* instance;
    std::string path;
    std::string key;
    Security security;
};
```

## Interpreter Class
Acts as an interface for interacting with the database. It provides methods to perform database operations through user commands.

```CPP
class Interpreter {
public:
    // Constructor and Destructor
    Interpreter(Database *database);
    ~Interpreter();

    // Database Operations
    void Insert(std::string id, std::string value);
    void Update(std::string id, std::string value);
    void Retrieve(std::string id);
    void Delete(std::string id);
    void Display();
    void Save();
    bool Load();
};
```

## Examples
- Create a database with a specified encryption key.
- Create a table in the database.
- Select the table and perform operations like insertion, retrieval, update, and display.
- Save the database state to a file.
- Create an interpreter to interact with the database.
- Load the database state from the file using the interpreter.
- Perform additional operations through the interpreter.

```CPP
int main() {
    // Create a Database with a key
    Database myDatabase("encryption_key");

    // Create a table in the database
    myDatabase.Create("table1", "FirstTable");

    // Select the table and perform operations
    myDatabase.Select("table1");
    myDatabase.Insert("record1", "value1");
    std::string retrievedValue = myDatabase.Retrieve("record1");

    // Update and display records
    myDatabase.Update("record1", "new_value");
    myDatabase.Display();

    // Save and load using an interpreter
    myDatabase.Save();
    Interpreter myInterpreter(&myDatabase);
    myInterpreter.Load();

    // Perform additional operations through the interpreter
    myInterpreter.Insert("record2", "value2");
    myInterpreter.Display();

    return 0;
}
```

## Database documentation
- [Introduction](#introduction)
- [Class Overview](#class-overview)
- [Constructor and Destructor](#constructor-and-destructor)
- [Member Functions](#member-functions)
  - [Locked](#locked)
  - [Select](#select)
  - [Create](#create)
  - [Insert](#insert)
  - [Retrieve](#retrieve)
  - [Update](#update)
  - [Delete](#delete)
  - [Display](#display)
  - [SerializeTables](#serializetables)
  - [TerminatedString](#terminatedstring)
  - [Save](#save)
  - [Load](#load)
  - [Exists](#exists)

## Introduction

The `Database` class manages a collection of tables and provides methods for database operations such as creating tables, inserting, updating, retrieving, and deleting records. It also supports serialization and deserialization of tables for data persistence.

## Class Overview

### Class: `Database`

- Manages a list of Table pointers.
- Implements methods for database operations and data persistence.

## Constructor and Destructor

### `Database(std::string _key)`

- **Parameters:**
  - `_key`: The encryption key for data security.
  
- Initializes the `Database` instance with the specified encryption key.

### `~Database()`

- Releases resources associated with the `Database` instance.

## Member Functions

### `bool Locked()`

- Checks if a table is selected.
- **Returns:** True if no table is selected, false otherwise.

### `bool Select(std::string select_table)`

- Selects a table with the specified name.
- **Parameters:**
  - `select_table`: The name of the table to select.
- **Returns:** True if the table is found and selected, false otherwise.

### `void Create(std::string table_id, std::string table_name)`

- Creates a new table and adds it to the list of tables.
- **Parameters:**
  - `table_id`: The ID of the new table.
  - `table_name`: The name of the new table.

### `void Insert(std::string id, const std::string value)`

- Inserts a key-value pair into the selected table.
- **Parameters:**
  - `id`: The key for the data.
  - `value`: The value associated with the key.

### `std::string Retrieve(std::string id)`

- Retrieves the value associated with a key from the selected table.
- **Parameters:**
  - `id`: The key to retrieve.
- **Returns:** The value associated with the key if found, nullptr otherwise.

### `void Update(std::string id, std::string value)`

- Updates the value associated with a key in the selected table.
- **Parameters:**
  - `id`: The key whose value needs to be updated.
  - `value`: The new value to be associated with the key.

### `void Delete(std::string id)`

- Deletes a key-value pair from the selected table.
- **Parameters:**
  - `id`: The key to be deleted.

### `void Display()`

- Displays all key-value pairs in the selected table.

### `void SerializeTables(std::ostream &os, const std::list<Table*> &tables)`

- Serializes the tables and writes them to an output stream.
- **Parameters:**
  - `os`: The output stream.
  - `tables`: The list of tables to serialize.

### `std::string TerminatedString(std::istream &is)`

- Reads a null-terminated string from an input stream.
- **Parameters:**
  - `is`: The input stream.
- **Returns:** The read string.

### `void Save()`

- Saves the state of the database to a binary file.

### `void Load()`

- Loads the state of the database from a binary file.

### `bool Exists()`

- Checks if the database file exists.
- **Returns:** True if the file exists, false otherwise.



## Interpreter documentation
- [Introduction](#introduction)
- [Class Overview](#class-overview)
- [Constructor](#constructor)
- [Destructor](#destructor)
- [Member Functions](#member-functions)
  - [Insert](#insert)
  - [Update](#update)
  - [Retrieve](#retrieve)
  - [Delete](#delete)
  - [Display](#display)
  - [Save](#save)
  - [Load](#load)

## Introduction

The `Interpreter` class provides an interface to interact with a Database. It acts as a mediator between user commands and the underlying Database.

## Class Overview

### Class: `Interpreter`

- Manages a Database instance.
- Provides methods to perform operations like Insert, Update, Retrieve, Delete, Display, Save, and Load on the Database.

## Constructor

### `Interpreter(Database* database)`

- **Parameters:**
  - `database`: A pointer to the Database instance to be managed by the Interpreter.

## Destructor

### `~Interpreter()`

- Releases resources associated with the Interpreter.

## Member Functions

### Insert

#### `void Insert(std::string id, std::string value)`

Inserts a key-value pair into the Database.

### Update

#### `void Update(std::string id, std::string value)`

Updates the value associated with a key in the Database.

### Retrieve

#### `void Retrieve(std::string id)`

Retrieves and displays the value associated with a key in the Database.

### Delete

#### `void Delete(std::string id)`

Deletes a key-value pair from the Database.

### Display

#### `void Display()`

Displays all key-value pairs in the Database.

### Save

#### `void Save()`

Saves the state of the Database to a file.

### Load

#### `bool Load()`

Loads the state of the Database from a file.

- **Returns:** True if the Database was successfully loaded, false otherwise.

