//
// Created by Jey on 2019/2/26.
//

#ifndef BOOKCLUBSERVER_DATABASEMANAGER_H
#define BOOKCLUBSERVER_DATABASEMANAGER_H

#include "BookClubEntity.hpp"

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();

    static DatabaseManager * getInstance()
    {
        static  DatabaseManager * instance = new DatabaseManager;
        return instance;
    }

    bool init_database(std::string db_ip,std::string db_name,std::string username,std::string password);
    user_info get_userinfo(std::string phone_number,std::string pass_word);
    bool check_username_password(std::string phone_number,std::string pass_word);
    bool insert_userinfo(user_info userinfo);
private:
    bool m_is_db_inited;
    ormpp::dbng<ormpp::mysql> m_db;

    std::string db_ip;
    std::string db_user;
    std::string db_pass;
    std::string db_name;
};


#endif //BOOKCLUBSERVER_DATABASEMANAGER_H
