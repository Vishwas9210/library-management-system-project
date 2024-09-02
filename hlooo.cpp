#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    int availableCopies;

    void addBook(int bookId, string bookTitle, string bookAuthor, int copies) {
        id = bookId;
        title = bookTitle;
        author = bookAuthor;
        availableCopies = copies;
    }

    void displayBook() {
        cout << "Book ID: " << id << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        if (availableCopies > 0) {
            cout << "Status: Available (" << availableCopies << " copies)" << endl;
        } else {
            cout << "Status: Not Available" << endl;
        }
    }
};

class Library {
public:
    Book books[100];
    int bookCount;

    Library() {
        bookCount = 0;
        loadFromFile();
    }

    void saveToFile() {
        ofstream outFile("library_data.txt");
        if (outFile.is_open()) {
            for (int i = 0; i < bookCount; i++) {
                outFile << books[i].id << endl;
                outFile << books[i].title << endl;
                outFile << books[i].author << endl;
                outFile << books[i].availableCopies << endl;
            }
            outFile.close();
        } else {
            cout << "Unable to open file for writing." << endl;
        }
    }

    void loadFromFile() {
        ifstream inFile("library_data.txt");
        if (inFile.is_open()) {
            while (inFile >> books[bookCount].id && bookCount < 100) {
                inFile.ignore(); // Ignore newline character after id
                getline(inFile, books[bookCount].title);
                getline(inFile, books[bookCount].author);
                inFile >> books[bookCount].availableCopies;
                inFile.ignore(); // Ignore newline character after availableCopies
                bookCount++;
            }
            inFile.close();
        }
    }

    void addBook() {
        if (bookCount < 100) {
            int id, copies;
            string title;
            string author;

            cout << "Enter Book ID: ";
            cin >> id;
            cin.ignore(); // Ignore the newline character after entering the ID
            cout << "Enter Book Title: ";
            getline(cin, title);
            cout << "Enter Book Author: ";
            getline(cin, author);
            cout << "Enter number of copies: ";
            cin >> copies;

            books[bookCount].addBook(id, title, author, copies);
            bookCount++;
            saveToFile();
            cout << "Book added successfully!" << endl;
        } else {
            cout << "Library is full. Cannot add more books." << endl;
        }
    }

    void displayBooks() {
        if (bookCount == 0) {
            cout << "No books available in the library." << endl;
        } else {
            for (int i = 0; i < bookCount; i++) {
                books[i].displayBook();
                cout << "----------------------" << endl;
            }
        }
    }

    void borrowBook() {
        int id;
        cout << "Enter Book ID to borrow: ";
        cin >> id;

        for (int i = 0; i < bookCount; i++) {
            if (books[i].id == id) {
                if (books[i].availableCopies > 0) {
                    books[i].availableCopies--;
                    saveToFile();  // Save changes to file
                    cout << "Book borrowed successfully!" << endl;
                } else {
                    cout << "Book is not available." << endl;
                }
                return;
            }
        }

        cout << "Book not found." << endl;
    }

    void returnBook() {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;

        for (int i = 0; i < bookCount; i++) {
            if (books[i].id == id) {
                books[i].availableCopies++;
                saveToFile();  // Save changes to file
                cout << "Book returned successfully!" << endl;
                return;
            }
        }

        cout << "Book not found." << endl;
    }

    void adminMenu() {
        int choice;
        do {
            cout << endl;
            cout << "*******Admin Menu*******" << endl;
            cout << "1. Add Book" << endl;
            cout << "2. Display All Books" << endl;
            cout << "3. Exit Admin Menu" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addBook();
                    break;
                case 2:
                    displayBooks();
                    break;
                case 3:
                    cout << "Exiting Admin Menu..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 3);
    }

    void customerMenu() {
        int choice;
        do {
            cout << endl;
            cout << "*******Customer Menu*******" << endl;
            cout << "1. Borrow Book" << endl;
            cout << "2. Return Book" << endl;
            cout << "3. Check Book Availability" << endl;
            cout << "4. Exit Customer Menu" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    borrowBook();
                    break;
                case 2:
                    returnBook();
                    break;
                case 3:
                    displayBooks();
                    break;
                case 4:
                    cout << "Exiting Customer Menu..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 4);
    }
};

int main() {
    Library lib;
    int userchoice;
    string admin_password;
    string admin_id;
    string customer_mobile_no;
    string customer_password;

    do {
        cout << endl;
        cout << "*******Library Management System*******" << endl;
        cout << "1. Customer Menu" << endl;
        cout << "2. Admin Menu" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> userchoice;

        switch (userchoice) {
            case 1: {
                do {
                    cout << endl << "Enter your mobile number: ";
                    cin >> customer_mobile_no;

                    if (customer_mobile_no.length() != 10) {
                        cout << "Mobile number must be exactly 10 digits long. Please try again." << endl;
                    }
                } while (customer_mobile_no.length() != 10);

                cout << "Enter your password: ";
                cin >> customer_password;

                if (customer_password == "223") {
                    lib.customerMenu();
                } else {
                    cout << "Invalid mobile number or password!" << endl;
                }
                break;
            }
            case 2: {
                cout << endl << "Enter admin ID: ";
                cin >> admin_id;
                cout << "Enter admin password: ";
                cin >> admin_password;

                if (admin_id == "vishwas" && admin_password == "223") {
                    lib.adminMenu();
                } else {
                    cout << "Invalid admin ID or password!" << endl;
                }
                break;
            }
            case 3:
                cout << "Exiting the program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (userchoice != 3);

    return 0;
}
