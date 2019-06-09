//
// Created by Jey on 2019/2/26.
//

#include "DatabaseManager.h"
#include <boost/lexical_cast.hpp>

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
    ormpp_not_null user_info_not_null{{"user_id","phone_number","pass_word"}};

    if (!m_db.create_datatable<user_info>(user_info_key,user_info_not_null))
    {
        std::cout << "database_create_user_base_info_error" << std::endl;
        return false;
    }

//    struct file_base_info
//    {
//        int id;
//        std::string file_md5;
//        int file_size;
//        int file_type;
//        std::string local_path;
//    };
    ormpp_auto_key file_info_key{"id"};
    ormpp_not_null file_info_not_null{{"file_md5","file_size","file_type","local_path"}};

    if (!m_db.create_datatable<file_base_info>(file_info_key,file_info_not_null))
    {
        std::cout << "database_create_file_base_info_error" << std::endl;
        return false;
    }
//    struct message_info
//    {
//    int id;
//    std::string message_id;
//    std::string messgae_body;
//    std::string sender_id;
//    std::string accepter_id;
//    std::string session_id;
//    std::string send_time;
//    int message_state;
//    int message_type;
//
//        friend void to_json(nlohmann::json &j,const message_info & message);
//        friend void from_json(const nlohmann::json &j,message_info & message);
//    };
    ormpp_auto_key message_info_key{"id"};
    ormpp_not_null message_info_not_null{{"message_id","messgae_body","sender_id","accepter_id","session_id","send_time","message_state","message_type"}};

    if (!m_db.create_datatable<message_info>(message_info_key,message_info_not_null))
    {
        std::cout << "database_create_message_info_error" << std::endl;
        return false;
    }
//    struct article_info
//    {
//        int id;
//        std::string article_id;
//        std::string article_title;
//        std::string article_content;
//        std::string author_id;
//        int article_type;
//        std::string release_time;
//        int supporting_number;
//        int page_view;
//        int comment_number;
//        std::string first_file;
//        std::string second_file;
//        std::string third_file;
//
//        friend void to_json(nlohmann::json &j,const article_info & article);
//        friend void from_json(const nlohmann::json &j,article_info & article);
//    };
    ormpp_auto_key article_info_key{"id"};
    ormpp_not_null article_info_not_null{{"article_id","article_title","article_content","author_id","article_type","release_time","supporting_number","page_view","comment_number"}};

    if (!m_db.create_datatable<article_info>(message_info_key,message_info_not_null))
    {
        std::cout << "database_create_message_info_error" << std::endl;
        return false;
    }
//    struct action_info
//    {
//        int id;
//        std::string action_id;
//        std::string action_title;
//        std::string action_content;
//        std::string action_city;
//        std::string begin_time;
//        std::string end_time;
//        std::string author_id;
//        std::string first_file;
//        std::string second_file;
//        std::string third_file;
//        std::string release_time;
//        int page_view;
//
//        friend void to_json(nlohmann::json &j,const action_info & action);
//        friend void from_json(const nlohmann::json &j,action_info & action);
//    };
    ormpp_auto_key action_info_key{"id"};
    ormpp_not_null action_info_not_null{{"action_id","action_title","action_content","action_city","begin_time","end_time","author_id","release_time","page_view"}};

    if (!m_db.create_datatable<action_info>(message_info_key,message_info_not_null))
    {
        std::cout << "database_create_action_info_error" << std::endl;
        return false;
    }

//    struct interest_list
//    {
//        int id;
//        std::string user_id;
//        std::string follower_id;
//        std::string date_subscribed;
//    };
    ormpp_auto_key interest_list_key{"id"};
    ormpp_not_null interest_list_not_null{{"user_id","interest_id","follower_id","date_subscribed"}};

    if (!m_db.create_datatable<interest_list>(interest_list_key,interest_list_not_null))
    {
        std::cout << "database_create_action_info_error" << std::endl;
        return false;
    }
    return true;
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
    return user_info ();
}

user_info DatabaseManager::get_userinfo_with_userid(std::string user_id)
{
    std::string sql = "select * from user_info where user_id = '" + user_id + "';";
//    std::cout << sql << std::endl;
    auto result = m_db.query<user_info>(sql);

    if(!result.empty())
    {
        for (auto &user:result)
        {
            return user;
        }
    }
    return user_info ();
}

bool DatabaseManager::check_username_password(std::string phone_number,std::string pass_word)
{
auto result = m_db.query<user_info>(
        "select * from user_info where phone_number = '" + phone_number + "' and pass_word = '" + pass_word + "'");

return result.empty ();
}

bool DatabaseManager::check_username_exist(std::string phone_number)
{
    auto result = m_db.query<user_info>(
            "select * from user_info where phone_number = '" + phone_number + "'");

    return !result.empty ();
}

bool DatabaseManager::insert_userinfo(user_info userinfo)
{
    auto result = m_db.query<user_info>("select * from user_info where phone_number = '" + userinfo.phone_number + "'");

    int res = INT_MIN;

//    std::cout << "result_status:" << result.empty () << std::endl;

    if (result.empty())
    {
        res = m_db.insert<user_info>(userinfo);
    }
    return res != INT_MIN;
}

bool DatabaseManager::check_file_is_exist(std::string filemd5)
{
    auto result = m_db.query<file_base_info>(
            "select * from file_base_info where file_md5 = '" + filemd5 + "'");

    return !result.empty ();
}

file_base_info DatabaseManager::get_file_info_with_md5(std::string filemd5)
{
    auto result = m_db.query<file_base_info>(
            "select * from file_base_info where file_md5 = '" + filemd5 + "'");

    if(!result.empty())
    {
        for (auto &file:result)
        {
            return file;
        }
    }
    return file_base_info ();
}

bool DatabaseManager::insert_file_base_info(file_base_info fileinfo)
{
    auto result = m_db.query<file_base_info>("select * from user_info where phone_number = '" + fileinfo.file_md5 + "'");

    int res = INT_MIN;

//    std::cout << "result_status:" << result.empty () << std::endl;

    if (result.empty())
    {
        res = m_db.insert<file_base_info>(fileinfo);
    }
    return res != INT_MIN;
}

std::vector<message_info> DatabaseManager::get_message_list (std::string session_id, int message_type)
{
//    auto result = m_db.query<message_info>(
//            "select * from message_info where accepter_id = '" + session_id + "' and message_state = '1';");
    std::string str_sql;
    if(1 == message_type)
    {
        str_sql =  "select * from message_info where accepter_id = '" + session_id + "' and message_state = '1';";
    }
    else if(0 == message_type)
    {
        str_sql =  "select * from message_info where session_id = '" + session_id + "' and message_type = '0';";
    }
    else
    {
        str_sql =  "select * from message_info where accepter_id = '2c1d394d222493560df2c793d660a134' and message_state = '1';";
    }

    auto result = m_db.query<message_info>(str_sql);
    if(!result.empty())
    {
        return result;
    }
    return std::vector<message_info> ();
}

bool DatabaseManager::insert_message (message_info message)
{
    auto result = m_db.query<message_info>("select * from message_info where message_id = '" + message.message_id + "'");

    int res = INT_MIN;

    if (result.empty())
    {
        res = m_db.insert<message_info>(message);
    }
    return res != INT_MIN;
}

std::vector<action_info> DatabaseManager::get_action_list (int pagesize, int pagenum, std::string city, std::string begintime, std::string endtime)
{
    //"select * from orders_history where type=8 and \n"
    //"id>=(select id from orders_history where type=8 limit 100000,1) \n"
    //"limit 100;"  分页查询数据库
    std::string sql_str_chile = "(select id from action_info where ((begin_time + 0) <  "+ begintime + ")  and ((end_time + 0) >  " + endtime + ") and ((action_city + 0) = " + city + ") limit " + boost::lexical_cast<std::string> (pagesize * pagenum) + ",1)";
    std::string sql_str_main = "select * from action_info where id >= "+ sql_str_chile + "limit " + boost::lexical_cast<std::string> (pagesize) + ";";
    auto result = m_db.query<action_info>(sql_str_main);
//    std::cout << result.size () << std::endl;
    if(!result.empty())
    {
        return result;
    }
    return std::vector<action_info> ();
}

bool DatabaseManager::insert_action (action_info action)
{
    auto result = m_db.query<action_info>("select * from action_info where action_id = '" + action.action_id + "'");

    int res = INT_MIN;

    if (result.empty())
    {
        action.id = 0;
        res = m_db.insert<action_info>(action);
    }
    if(res != INT_MIN)
    {
        auto user = get_userinfo_with_userid (action.author_id);
        user.action_number ++ ;
        m_db.update<user_info>(user);
    }
    return res != INT_MIN;
}

std::vector<article_info> DatabaseManager::get_article_list (int pagenum,int pagesize,std::string article_type)
{
    std::string sql_str_chile;
    std::string sql_str_main;

    if(1 == boost::lexical_cast<int>(article_type))
    {
        sql_str_chile = "(select id from article_info where (article_type >= " + article_type +") limit " + boost::lexical_cast<std::string> (pagesize * pagenum) + ",1)";
        sql_str_main = "select * from article_info where id >= "+ sql_str_chile + " and (article_type >= " + article_type + ") limit " + boost::lexical_cast<std::string> (pagesize) + ";";
    }
    else
    {
        sql_str_chile = "(select id from article_info where (article_type = " + article_type +") limit " + boost::lexical_cast<std::string> (pagesize * pagenum) + ",1)";
        sql_str_main = "select * from article_info where id >= "+ sql_str_chile + " and (article_type = " + article_type + ") limit " + boost::lexical_cast<std::string> (pagesize) + ";";
    }


    auto result = m_db.query<article_info>(sql_str_main);

    if(!result.empty())
    {
        return result;
    }
    return std::vector<article_info> ();
}

bool DatabaseManager::insert_article (article_info article)
{
    auto result = m_db.query<article_info>("select * from article_info where article_id = '" + article.article_id + "'");

    int res = INT_MIN;

    if (result.empty())
    {
        res = m_db.insert<article_info>(article);
    }

    if(res != INT_MIN)
    {
        auto user = get_userinfo_with_userid (article.author_id);
        user.article_number ++ ;
        m_db.update<user_info>(user);
    }

    return res != INT_MIN;
}

action_info DatabaseManager::get_action_info (std::string action_id)
{
    auto result = m_db.query<action_info>("select * from action_info where action_id = '" + action_id + "'");

    if(!result.empty ())
    {
        for(auto & action : result)
        {
            return  action;
        }
    }
    return action_info ();
}

article_info DatabaseManager::get_article_info (std::string article_id)
{
    auto result = m_db.query<article_info>("select * from article_info where article_id = '" + article_id + "'");

    if(!result.empty ())
    {
        for(auto & article : result)
        {
            return  article;
        }
    }
    return article_info ();
}

void DatabaseManager::update_article (article_info article)
{
    m_db.update<article_info>(article);
}

void DatabaseManager::update_action (action_info action)
{
    m_db.update<action_info>(action);
}

std::vector<article_info> DatabaseManager::get_article_list_with_someone (std::string userid, int pagenum, int pagesize)
{
    std::string sql_str_chile = "(select id from article_info where author_id = '" + userid +"' limit " + boost::lexical_cast<std::string> (pagesize * pagenum) + ",1)";
    std::string sql_str_main = "select * from article_info where id >= "+ sql_str_chile + " and author_id = '" + userid + "' limit " + boost::lexical_cast<std::string> (pagesize) + ";";
//    std::cout << sql_str_main << std::endl;
    auto result = m_db.query<article_info>(sql_str_main);

    if(!result.empty())
    {
        return result;
    }
    return std::vector<article_info> ();
}

std::vector<action_info> DatabaseManager::get_action_list_with_someone (std::string userid, int pagenum, int pagesize)
{
    std::string sql_str_chile = "(select id from action_info where author_id = '" + userid +"' limit " + boost::lexical_cast<std::string> (pagesize * pagenum) + ",1)";
    std::string sql_str_main = "select * from action_info where id >= "+ sql_str_chile + " and author_id = '" + userid + "' limit " + boost::lexical_cast<std::string> (pagesize) + ";";
//    std::cout << sql_str_main << std::endl;
    auto result = m_db.query<action_info>(sql_str_main);

    if(!result.empty())
    {
        return result;
    }
    return std::vector<action_info> ();
}

bool DatabaseManager::insert_interest (interest_list interest)
{
    auto result = m_db.query<interest_list>("select * from interest_list where (interest_id = '" + interest.interest_id + "') or (user_id = '" + interest.user_id + "' and follower_id = '" + interest.follower_id + "')");

    int res = INT_MIN;

    if (result.empty())
    {
        res = m_db.insert<interest_list>(interest);
    }

    if(res != INT_MIN)
    {
        auto user = get_userinfo_with_userid (interest.follower_id);
        user.funs_number ++ ;
        m_db.update<user_info>(user);
    }

    return res != INT_MIN;
}

bool DatabaseManager::remove_interest (std::string interest_id)
{
    return m_db.delete_records<interest_list>("id='" + interest_id + "'");
}

std::vector<interest_list> DatabaseManager::get_someone_interest_list (std::string user_id)
{
    auto result = m_db.query<interest_list>("select * from interest_list where user_id = '" + user_id + "'");

    if(!result.empty ())
    {
        return result;
    }
    return std::vector<interest_list> ();
}

bool DatabaseManager::change_message_status (std::string sender_id, std::string session_id, std::string message_type)
{
    std::string sql = "select * from message_info where sender_id = '" + sender_id + "' and session_id = '"+ session_id + "' and message_type = " + message_type + ";";
//    std::cout << sql << std::endl;
    auto result = m_db.query<message_info>(sql);

    int res = INT_MIN;

    if(!result.empty ())
    {
        for(auto &message : result)
        {
            message.message_state = 0;
            res = m_db.update<message_info>(message);
        }
    }
    return res == INT_MIN;
}

