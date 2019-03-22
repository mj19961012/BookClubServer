#include <iostream>
#include "feather/ormpp/ormpp_cfg.hpp"
#include "BookClubConfig.h"
#include "BookClubMannger.h"
#include "DatabaseManager.h"


using namespace cinatra;
int main (int argc,char ** argv)
{
//    nanolog::initialize(nanolog::GuaranteedLogger(), "/tmp/", "nanolog", 1);
//
//    int max_thread_num = std::thread::hardware_concurrency();
//    http_server server(max_thread_num);
//    server.listen(API_HOST_IP, API_HOST_PORT);
//
//    DatabaseManager::getInstance()->init_database(API_DATABASE_IP,"bc_info_db","root","!Qaz1234");
//    user_info userinfo;
//    userinfo.phone_number = "19910120215";
//    userinfo.head_image = "/res/default.png";
//    userinfo.nick_name = "Jey";
//    userinfo.pass_word = "!Qaz1234";
//    userinfo.user_id = "boost::uuids::to_string(a_uuid);";
//    userinfo.city = "成都";
//    userinfo.school = "加里敦大学";

//    std::cout << DatabaseManager::getInstance ()->insert_userinfo (userinfo) << std::endl;
//    std::cout << DatabaseManager::getInstance ()->check_username_password ("19910120215","!Qaz1234") << std::endl;
//    auto tmp_userinfo = DatabaseManager::getInstance ()->get_userinfo ("19910120215","!Qaz1234");
//    std::cout << tmp_userinfo.user_id << std::endl;

//    nlohmann::json json_temp(userinfo);
//
//    std::cout << json_temp.dump() << std::endl;

//    BookClubMannger BC_Manager;
//
//    try
//    {
//        server.set_http_handler<GET, POST>("/user_login", &BookClubMannger::user_login_handle, &BC_Manager);
//    }
//    catch (...)
//    {
//        std::cout << "error" << std::endl;
//    }
//
//
//    server.run();

//    nlohmann::json json_city;
//    std::ifstream file("../city.json");
//    file >> json_city;
//
//    for(auto iter = json_city.begin(); iter!=json_city.end(); ++iter)
//    {
//        std::cout << "parent:" << iter.key().c_str() << std::endl;
//        for(auto it = iter.value()["child"].begin(); it != iter.value()["child"].end(); ++it)
//        {
//            std::cout << iter.key().c_str() << "--" << it.key().c_str() << it.value()["name"].get<std::string>().c_str() << std::endl;
//        }
//    }

    //std::cout << json_city.dump () << std::endl;


    std::getchar ();
    return 0;
//    database::getInstance()->insert_user(1, "123", "123", 45, "123456789", "华北科技学院");
//    database::getInstance()->delete_commodity(1);
//    database::getInstance()->query_commodity();
//    database::getInstance()->query_customer();
//    database::getInstance()->query_order();
//    database::getInstance()->query_stock();
//    database::getInstance()->query_supplier();
//    database::getInstance()->query_user();
//    database::getInstance()->query_userinfo();
//    ormpp::dbng<ormpp::mysql> mysql;
//    const char* ip = "127.0.0.1";
//    mysql.connect(ip, "root", "huxingde08", "aaa");
//    mysql.create_datatable<commodity>();
//    commodity s = {1, "tom", 0, 19, 1.5};
//    commodity s1 = {1, "jack", 1, 20, 2.5};
//    commodity s2 = {1, "mke", 2, 21, 3.5};
//    std::vector<commodity> v{s1, s2};
//    mysql.insert(v);
    //database::getInstance()->check_user_pas("123", "123");
    //database::getInstance()->insert_user("123","123", 12, "123", "123");
    return 0;
}