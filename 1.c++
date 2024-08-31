/*
#include <iostream>
#include <string>
#include <map>

using namespace std;

class PhoneBook {
private:
    map<string, string> contacts;

public:
    void addContact(string name, string phoneNumber) {
        contacts[name] = phoneNumber;
        cout << "Contact " << name << " added with phone number " << phoneNumber << endl;
    }

    void deleteContact(string name) {
        if (contacts.find(name) != contacts.end()) {
            contacts.erase(name);
            cout << "Contact " << name << " deleted" << endl;
        } else {
            cout << "Contact " << name << " not found" << endl;
        }
    }

    void updateContact(string name, string newPhoneNumber) {
        if (contacts.find(name) != contacts.end()) {
            contacts[name] = newPhoneNumber;
            cout << "Contact " << name << " updated with new phone number " << newPhoneNumber << endl;
        } else {
            cout << "Contact " << name << " not found" << endl;
        }
    }

    void searchContact(string name) {
        if (contacts.find(name) != contacts.end()) {
            cout << "Contact " << name << " found with phone number " << contacts[name] << endl;
        } else {
            cout << "Contact " << name << " not found" << endl;
        }
    }

    void displayContacts() {
        if (!contacts.empty()) {
            cout << "Phone Book:" << endl;
            for (auto& contact : contacts) {
                cout << contact.first << ": " << contact.second << endl;
            }
        } else {
            cout << "Phone Book is empty" << endl;
        }
    }
};

int main() {
    PhoneBook phoneBook;

    int choice;
    string name, phoneNumber, newPhoneNumber;

    while (true) {
        cout << "\nPhone Book Menu:" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Delete Contact" << endl;
        cout << "3. Update Contact" << endl;
        cout << "4. Search Contact" << endl;
        cout << "5. Display Contacts" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter contact name: ";
                cin >> name;
                cout << "Enter phone number: ";
                cin >> phoneNumber;
                phoneBook.addContact(name, phoneNumber);
                break;
            case 2:
                cout << "Enter contact name: ";
                cin >> name;
                phoneBook.deleteContact(name);
                break;
            case 3:
                cout << "Enter contact name: ";
                cin >> name;
                cout << "Enter new phone number: ";
                cin >> newPhoneNumber;
                phoneBook.updateContact(name, newPhoneNumber);
                break;
            case 4:
                cout << "Enter contact name: ";
                cin >> name;
                phoneBook.searchContact(name);
                break;
            case 5:
                phoneBook.displayContacts();
                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
*/

#include "crow.h"
#include <map>
#include <string>

using namespace std;

class PhoneBook {
private:
    map<string, string> contacts;

public:
    void addContact(string name, string phoneNumber) {
        contacts[name] = phoneNumber;
    }

    void deleteContact(string name) {
        if (contacts.find(name) != contacts.end()) {
            contacts.erase(name);
        }
    }

    void updateContact(string name, string newPhoneNumber) {
        if (contacts.find(name) != contacts.end()) {
            contacts[name] = newPhoneNumber;
        }
    }

    void searchContact(string name) {
        if (contacts.find(name) != contacts.end()) {
            return crow::json::wvalue{{"name", name}, {"phoneNumber", contacts[name]}};
        } else {
            return crow::json::wvalue{{"error", "Contact not found"}};
        }
    }

    void displayContacts() {
        crow::json::wvalue contactsJson;
        for (auto& contact : contacts) {
            contactsJson[contact.first] = contact.second;
        }
        return contactsJson;
    }
};

int main() {
    PhoneBook phoneBook;

    crow::SimpleApp app;

    CROW_ROUTE(app, "/addContact")
    ([](const crow::request& req){
        phoneBook.addContact(req.param("name"), req.param("phoneNumber"));
        return crow::response(200, "Contact added successfully");
    });

    CROW_ROUTE(app, "/deleteContact")
    ([](const crow::request& req){
        phoneBook.deleteContact(req.param("name"));
        return crow::response(200, "Contact deleted successfully");
    });

    CROW_ROUTE(app, "/updateContact")
    ([](const crow::request& req){
        phoneBook.updateContact(req.param("name"), req.param("newPhoneNumber"));
        return crow::response(200, "Contact updated successfully");
    });

    CROW_ROUTE(app, "/searchContact")
    ([](const crow::request& req){
        return phoneBook.searchContact(req.param("name"));
    });

    CROW_ROUTE(app, "/displayContacts")
    ([](){
        return phoneBook.displayContacts();
    });

    app.port(18080).run();
}