//
// Created by Jey on 2019/2/26.
//

#ifndef BOOKCLUBSERVER_BOOKCLUBMANNGER_H
#define BOOKCLUBSERVER_BOOKCLUBMANNGER_H
#include "feather/cinatra/http_server.hpp"
#include <iostream>
#include "DatabaseManager.h"
#include "feather/inja/inja.hpp"

class BookClubMannger
{
public:
    void user_login_handle(const cinatra::request& req, cinatra::response& res);
    void user_regist_handle(const cinatra::request& req, cinatra::response& res);
    void init_city_dictionary(const cinatra::request& req, cinatra::response& res);
    void upload_simple_file(const cinatra::request& req, cinatra::response& res);
    void download_simple_file(const cinatra::request& req, cinatra::response& res);
    void get_file_info(const cinatra::request& req, cinatra::response& res);
    void get_messages_list_handle(const cinatra::request& req, cinatra::response& res);
    void send_message_handle(const cinatra::request& req, cinatra::response& res);
    void get_activice_list_handle(const cinatra::request& req, cinatra::response& res);
    void create_new_active_handle(const cinatra::request& req, cinatra::response& res);
    void remove_an_active_handle(const cinatra::request& req, cinatra::response& res);
    void get_articles_list_handle(const cinatra::request& req, cinatra::response& res);
    void create_new_article_handle(const cinatra::request& req, cinatra::response& res);
    void remove_an_article_handle(const cinatra::request& req, cinatra::response& res);
};


#endif //BOOKCLUBSERVER_BOOKCLUBMANNGER_H
