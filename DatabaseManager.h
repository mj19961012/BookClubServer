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
    user_info get_userinfo_with_userid(std::string user_id);
    bool check_username_password(std::string phone_number,std::string pass_word);
    bool check_username_exist(std::string phone_number);
    bool insert_userinfo(user_info userinfo);
    bool check_file_is_exist(std::string filemd5);
    file_base_info get_file_info_with_md5(std::string filemd5);
    bool insert_file_base_info(file_base_info fileinfo);
    std::vector<message_info> get_message_list(std::string user_id);
    bool insert_message(message_info msg_info);
private:
    bool m_is_db_inited;
    ormpp::dbng<ormpp::mysql> m_db;

    std::string db_ip;
    std::string db_user;
    std::string db_pass;
    std::string db_name;
};


#endif //BOOKCLUBSERVER_DATABASEMANAGER_H
