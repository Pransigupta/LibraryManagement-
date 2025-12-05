#include <iostream>
#include <vector>
#include <string>
using namespace std;

// -------------------- STRUCTS --------------------

struct Book {
    string name;
    string author;
    string id;
    string edition;
    string type;
    bool issued = false;
};

struct User {
    string username;
    string userid;
    string branch;
    int year;
};

struct IssueRecord {
    string userid;
    string bookid;
    int issueDay;
};

// -------------------- GLOBAL DATA --------------------

vector<Book> books;
vector<User> users;
vector<IssueRecord> issues;

// -------------------- CLASS DEFINITIONS --------------------

class LibrarySystem {
public:
    // ---------------- ADD USER ----------------
    void createUser() {
        User u;
        cout << "\n--- Create New User ---\n";
        cout << "Enter username: ";
        cin >> u.username;
        cout << "Enter user ID: ";
        cin >> u.userid;
        cout << "Enter branch: ";
        cin >> u.branch;
        cout << "Enter year: ";
        cin >> u.year;

        users.push_back(u);
        cout << "\nUser account created successfully!\n";
    }

    // ---------------- SHOW USERS ----------------
    void showUsers() {
        cout << "\n--- User List ---\n";
        if (users.empty()) {
            cout << "No users found.\n";
            return;
        }

        cout << "S.No   Username   UserID   Branch   Year\n";
        int i = 1;
        for (auto &u : users) {
            cout << i++ << ".     " << u.username << "     "
                 << u.userid << "     " << u.branch
                 << "     " << u.year << endl;
        }
    }

    // ---------------- ADD BOOK ----------------
    void addBook() {
        Book b;
        cout << "\n--- Add New Book ---\n";
        cout << "Enter book name: ";
        cin >> b.name;
        cout << "Enter author name: ";
        cin >> b.author;
        cout << "Enter book ID: ";
        cin >> b.id;
        cout << "Enter edition: ";
        cin >> b.edition;
        cout << "Enter book type: ";
        cin >> b.type;

        books.push_back(b);
        cout << "\nBook added successfully!\n";
    }

    // ---------------- SHOW BOOKS ----------------
    void showBooks() {
        cout << "\n--- Book List ---\n";
        if (books.empty()) {
            cout << "No books available.\n";
            return;
        }

        cout << "S.No   Name   Author   ID   Edition   Type   Status\n";
        int i = 1;
        for (auto &b : books) {
            cout << i++ << ".   " << b.name << "   "
                 << b.author << "   " << b.id << "   "
                 << b.edition << "   " << b.type
                 << "   " << (b.issued ? "Issued" : "Available") << endl;
        }
    }

    // ---------------- ISSUE BOOK ----------------
    void issueBook() {
        string uid, bid;
        cout << "\nEnter user ID: ";
        cin >> uid;

        if (!isValidUser(uid)) {
            cout << "User not found!\n";
            return;
        }

        cout << "Enter book ID to issue: ";
        cin >> bid;

        for (auto &b : books) {
            if (b.id == bid) {
                if (b.issued) {
                    cout << "Book already issued!\n";
                    return;
                }

                b.issued = true;

                IssueRecord rec;
                rec.userid = uid;
                rec.bookid = bid;

                cout << "Enter issue day (1-31): ";
                cin >> rec.issueDay;

                issues.push_back(rec);

                cout << "\nBook issued successfully!\n";
                return;
            }
        }

        cout << "Book not found!\n";
    }

    // ---------------- RETURN BOOK ----------------
    void returnBook() {
        string bid;
        int returnDay;

        cout << "\nEnter book ID to return: ";
        cin >> bid;

        for (auto &b : books) {
            if (b.id == bid) {
                if (!b.issued) {
                    cout << "This book is not issued!\n";
                    return;
                }

                cout << "Enter return day (1-31): ";
                cin >> returnDay;

                for (auto &r : issues) {
                    if (r.bookid == bid) {
                        int late = returnDay - r.issueDay - 14;

                        if (late > 0) {
                            cout << "\nLate by " << late << " days.\n";
                            cout << "Fine: Rs " << late * 2 << "\n";
                        } else {
                            cout << "\nReturned on time. No fine.\n";
                        }

                        b.issued = false;
                        return;
                    }
                }
            }
        }

        cout << "Book not found!\n";
    }

private:
    bool isValidUser(string uid) {
        for (auto &u : users)
            if (u.userid == uid)
                return true;
        return false;
    }
};

// -------------------- MAIN FUNCTION --------------------

int main() {
    LibrarySystem lib;
    int choice;

    cout << "\n===== Welcome to Library Management System =====\n";

    do {
        cout << "\n--------------- MENU ---------------\n";
        cout << "1. Admin Login\n";
        cout << "2. Show Books\n";
        cout << "3. Create User\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "0. Exit\n";
        cout << "------------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string u, p;
            cout << "Enter admin username: ";
            cin >> u;
            cout << "Enter password: ";
            cin >> p;

            if (u == "Admin@123" && p == "1234") {
                int c2;
                do {
                    cout << "\n--- Admin Panel ---\n";
                    cout << "1. Add Book\n";
                    cout << "2. Show Books\n";
                    cout << "3. Show Users\n";
                    cout << "0. Back\n";
                    cin >> c2;

                    switch (c2) {
                    case 1: lib.addBook(); break;
                    case 2: lib.showBooks(); break;
                    case 3: lib.showUsers(); break;
                    }
                } while (c2 != 0);
            } else {
                cout << "Invalid credentials!\n";
            }
            break;
        }

        case 2: lib.showBooks(); break;
        case 3: lib.createUser(); break;
        case 4: lib.issueBook(); break;
        case 5: lib.returnBook(); break;

        case 0: cout << "Exiting...\n"; break;

        default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
