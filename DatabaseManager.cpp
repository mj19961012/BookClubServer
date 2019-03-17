//
// Created by Jey on 2019/2/26.
//

#include "DatabaseManager.h"

DatabaseManager::DatabaseManager()
    :m_is_db_inited(false)
    ,m_db()
{

}

DatabaseManager::~DatabaseManager()
{

}

bool DatabaseManager::init_database(std::string db_ip,std::string db_name,std::string username,std::string password)
{
    if (m_is_db_inited)
    {
        return m_is_db_inited;
    }

    this->db_ip = db_ip;
    this->db_name = db_name;
    this->db_pass = password;
    this->db_user = username;

    if (!m_db.connect(this->db_ip.c_str(),this->db_user.c_str(),this->db_pass.c_str(),this->db_name.c_str()))
    {
        std::cout << "database_connect_error" << std::endl;
        return false;
    }
    else
    {
        std::cout << "connect_success" << std::endl;
    }

//    struct user_info
//    {
//        int id;
//        std::string user_id;
//        std::string phone_number;
//        std::string nick_name;
//        std::string user_name;
//        std::string pass_word;
//        std::string school;
//        std::string city;
//        std::string head_image;
//        int funs_number;
//        int article_number;
//        int action_number;
//    };
    ormpp_auto_key user_info_key{"id"};
    ormpp_not_null user_info_not_null{{"user_id","user_name","pass_word"}};

    if (!m_db.create_datatable<user_info>(user_info_key,user_info_not_null))
    {
        std::cout << "database_create_user_base_info_error" << std::endl;
        return false;
    }
}

user_info DatabaseManager::get_userinfo(std::string phone_number,std::string pass_word)
{
    auto result = m_db.query<user_info>(
            "select * from user_info where phone_number = '" + phone_number + "' and pass_word = '" + pass_word + "'");

    if(!result.empty())
    {
        for (auto &user:result)
        {
            return user;
        }
    }
}

bool DatabaseManager::check_username_password(std::string phone_number,std::string pass_word)
{
auto result = m_db.query<user_info>(
        "select * from user_info where phone_number = '" + phone_number + "' and pass_word = '" + pass_word + "'");

return result.empty ();
}

bool DatabaseManager::insert_userinfo(user_info userinfo)
{
    auto result = m_db.query<user_info>("select * from user_info where phone_number = '" + userinfo.phone_number + "'");

    int res = INT_MIN;
    if (result.empty())
    {
        res = m_db.insert<user_info>(userinfo);
    }
    return res == INT_MIN;
}

