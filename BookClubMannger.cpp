//
// Created by Jey on 2019/2/26.
//
#include "DatabaseManager.h"
#include "BookClubMannger.h"
void BookClubMannger::user_login_handle(const cinatra::request& req, cinatra::response& res)
{
    std::cout << "user_login_callback" << std::endl;
    auto username = req.get_query_value("username");
    std::string username_str = std::string(username.data(),username.length());

    auto password = req.get_query_value("password");
    std::string password_str = std::string(password.data(),password.length());
    std::cout << "username : " << username_str << std::endl;
    std::cout << "password : " << password_str << std::endl;
//    nlohmann::json json_res;
}