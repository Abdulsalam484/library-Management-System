#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <list>
#include <map>
#include <algorithm>
#include <windows.h>
using namespace std;

void setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

struct Book {
    int id;
    string title;
    string author;
    bool isIssued;

    Book(int bookId, string bookTitle, string bookAuthor, bool issued = false)
        : id(bookId), title(bookTitle), author(bookAuthor), isIssued(issued) {}
};

class Library {
private:
    list<Book> books; // Linked list to store books
    map<int, list<Book>::iterator> bookMap; // Map with iterator to list for compatibility
    stack<Book> deletedBooks; // Stack for undoing deletions
    queue<int> issueRequests; // Queue for managing book issue requests

    void saveToFile() {
        ofstream file("library_data.txt");
        for (list<Book>::iterator it = books.begin(); it != books.end(); ++it) {
            file << it->id << "\n" << it->title << "\n" << it->author << "\n" << it->isIssued << "\n";
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file("library_data.txt");
        if (file) {
            int id;
            string title, author;
            bool isIssued;
            while (file >> id) {
                file.ignore();
                getline(file, title);
                getline(file, author);
                file >> isIssued;
                file.ignore();
                books.push_back(Book(id, title, author, isIssued));
                bookMap[id] = --books.end();
            }
            file.close();
        }
    }

public:
    Library() {
        loadFromFile();
    }

    ~Library() {
        saveToFile();
    }

    void addBook(int id, string title, string author) {
        books.push_back(Book(id, title, author));
        bookMap[id] = --books.end();
        saveToFile();
    }

    void searchBookById(int id) {
        if (bookMap.find(id) != bookMap.end()) {
            displayBookDetails(*bookMap[id]);
        } else {
            cout << "Book not found." << endl;
        }
    }

    void searchBookByTitle(string title) {
        for (list<Book>::iterator it = books.begin(); it != books.end(); ++it) {
            if (it->title == title) {
                displayBookDetails(*it);
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void issueBook(int id, string student) {
        if (bookMap.find(id) != bookMap.end() && !bookMap[id]->isIssued) {
            bookMap[id]->isIssued = true;
            saveToFile();
            cout << "Book issued to " << student << "." << endl;
        } else {
            cout << "Book is either not found or already issued." << endl;
        }
    }

    void returnBook(int id) {
        if (bookMap.find(id) != bookMap.end() && bookMap[id]->isIssued) {
            bookMap[id]->isIssued = false;
            saveToFile();
            cout << "Book returned." << endl;
        } else {
            cout << "Book is either not found or wasn't issued." << endl;
        }
    }

    void listAllBooks() {
        books.sort(compareBooks);
        for (list<Book>::iterator it = books.begin(); it != books.end(); ++it) {
            displayBookDetails(*it);
        }
    }

    static bool compareBooks(const Book& a, const Book& b) {
        return a.title < b.title;
    }

    void deleteBook(int id) {
        map<int, list<Book>::iterator>::iterator it = bookMap.find(id);
        if (it != bookMap.end()) {
            deletedBooks.push(*it->second);
            books.erase(it->second);
            bookMap.erase(it);
            saveToFile();
            cout << "Book deleted." << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }

    void undoLastDeletion() {
        if (!deletedBooks.empty()) {
            Book restored = deletedBooks.top();
            deletedBooks.pop();
            books.push_back(restored);
            bookMap[restored.id] = --books.end();
            saveToFile();
            cout << "Last deleted book restored." << endl;
        } else {
            cout << "No deleted books to undo." << endl;
        }
    }

    void displayBookDetails(const Book& book) const {
        setConsoleColor(10); // Green for output
        cout << "ID: " << book.id << ", Title: " << book.title
             << ", Author: " << book.author
             << ", Status: " << (book.isIssued ? "Issued" : "Available") << endl;
        setConsoleColor(7); // Reset to default
    }
};

void displayTitle() {
    setConsoleColor(14); // Yellow for title
    cout << "\t\t\t\t===============================================================\n";
    cout << "\t\t\t\t             LIBRARY MANAGEMENT SYSTEM\n";
    cout << "\t\t\t\t===============================================================\n";
    setConsoleColor(7); // Reset to default
}

int main() {
    Library lib;
    int choice, id;
    string title, author, student;
    char continueProgram;

    do {
        system("cls"); // Clear the screen
        displayTitle(); // Display the title after clearing the screen

        setConsoleColor(11); // Cyan for menu options
        cout << "\n[1] Add Book\n";
        cout << "[2] Search Book by ID\n";
        cout << "[3] Search Book by Title\n";
        cout << "[4] Issue Book\n";
        cout << "[5] Return Book\n";
        cout << "[6] List All Books\n";
        cout << "[7] Delete Book\n";
        cout << "[8] Undo Last Deletion\n";
        cout << "[9] Exit\n";
        cout << "============================================" << endl;
        setConsoleColor(9);
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        system("cls"); // Clear the screen again
        displayTitle(); // Display the title again before showing the result

        switch (choice) {
            case 1:
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                lib.addBook(id, title, author);
                cout << "Book has been added: " << title << endl;
                break;

            case 2:
                cout << "Enter book ID: ";
                cin >> id;
                lib.searchBookById(id);
                break;

            case 3:
                cin.ignore();
                cout << "Enter book title: ";
                getline(cin, title);
                lib.searchBookByTitle(title);
                break;

            case 4:
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter student name: ";
                getline(cin, student);
                lib.issueBook(id, student);
                break;

            case 5:
                cout << "Enter book ID: ";
                cin >> id;
                lib.returnBook(id);
                break;

            case 6:
                lib.listAllBooks();
                break;

            case 7:
                cout << "Enter book ID: ";
                cin >> id;
                lib.deleteBook(id);
                break;

            case 8:
                lib.undoLastDeletion();
                break;

            case 9:
                cout << "Exiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

        if (choice != 9) {
            cout << "\nDo you want to continue? (Y/N): ";
            cin >> continueProgram;
            continueProgram = tolower(continueProgram); // Normalize input
        }

    } while (choice != 9 && continueProgram == 'y');

    return 0;
}

