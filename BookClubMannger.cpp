//
// Created by Jey on 2019/2/26.
//
#include "DatabaseManager.h"
#include "BookClubMannger.h"
#include "FileMd5.hpp"
#include <boost/lexical_cast.hpp>
void BookClubMannger::user_login_handle(const cinatra::request& req, cinatra::response& res)
{
    std::cout << "user_login_callback" << std::endl;
    auto username = req.get_query_value("username");
    std::string username_str = std::string(username.data(),username.length());

    auto password = req.get_query_value("password");
    std::string password_str = std::string(password.data(),password.length());
    std::cout << "username : " << username_str << std::endl;
    std::cout << "password : " << password_str << std::endl;
    nlohmann::json json_res;
    if(DatabaseManager::getInstance ()->check_username_password (username_str,password_str))
    {
        json_res["code"] = -100;
    }
    else
    {
        auto tmp_userinfo = DatabaseManager::getInstance ()->get_userinfo (username_str,password_str);
        nlohmann::json json_user(tmp_userinfo);
        if (!json_user.empty ())
        {
            json_res["code"] = 200;
            json_res["user"] = json_user;
        }
        else
        {
            json_res["code"] = -100;
        }
    }

    res.set_status_and_content(cinatra::status_type::ok,json_res.dump());
}

void BookClubMannger::user_regist_handle(const cinatra::request& req, cinatra::response& res)
{
    std::cout << "user_regist_handle" << std::endl;

    auto userid = req.get_query_value("userid");
    std::string userid_str = std::string(userid.data(),userid.length());

    auto username = req.get_query_value("username");
    std::string username_str = std::string(username.data(),username.length());

    auto password = req.get_query_value("password");
    std::string password_str = std::string(password.data(),password.length());

    auto nickname = req.get_query_value("nickname");
    std::string nickname_str = std::string(nickname.data(),nickname.length());

    auto school = req.get_query_value("school");
    std::string school_str = std::string(school.data(),school.length());

    auto headimage = req.get_query_value("headimage");
    std::string headimage_str = std::string(headimage.data(),headimage.length());

    auto city = req.get_query_value("city");
    std::string city_str = std::string(city.data(),city.length());

    std::cout << userid_str << std::endl;
    std::cout << username_str << std::endl;
    std::cout << password_str << std::endl;
    std::cout << nickname_str << std::endl;
    std::cout << school_str << std::endl;
    std::cout << headimage_str << std::endl;
    std::cout << city_str << std::endl;

    nlohmann::json json_res;
    if(DatabaseManager::getInstance ()->check_username_exist(username_str))
    {
        json_res["code"] = -100;
        json_res["msg"] = "username_exist.";
    }
    else
    {
        user_info temp_user;
        temp_user.user_id = userid_str;
        temp_user.phone_number = username_str;
        temp_user.pass_word = password_str;
        temp_user.nick_name = nickname_str;
        temp_user.school = school_str;
        temp_user.city = city_str;
        temp_user.head_image = headimage_str;
        temp_user.funs_number = 0;
        temp_user.article_number = 0;
        temp_user.action_number = 0;

        if(DatabaseManager::getInstance ()->insert_userinfo (temp_user))
        {
            json_res["code"] = 200;
        }
        else
        {
            json_res["code"] = -100;
            json_res["msg"] = "insert_userinfo_failed.";
        }
    }

    res.set_status_and_content(cinatra::status_type::ok,json_res.dump());
//    res.set_status_and_content(cinatra::status_type::ok,"");
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

void BookClubMannger::upload_simple_file(const cinatra::request& req, cinatra::response& res)
{
    std::cout << "upload_simple_file_callback" << std::endl;

    assert(req.get_content_type() == cinatra::content_type::multipart);
    auto& files = req.get_upload_files();

    nlohmann::json json;

    for (auto& file : files) {
        std::cout << file.get_file_path() << " " << file.get_file_size() << " md5: " << FileMd5::getInstance()->MD5_file(file.get_file_path().c_str()) << std::endl;
//        file.get

        std::string file_path = file.get_file_path();
        std::string file_name = file_path.substr(file_path.find_last_of('/')+1);
        auto file_size = file.get_file_size();
//        std::string FileMd5 = FileMd5::getInstance()->MD5_file(file.get_file_path().c_str());

        std::string upload_file_md5 = FileMd5::getInstance()->MD5_file(file.get_file_path().c_str());

        file_base_info file_info;

        if (DatabaseManager::getInstance ()->check_file_is_exist(upload_file_md5))
        {
            std::cout << "find_the_file:success" << std::endl;
            file_info = DatabaseManager::getInstance()->get_file_info_with_md5(upload_file_md5);
            file.remove();
        }
        else
        {
            std::string file_suffix = file_path.substr(file_path.find_last_of('.')+1);

            std::cout << "file_suffix : " << file_suffix << std::endl;

            if(file_suffix == "jpg" || file_suffix == "png")
            {
                file_info.file_type =  FileTypePicture;
            }
            else if(file_suffix == "doc" || file_suffix == "docx" || file_suffix == "txt" || file_suffix == "xlsx" || file_suffix == "pdf" || file_suffix == "ppt")
            {
                file_info.file_type = FileTypeDoc;
            }
            else if(file_suffix == "mp3")
            {
                file_info.file_type =  FileTypeAideo;
            }
            else if(file_suffix == "mp4" || file_suffix == "avi" || file_suffix == "mkv")
            {
                file_info.file_type =  FileTypeVideo;
            }
            else
            {
                file_info.file_type =  FileTypeOther;
            }

            file_info.local_path = file.get_file_path();
            file_info.file_size = file.get_file_size();
            file_info.file_md5 = upload_file_md5;

            DatabaseManager::getInstance()->insert_file_base_info(file_info);
        }

        json["code"] = 200;
        json["file_md5"] = file_info.file_md5;

        std::cout << "file_path:" <<  file_info.local_path << std::endl;
    }

    res.set_status_and_content(cinatra::status_type::ok,json.dump());
}

void BookClubMannger::get_file_info (const cinatra::request &req, cinatra::response &res)
{
    auto filemd5 = req.get_query_value("file_md5");
    std::string filemd5_str = std::string(filemd5.data(),filemd5.length());
    nlohmann::json json;
    if(DatabaseManager::getInstance ()->check_file_is_exist(filemd5_str))
    {
        file_base_info file_info = DatabaseManager::getInstance()->get_file_info_with_md5(filemd5_str);

        json["code"] = 200;
        json["file_md5"] = file_info.file_md5;
        json["file_size"] = file_info.file_size;
        json["local_path"] = file_info.local_path;
        json["file_type"] = file_info.file_type;
    }
    else
    {
        json["code"] = -100;
        json["msg"] = "The file was not found";
    }

    res.set_status_and_content(cinatra::status_type::ok,json.dump());
}

void BookClubMannger::download_simple_file (const cinatra::request &req, cinatra::response &res)
{

}

void BookClubMannger::get_messages_list_handle (const cinatra::request &req, cinatra::response &res)
{
    auto userid = req.get_query_value("userid");
    std::string userid_str = std::string(userid.data(),userid.length());

    auto messages = DatabaseManager::getInstance ()->get_message_list(userid_str);

    nlohmann::json json;
    if(messages.size () > 0)
    {
        nlohmann::json messages_json(messages);

        json["code"] = 200;
        json["list"] = messages_json;
        json["size"] = messages.size ();
    }
    else
    {
        json["code"] = -100;
        json["msg"] = "No unread messages";
        json["size"] = 0;
    }
    res.set_status_and_content(cinatra::status_type::ok,json.dump());
}

void BookClubMannger::send_message_handle (const cinatra::request &req, cinatra::response &res)
{
    auto sender_id = req.get_query_value("sender_id");
    std::string sender_id_str = std::string(sender_id.data(),sender_id.length());
    auto accepter_id = req.get_query_value("accepter_id");
    std::string accepter_id_str = std::string(accepter_id.data(),accepter_id.length());
    auto session_id = req.get_query_value("session_id");
    std::string session_id_str = std::string(session_id.data(),session_id.length());
    auto message_id = req.get_query_value("message_id");
    std::string message_id_str = std::string(message_id.data(),message_id.length());
    auto message_type = req.get_query_value("message_type");
    int message_type_int = boost::lexical_cast<int>(message_type);
    auto messgae_body = req.get_query_value("messgae_body");
    std::string messgae_body_str = std::string(messgae_body.data(),messgae_body.length());
    auto send_time = req.get_query_value("send_time");
    std::string send_time_str = std::string(send_time.data(),send_time.length());

    message_info message;
    message.message_id = message_id_str;
    message.messgae_body = messgae_body_str;
    message.sender_id = sender_id_str;
    message.accepter_id = accepter_id_str;
    message.session_id = session_id_str;
    message.message_type = message_type_int;
    message.send_time = send_time_str;
    message.message_state = 1;

    nlohmann::json json;
    if(DatabaseManager::getInstance ()->insert_message (message))
    {
        json["code"] = 200;
        json["msg"] = "Send a success";
    }
    else
    {
        json["code"] = -100;
        json["msg"] = "Send failure";
    }
    res.set_status_and_content(cinatra::status_type::ok,json.dump());
}

void BookClubMannger::get_activice_list_handle (const cinatra::request &req, cinatra::response &res)
{

}

void BookClubMannger::create_new_active_handle (const cinatra::request &req, cinatra::response &res)
{

}

void BookClubMannger::remove_an_active_handle (const cinatra::request &req, cinatra::response &res)
{

}

void BookClubMannger::get_articles_list_handle (const cinatra::request &req, cinatra::response &res)
{

}

void BookClubMannger::create_new_article_handle (const cinatra::request &req, cinatra::response &res)
{

}

void BookClubMannger::remove_an_article_handle (const cinatra::request &req, cinatra::response &res)
{

}
