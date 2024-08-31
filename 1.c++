

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