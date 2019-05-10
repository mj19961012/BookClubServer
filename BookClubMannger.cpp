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

    auto messages = DatabaseManager::getInstance ()->get_message_list (userid_str, 0);

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

void BookClubMannger::get_activities_list_handle (const cinatra::request &req, cinatra::response &res)
{
    auto page_num = req.get_query_value("page_num");
    std::string page_num_str = std::string(page_num.data(),page_num.length());
    int page_num_int = boost::lexical_cast<int>(page_num_str);
    auto page_size = req.get_query_value("page_size");
    std::string page_size_str = std::string(page_size.data(),page_size.length());
    int page_size_int = boost::lexical_cast<int>(page_size_str);
    auto action_city = req.get_query_value("action_city");
    std::string action_city_str = std::string(action_city.data(),action_city.length());
    auto begin_time = req.get_query_value("begin_time");
    std::string begin_time_str = std::string(begin_time.data(),begin_time.length());
    auto end_time = req.get_query_value("end_time");
    std::string end_time_str = std::string(end_time.data(),end_time.length());

    auto activities = DatabaseManager::getInstance ()->get_action_list (page_num_int,page_size_int,action_city_str,begin_time_str,end_time_str);

    nlohmann::json json;
    if(activities.size () > 0)
    {
        nlohmann::json activities_json(activities);

        json["code"] = 200;
        json["list"] = activities_json;
        json["size"] = activities.size ();
    }
    else
    {
        json["code"] = -100;
        json["msg"] = "No eligible activities";
        json["size"] = 0;
    }
    res.set_status_and_content(cinatra::status_type::ok,json.dump());
}

void BookClubMannger::create_new_action_handle (const cinatra::request &req, cinatra::response &res)
{
    auto action_id = req.get_query_value("action_id");
    std::string action_id_str = std::string(action_id.data(),action_id.length());
    auto action_title = req.get_query_value("action_title");
    std::string action_title_str = std::string(action_title.data(),action_title.length());
    auto action_content = req.get_query_value("action_content");
    std::string action_content_str = std::string(action_content.data(),action_content.length());
    auto action_city = req.get_query_value("action_city");
    std::string action_city_str = std::string(action_city.data(),action_city.length());
    auto begin_time = req.get_query_value("begin_time");
    std::string begin_time_str = std::string(begin_time.data(),begin_time.length());
    auto end_time = req.get_query_value("end_time");
    std::string end_time_str = std::string(end_time.data(),end_time.length());
    auto author_id = req.get_query_value("author_id");
    std::string author_id_str = std::string(author_id.data(),author_id.length());
    auto first_file = req.get_query_value("first_file");
    std::string first_file_str = std::string(first_file.data(),first_file.length());
    auto second_file = req.get_query_value("second_file");
    std::string second_file_str = std::string(second_file.data(),second_file.length());
    auto third_file = req.get_query_value("third_file");
    std::string third_file_str = std::string(third_file.data(),third_file.length());
    auto release_time = req.get_query_value("release_time");
    std::string release_time_str = std::string(release_time.data(),release_time.length());

    action_info action;
    action.action_id = action_id_str;
    action.action_title = action_title_str;
    action.action_content = action_content_str;
    action.action_city = action_city_str;
    action.begin_time = begin_time_str;
    action.end_time = end_time_str;
    action.author_id = author_id_str;
    action.first_file = first_file_str;
    action.second_file = second_file_str;
    action.third_file = third_file_str;
    action.release_time = release_time_str;
    action.page_view = 0;

    nlohmann::json json;

    if (DatabaseManager::getInstance ()->insert_action (action))
    {
        json["code"] = 200;
        json["msg"] = "Release success";
    }
    else
    {
        json["code"] = -100;
        json["msg"] = "Post failure";
    }
    res.set_status_and_content(cinatra::status_type::ok,json.dump());
}

void BookClubMannger::remove_an_action_handle (const cinatra::request &req, cinatra::response &res)
{

}

void BookClubMannger::get_articles_list_handle (const cinatra::request &req, cinatra::response &res)
{
    auto page_num = req.get_query_value("page_num");
    std::string page_num_str = std::string(page_num.data(),page_num.length());
    int page_num_int = boost::lexical_cast<int>(page_num_str);
    auto page_size = req.get_query_value("page_size");
    std::string page_size_str = std::string(page_size.data(),page_size.length());
    int page_size_int = boost::lexical_cast<int>(page_size_str);

    auto articles = DatabaseManager::getInstance ()->get_article_list (page_num_int,page_size_int);

    nlohmann::json json;
    if(articles.size () > 0)
    {
        nlohmann::json articles_json(articles);

        json["code"] = 200;
        json["list"] = articles_json;
        json["size"] = articles.size ();
    }
    else
    {
        json["code"] = -100;
        json["msg"] = "There are no eligible posts";
        json["size"] = 0;
    }
    res.set_status_and_content(cinatra::status_type::ok,json.dump());
}

void BookClubMannger::create_new_article_handle (const cinatra::request &req, cinatra::response &res)
{
    auto article_id = req.get_query_value("article_id");
    std::string article_id_str = std::string(article_id.data(),article_id.length());
    auto article_title = req.get_query_value("article_title");
    std::string article_title_str = std::string(article_title.data(),article_title.length());
    auto article_content = req.get_query_value("article_content");
    std::string article_content_str = std::string(article_content.data(),article_content.length());
    auto article_type = req.get_query_value("article_type");
    std::string article_type_str = std::string(article_type.data(),article_type.length());
    int article_type_int = boost::lexical_cast<int>(article_type_str);
    auto release_time = req.get_query_value("release_time");
    std::string release_time_str = std::string(release_time.data(),release_time.length());
    auto author_id = req.get_query_value("author_id");
    std::string author_id_str = std::string(author_id.data(),author_id.length());

    article_info article;
    article.article_id = article_id_str;
    article.article_title = article_title_str;
    article.article_content = article_content_str;
    article.author_id = author_id_str;
    article.article_type = article_type_int;
    article.release_time = release_time_str;
    article.author_id = author_id_str;
    article.supporting_number = 0;
    article.page_view = 0;
    article.comment_number = 0;
    nlohmann::json json;

    if (DatabaseManager::getInstance ()->insert_article (article))
    {
        json["code"] = 200;
        json["msg"] = "Release success";
    }
    else
    {
        json["code"] = -100;
        json["msg"] = "Post failure";
    }
    res.set_status_and_content(cinatra::status_type::ok,json.dump());
}

void BookClubMannger::remove_an_article_handle (const cinatra::request &req, cinatra::response &res)
{

}

void BookClubMannger::get_detail_of_the_action_handle (const cinatra::request &req, cinatra::response &res)
{
    auto action_id = req.get_query_value("action_id");
    std::string action_id_str = std::string(action_id.data(),action_id.length());

    nlohmann::json json;

    auto action = DatabaseManager::getInstance ()->get_action_info (action_id_str);
    auto commit_list = DatabaseManager::getInstance ()->get_message_list (action_id_str,1);
    if(action.action_id != "")
    {
        json["code"] = 200;
        json["action"] = action;
        json["list"] = commit_list;
        ++action.page_view;
        DatabaseManager::getInstance ()->update_action (action);
    }
    else
    {
        json["code"] = -100;
        json["msg"] = "Activities do not exist";
    }
    res.set_status_and_content(cinatra::status_type::ok,json.dump());
}

void BookClubMannger::get_detail_of_the_article_handle (const cinatra::request &req, cinatra::response &res)
{
    auto article_id = req.get_query_value("article_id");
    std::string article_id_str = std::string(article_id.data(),article_id.length());

    nlohmann::json json;

    auto article = DatabaseManager::getInstance ()->get_article_info (article_id_str);
    auto commit_list = DatabaseManager::getInstance ()->get_message_list (article_id_str,1);
    if(article.article_id != "")
    {
        json["code"] = 200;
        json["article"] = article;
        json["list"] = commit_list;
        ++article.page_view;
        DatabaseManager::getInstance ()->update_article (article);
    }
    else
    {
        json["code"] = -100;
        json["msg"] = "Articles do not exist";
    }
    res.set_status_and_content(cinatra::status_type::ok,json.dump());
}
