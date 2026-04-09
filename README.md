# Mini SQL Database (C++)

A lightweight SQL-like database engine implemented in C++, designed to model how relational database systems parse, store, and query structured data at a low level.

This project recreates core database functionality from scratch—without external database libraries—to demonstrate a deep understanding of data storage, query execution, and system design.

---

## Overview

This system simulates a simplified relational database engine capable of executing SQL-like commands against structured datasets. It includes a custom query parser, file-based storage engine, and internal data handling mechanisms.

Rather than focusing on full SQL compliance, the project emphasizes how databases work internally, including:

- Query parsing and interpretation  
- Record storage and retrieval  
- Table abstraction and schema handling  
- Execution of basic relational operations  

---

## Key Features

- SQL-like command interface (`CREATE`, `INSERT`, `SELECT`)
- Table creation with dynamic schemas
- Record insertion and retrieval
- File-based persistence using binary storage
- Custom parsing and execution pipeline
- Modular engine design for extensibility

---

## Tech Stack

- **Language:** C++  
- **Build System:** CMake  
- **Core Concepts:**
  - File I/O (binary storage)
  - Data structures (maps, vectors, indexing)
  - Parsing and tokenization
  - Object-oriented design

---

## System Architecture

The database engine is structured into distinct components that mirror real-world database systems:
```
User Input (SQL-like query)
│
▼
[ Query Parser ]
│
▼
[ Execution Engine ]
│
▼
[ Storage Engine (Binary Files) ]
│
▼
[ Result Output ]
```

### Component Breakdown

- **Parser**
  - Tokenizes and interprets SQL-like commands
  - Converts raw input into structured operations

- **Execution Engine**
  - Processes parsed commands
  - Coordinates table operations and data flow

- **Storage Layer**
  - Handles persistent storage using binary files
  - Manages table data and schema representation

---

## Project Structure
```
.
├── includes/ # Core database engine implementation
├── main.cpp # Entry point / command interface
├── CMakeLists.txt # Build configuration
└── README.md
```
---

## Demo

### Example Usage

```sql
CREATE TABLE students (name, age, major);
INSERT INTO students VALUES ("Alice", 20, "CS");
INSERT INTO students VALUES ("Bob", 22, "Math");
SELECT * FROM students;
```

## Sample Output
```
+--------+-----+-------+
| name   | age | major |
+--------+-----+-------+
| Alice  | 20  | CS    |
| Bob    | 22  | Math  |
+--------+-----+-------+
```
## Getting Started
Prerequisites
  - C++ compiler (g++ or clang++)
  - CMake

## Build and Run
```
git clone https://github.com/fredylung/mini-sql-database.git
cd mini-sql-database

mkdir build
cd build
cmake ..
make

./main
```
## Design Decisions
  - Binary storage over text files
  - Improves performance and mimics real database storage strategies.
  - Custom parser instead of external libraries
  - Reinforces understanding of how query languages are interpreted.
  - Modular architecture
  - Allows future expansion (e.g., indexing, query optimization).
## Limitations
  - Not a full SQL implementation
  - No support for JOIN operations or complex queries
  - No concurrency or transaction management
  - Minimal query optimization

## This project is intended as a learning-focused system, not a production database.

## Future Improvements
  - Add indexing (e.g., B-trees or hash indexing)
  - Support WHERE conditions and filtering
  - Implement JOIN operations
  - Improve parser robustness and error handling
  - Add interactive CLI with command history
  - Introduce basic query optimization strategies
    
## What This Project Demonstrates
  - Strong understanding of database internals
  - Ability to design and implement complex systems in C++
  - Experience with file-based data persistence
  - Knowledge of parsing, execution pipelines, and system architecture
### Author

## Fredy Lung
## Software Developer

### Portfolio

This project is part of my software engineering portfolio.
Explore more projects here:

👉 https://fredylung.vercel.app/
