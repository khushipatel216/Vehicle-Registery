
#include <iostream>
#include <string>
using namespace std;


class LibraryItem {
private:
    string title;
    string author;
    string dueDate;

public:
   
    LibraryItem(string t, string a, string d) {
        title = t;
        author = a;
        dueDate = d;
    }

    
    string getTitle() {
        return title;
    }

    string getAuthor() {
        return author;
    }

    string getDueDate() {
        return dueDate;
    }

    void setTitle(string t) {
        title = t;
    }

    void setAuthor(string a) {
        author = a;
    }

    void setDueDate(string d) {
        dueDate = d;
    }

    virtual void checkOut() = 0;
    virtual void returnItem() = 0;
    virtual void displayDetails() = 0;

    virtual ~LibraryItem() {}
};

class Book : public LibraryItem {
private:
    string ISBN;
    bool issued;

public:
    Book(string t, string a, string d, string isbn)
        : LibraryItem(t, a, d) {

        if (isbn.length() != 13) {
            throw "ISBN must contain 13 characters!";
        }

        ISBN = isbn;
        issued = false;
    }

    void checkOut() override {
        if (issued == true) {
            cout << "Book is already issued.\n";
        } else {
            issued = true;
            cout << "Book issued successfully.\n";
        }
    }

    void returnItem() override {
        if (issued == false) {
            cout << "Book is not issued.\n";
        } else {
            issued = false;
            cout << "Book returned successfully.\n";
        }
    }

    void displayDetails() override {
        cout << "\nType: Book";
        cout << "\nTitle: " << getTitle();
        cout << "\nAuthor: " << getAuthor();
        cout << "\nDue Date: " << getDueDate();
        cout << "\nISBN: " << ISBN;
        cout << "\nStatus: "
             << (issued ? "Issued" : "Available") << endl;
    }
};

class DVD : public LibraryItem {
private:
    int duration;
    bool issued;

public:
    DVD(string t, string a, string d, int minutes)
        : LibraryItem(t, a, d) {

        if (minutes <= 0) {
            throw "DVD duration must be positive!";
        }

        duration = minutes;
        issued = false;
    }

    void checkOut() override {
        if (issued == true) {
            cout << "DVD is already issued.\n";
        } else {
            issued = true;
            cout << "DVD issued successfully.\n";
        }
    }

    void returnItem() override {
        if (issued == false) {
            cout << "DVD is not issued.\n";
        } else {
            issued = false;
            cout << "DVD returned successfully.\n";
        }
    }

    void displayDetails() override {
        cout << "\nType: DVD";
        cout << "\nTitle: " << getTitle();
        cout << "\nAuthor: " << getAuthor();
        cout << "\nDue Date: " << getDueDate();
        cout << "\nDuration: " << duration << " minutes";
        cout << "\nStatus: "
             << (issued ? "Issued" : "Available") << endl;
    }
};

int main() {
    LibraryItem *items[20];

    int count = 0;
    int choice;
    int number;

    do {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Book";
        cout << "\n2. Add DVD";
        cout << "\n3. Display All Items";
        cout << "\n4. Issue Item";
        cout << "\n5. Return Item";
        cout << "\n6. Search Item";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        try {
            if (choice == 1 || choice == 2) {
                if (count >= 20) {
                    throw "Library is full!";
                }

                string title, author, dueDate;

                cout << "Enter title (one word): ";
                cin >> title;

                cout << "Enter author (one word): ";
                cin >> author;

                cout << "Enter due date (DD-MM-YYYY): ";
                cin >> dueDate;

                if (choice == 1) {
                    string isbn;

                    cout << "Enter 13-character ISBN: ";
                    cin >> isbn;

                    items[count] = new Book(
                        title, author, dueDate, isbn
                    );
                } else {
                    int duration;

                    cout << "Enter DVD duration in minutes: ";
                    cin >> duration;

                    items[count] = new DVD(
                        title, author, dueDate, duration
                    );
                }

                count++;
                cout << "Item added successfully!\n";
            }

            else if (choice == 3) {
                if (count == 0) {
                    cout << "Library is empty.\n";
                } else {
                    for (int i = 0; i < count; i++) {
                        cout << "\nItem Number: " << i + 1;
                        items[i]->displayDetails();
                    }
                }
            }

            else if (choice == 4) {
                cout << "Enter item number to issue: ";
                cin >> number;

                if (number < 1 || number > count) {
                    throw "Invalid item number!";
                }

                items[number - 1]->checkOut();
            }

            else if (choice == 5) {
                cout << "Enter item number to return: ";
                cin >> number;

                if (number < 1 || number > count) {
                    throw "Invalid item number!";
                }

                items[number - 1]->returnItem();
            }

            else if (choice == 6) {
                string searchTitle;
                bool found = false;

                cout << "Enter title to search: ";
                cin >> searchTitle;

                for (int i = 0; i < count; i++) {
                    if (items[i]->getTitle() == searchTitle) {
                        items[i]->displayDetails();
                        found = true;
                    }
                }

                if (found == false) {
                    cout << "Item not found.\n";
                }
            }

            else if (choice != 0) {
                cout << "Invalid choice! Try again.\n";
            }
        }

        catch (const char *message) {
            cout << "Error: " << message << endl;
        }

        catch (...) {
            cout << "An unexpected error occurred.\n";
        }

    } while (choice != 0);

   
    for (int i = 0; i < count; i++) {
        delete items[i];
    }

    cout << "Library Management System closed.\n";

    return 0;
}
