  # Library Management System

## Introduction
The Library Management System is a console-based application designed to efficiently manage library operations. 
It allows users to add, search, issue, return, and delete books. The program also supports data persistence using files 
and provides functionalities like undoing deletions.

## Features
- Add new books to the library.
- Search for books by ID or title.
- Issue and return books.
- List all available books sorted alphabetically.
- Delete books and undo last deletions.
- Data persistence using file handling.
- User-friendly console interface with color-coded output.

## Requirements
-  Operating System : Windows
-  Compiler : GCC or any compatible C++ compiler supporting C++11 or later
-  Libraries :
- Standard C++ libraries (`<iostream>`, `<fstream>`, `<string>`, `<list>`, `<map>`, `<stack>`, `<queue>`, `<algorithm>`)
 - Windows-specific library (`<windows.h>`)

## How to Use
1. Clone the repository or download the source code.
2. Compile the program using a C++ compiler:
   ```bash
 g++ library_management.cpp -o library_management
   ```
3. Run the executable:
   ```bash
   ./library_management

4. Follow the on-screen instructions to navigate through the menu.

## File Structure

.
├── library_management.cpp  # Source code file
├── library_data.txt        # Data file for storing library records (auto-generated)
└── README.md               # Documentation file


## Code Description
The system is implemented using object-oriented programming principles:

### Key Classes and Functions
-  `struct Book` : Represents a book with attributes like ID, title, author, and issue status.
-  `class Library` :
  -  Data Structures Used :
    - `list<Book>`: To store books.
    - `map<int, list<Book>::iterator>`: For fast lookup of books by ID.
    - `stack<Book>`: To support undoing deletions.
    - `queue<int>`: To manage book issue requests.
  -  Methods :
    - `addBook`: Adds a new book to the library.
    - `searchBookById`: Finds a book by its ID.
    - `searchBookByTitle`: Finds a book by its title.
    - `issueBook`: Issues a book to a user.
    - `returnBook`: Returns an issued book.
    - `listAllBooks`: Displays all books sorted alphabetically by title.
    - `deleteBook`: Deletes a book from the library.
    - `undoLastDeletion`: Restores the most recently deleted book.
    - `saveToFile` and `loadFromFile`: Handle data persistence.
-  Console Utilities :
  - `setConsoleColor`: Sets console text color for better UX.
  - `displayTitle`: Displays the application title.

### Sample Menu
```
[1] Add Book
[2] Search Book by ID
[3] Search Book by Title
[4] Issue Book
[5] Return Book
[6] List All Books
[7] Delete Book
[8] Undo Last Deletion
[9] Exit
```

## Future Enhancements
- Add user authentication for better access control.
- Implement book reservation functionality.
- Enhance data storage using a database.
- Add support for exporting reports (e.g., issued books, available books).
## Contributing
Contributions are welcome! Please follow these steps:
1. Fork the repository.
2. Create a new branch (`feature-branch-name`).
3. Commit your changes.
4. Submit a pull request.




