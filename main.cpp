#include "crow.h"
#include <iostream>
#include "include/load.hpp"

int main() {
    try {
        hashTables table;

        crow::mustache::set_base("templates");

        crow::SimpleApp app;

        // Home route
        CROW_ROUTE(app, "/")([]() {
            auto page = crow::mustache::load("welcome.html");
            return page.render();
        });

        // Login page
        CROW_ROUTE(app, "/loginpage")([]() {
            auto page = crow::mustache::load("login.html");
            return page.render();
        });

        // Login POST
        CROW_ROUTE(app, "/login_post").methods("POST"_method)([&table](const crow::request& req) -> crow::response {
            auto req_body = crow::query_string(("?" + req.body).c_str());

            std::string email = req_body.get("email");
            std::string pass  = req_body.get("password");
            std::string role  = req_body.get("role");

            std::string* user = table.findUsername(email);

            if (user) {
                if (role == "user") {
                    user_data* data = table.findUser(*user);
                    if (data && data->password == pass) {
                        crow::mustache::context ctx;
                        ctx["user_name"] = data->username;

                        auto page = crow::mustache::load("user_dashboard.html");
                        return crow::response(page.render(ctx));
                    }
                }
                else if (role == "company") {
                    company_data* data = table.findCompany(*user);
                    if (data && data->password == pass) {
                        crow::mustache::context ctx;
                        ctx["company_name"] = data->username;

                        auto page = crow::mustache::load("company_dashboard.html");
                        return crow::response(page.render(ctx));
                    }
                }
                return crow::response("NO SUCH USER");
            }
            return crow::response("NO SUCH USER");
        });

        // Signup page
        CROW_ROUTE(app, "/signup")([]() {
            auto page = crow::mustache::load("signup.html");
            return page.render();
        });

        // Signup POST
        CROW_ROUTE(app, "/signup_post").methods("POST"_method)([&table](const crow::request& req) -> crow::response {
            auto req_body = crow::query_string(("?" + req.body).c_str());

            std::string name     = req_body.get("fullname");
            std::string username = req_body.get("username");
            std::string email    = req_body.get("email");
            std::string pass     = req_body.get("password");
            std::string role     = req_body.get("role");

            if (role == "user") {
                user_data* new_user = new user_data(name, username, email, pass);
                table.addUser(new_user);
                auto page = crow::mustache::load("user_dashboard.html");
                return crow::response(page.render());
            }
            else {
                company_data* new_company = new company_data(name, username, email, pass);
                table.addCompany(new_company);
                auto page = crow::mustache::load("company_dashboard.html");
                return crow::response(page.render());
            }
        });

        // Route from signup → login
        CROW_ROUTE(app, "/signToLoginpage")([]() {
            auto page = crow::mustache::load("login.html");
            return page.render();
        });

        std::cout << "Server running at http://localhost:18080\n";

        app.port(18080).multithreaded().run();
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
    }
}
