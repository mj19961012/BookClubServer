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

    DatabaseManager::getInstance ()->check_username_password (username_str,password_str);
    auto tmp_userinfo = DatabaseManager::getInstance ()->get_userinfo (username_str,password_str);

    nlohmann::json json_user(tmp_userinfo);

    nlohmann::json json_res;
    if (!json_user.empty ())
    {
        json_res["code"] = 200;
        json_res["user"] = json_user;
    }
    else
    {
        json_res["code"] = -100;
    }

    res.set_status_and_content(cinatra::status_type::ok,json_res.dump());
}

void BookClubMannger::init_city_dictionary(const cinatra::request& req, cinatra::response& res)
{
    nlohmann::json json_city;
    std::ifstream file("../city.json");
    file >> json_city;

    nlohmann::json json_res;
    if (!json_city.empty ())
    {
        json_res["code"] = 200;
        json_res["city"] = json_city;
    }
    else
    {
        json_res["code"] = -100;
    }

    res.set_status_and_content(cinatra::status_type::ok,json_res.dump());
}