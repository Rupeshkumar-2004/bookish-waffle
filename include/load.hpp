#ifndef USER_COMPANY_HPP
#define USER_COMPANY_HPP
#include <iostream>
#include <string>
#include <vector>
#include "json.hpp"
#include <fstream> 
using json = nlohmann::json;

//
// ===== User & Company Data =====
//

struct user_data {
    std::string name;
    std::string username;
    std::string email;
    std::string password;
    std::vector<std::string> connections;  // similar to classroomIds, but for networking

    user_data(const std::string& thename, const std::string& theusername,
              const std::string& theemail, const std::string& thepassword)
        : name(thename),
          username(theusername),
          email(theemail),
          password(thepassword) {}
};

struct user_link {
    user_data* data = nullptr;
    user_link* next = nullptr;
};

struct company_data {
    std::string name;
    std::string username;
    std::string email;
    std::string password;
    std::vector<std::string> jobIds;  // placeholder for future expansion

    company_data(const std::string& thename, const std::string& theusername,
                 const std::string& theemail, const std::string& thepassword)
        : name(thename),
          username(theusername),
          email(theemail),
          password(thepassword) {}
};

struct company_link {
    company_data* data = nullptr;
    company_link* next = nullptr;
};

struct email_link {
    std::string* username = nullptr;
    std::string* email = nullptr;
    email_link* next = nullptr;
};

//
// ===== JSON Serialization =====
//

void to_json(json& j, const user_data& u) {
    j = json{
        {"name", u.name},
        {"email", u.email},
        {"password", u.password},
        {"username", u.username},
        {"connections", u.connections}
    };
}

void to_json(json& j, const company_data& c) {
    j = json{
        {"name", c.name},
        {"email", c.email},
        {"password", c.password},
        {"username", c.username},
        {"jobIds", c.jobIds}
    };
}

//
// ===== HashTables for Users & Companies =====
//

class hashTables {
    user_link** users;
    company_link** companies;
    email_link** emails;
    int size;

    uint32_t fnv1a(std::string s) {
        const uint32_t basis = 2166136261u;
        const uint32_t prime = 16777619u;
        uint32_t hash = basis;
        for (unsigned char c : s) {
            hash ^= c;
            hash *= prime;
        }
        return hash;
    }

    void makeUser_hashtable(int& size, std::ifstream& file) {
        json data;
        file >> data;
        for (const auto& user : data) {
            uint32_t index = fnv1a(user["username"]) % size;
            user_data* new_user = new user_data(user["name"], user["username"], user["email"], user["password"]);
            user_link* newnode = new user_link;
            newnode->data = new_user;
            if (users[index]) {
                newnode->next = users[index];
                users[index] = newnode;
            } else {
                users[index] = newnode;
            }

            index = fnv1a(user["email"]) % (size * 2);
            std::string* new_email = new std::string(user["email"]);
            std::string* new_username = new std::string(user["username"]);
            email_link* email_node = new email_link;
            email_node->email = new_email;
            email_node->username = new_username;
            if (emails[index]) {
                email_node->next = emails[index];
                emails[index] = email_node;
            } else {
                emails[index] = email_node;
            }
        }
    }

    void makeCompany_hashtable(int& size, std::ifstream& file) {
        json data;
        file >> data;
        for (const auto& comp : data) {
            uint32_t index = fnv1a(comp["username"]) % size;
            company_data* new_company = new company_data(comp["name"], comp["username"], comp["email"], comp["password"]);
            company_link* newnode = new company_link;
            newnode->data = new_company;
            if (companies[index]) {
                newnode->next = companies[index];
                companies[index] = newnode;
            } else {
                companies[index] = newnode;
            }

            index = fnv1a(comp["email"]) % (size * 2);
            std::string* new_email = new std::string(comp["email"]);
            std::string* new_username = new std::string(comp["username"]);
            email_link* email_node = new email_link;
            email_node->email = new_email;
            email_node->username = new_username;
            if (emails[index]) {
                email_node->next = emails[index];
                emails[index] = email_node;
            } else {
                emails[index] = email_node;
            }
        }
    }

public:
    hashTables() {
        size = 100;
        emails = new email_link*[size * 2];
        users = new user_link*[size];
        companies = new company_link*[size];

        for (int i = 0; i < size * 2; i++) {
            emails[i] = nullptr;
        }
        for (int i = 0; i < size; ++i) {
            users[i] = nullptr;
            companies[i] = nullptr;
        }

        std::ifstream userFile("Data/users.json");
        if (!userFile.is_open()) {
            throw std::runtime_error("Could not open users.json");
        }

        std::ifstream companyFile("Data/companies.json");
        if (!companyFile.is_open()) {
            throw std::runtime_error("Could not open companies.json");
        }

        makeUser_hashtable(size, userFile);
        makeCompany_hashtable(size, companyFile);
    }

    user_data* findUser(std::string& s) {
        uint32_t index = fnv1a(s) % size;
        user_link* node = users[index];
        while (node) {
            if (node->data->username == s) return node->data;
            node = node->next;
        }
        return nullptr;
    }

    company_data* findCompany(std::string& s) {
        uint32_t index = fnv1a(s) % size;
        company_link* node = companies[index];
        while (node) {
            if (node->data->username == s) return node->data;
            node = node->next;
        }
        return nullptr;
    }

    void addUser(user_data* new_user) {
        uint32_t index = fnv1a(new_user->username) % size;
        user_link* newnode = new user_link;
        newnode->data = new_user;
        if (users[index]) {
            newnode->next = users[index];
            users[index] = newnode;
        } else {
            users[index] = newnode;
        }

        index = fnv1a(new_user->email) % (size * 2);
        std::string* new_email = new std::string(new_user->email);
        std::string* new_username = new std::string(new_user->username);
        email_link* email_node = new email_link;
        email_node->email = new_email;
        email_node->username = new_username;
        if (emails[index]) {
            email_node->next = emails[index];
            emails[index] = email_node;
        } else {
            emails[index] = email_node;
        }
    }

    void addCompany(company_data* new_company) {
        uint32_t index = fnv1a(new_company->username) % size;
        company_link* newnode = new company_link;
        newnode->data = new_company;
        if (companies[index]) {
            newnode->next = companies[index];
            companies[index] = newnode;
        } else {
            companies[index] = newnode;
        }

        index = fnv1a(new_company->email) % (size * 2);
        std::string* new_email = new std::string(new_company->email);
        std::string* new_username = new std::string(new_company->username);
        email_link* email_node = new email_link;
        email_node->email = new_email;
        email_node->username = new_username;
        if (emails[index]) {
            email_node->next = emails[index];
            emails[index] = email_node;
        } else {
            emails[index] = email_node;
        }
    }

    std::string* findUsername(std::string& theEmail) {
        uint32_t index = fnv1a(theEmail) % (size * 2);
        email_link* node = emails[index];
        while (node) {
            if (*(node->email) == theEmail) return node->username;
            node = node->next;
        }
        return nullptr;
    }

    ~hashTables() {
        std::cout << "Saving user & company data to files..." << std::endl;

        json users_json_array = json::array();
        for (int i = 0; i < size; ++i) {
            user_link* curr = users[i];
            while (curr != nullptr) {
                users_json_array.push_back(*(curr->data));
                curr = curr->next;
            }
        }
        std::ofstream userFile("Data/users.json");
        userFile << users_json_array.dump(4);
        userFile.close();

        json companies_json_array = json::array();
        for (int i = 0; i < size; ++i) {
            company_link* curr = companies[i];
            while (curr != nullptr) {
                companies_json_array.push_back(*(curr->data));
                curr = curr->next;
            }
        }
        std::ofstream companyFile("Data/companies.json");
        companyFile << companies_json_array.dump(4);
        companyFile.close();

        for (int i = 0; i < size; i++) {
            user_link* curr1 = users[i];
            while (curr1) {
                user_link* next = curr1->next;
                delete curr1->data;
                delete curr1;
                curr1 = next;
            }
            company_link* curr2 = companies[i];
            while (curr2) {
                company_link* next = curr2->next;
                delete curr2->data;
                delete curr2;
                curr2 = next;
            }
        }
        delete[] users;
        delete[] companies;

        for (int i = 0; i < size * 2; i++) {
            email_link* curr = emails[i];
            while (curr) {
                email_link* next = curr->next;
                delete curr->email;
                delete curr->username;
                delete curr;
                curr = next;
            }
        }
        delete[] emails;
    }
};

#endif
