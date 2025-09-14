// User.hpp
#pragma once
#include <string>
#include <unordered_map>

// ----------------- USER STRUCT -----------------
struct User {
    std::string userId;        // Unique identifier (e.g., email)
    std::string username;      // Display name
    std::string hashedPassword;// Hashed password (never store raw)
    bool isCompany;            // true = company, false = normal job seeker
};

// ----------------- GLOBAL STORAGE -----------------
inline std::unordered_map<std::string, User> user_data;
