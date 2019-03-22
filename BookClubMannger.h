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
    void init_city_dictionary(const cinatra::request& req, cinatra::response& res);
};


#endif //BOOKCLUBSERVER_BOOKCLUBMANNGER_H
