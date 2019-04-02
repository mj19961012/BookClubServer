//
// Created by Jey on 2019/2/26.
//

#ifndef BOOKCLUBSERVER_BOOKCLUBENTITY_HPP
#define BOOKCLUBSERVER_BOOKCLUBENTITY_HPP
#include "feather/ormpp/mysql.hpp"
#include "feather/ormpp/dbng.hpp"
#include "feather/ormpp/connection_pool.hpp"
#include "feather/cinatra/nlohmann_json.hpp"
#include <string>


struct user_info
{
    int id;
    std::string user_id;
    std::string phone_number;
    std::string nick_name;
    std::string pass_word;
    std::string school;
    std::string city;
    std::string head_image;
    int funs_number;
    int article_number;
    int action_number;
    friend void to_json(nlohmann::json &j,const user_info & user);
    friend void from_json(const nlohmann::json &j,user_info & user);
};
REFLECTION(user_info, id, user_id, phone_number, nick_name, pass_word, school, city, head_image, funs_number, article_number, action_number);

struct article_info
{
    int id;
    std::string article_id;
    std::string article_title;
    std::string article_content;
    std::string author_id;
    int article_type;
    std::string release_time;
    int supporting_number;
    int page_view;
    int comment_number;
    std::string first_file;
    std::string second_file;
    std::string third_file;

    friend void to_json(nlohmann::json &j,const article_info & article);
    friend void from_json(const nlohmann::json &j,article_info & article);
};
REFLECTION(article_info, id, article_id, article_title, article_content, author_id, article_type, release_time, supporting_number, page_view, comment_number, first_file, second_file, third_file);

struct action_info
{
    int id;
    std::string action_id;
    std::string action_title;
    std::string action_content;
    std::string action_city;
    std::string begin_time;
    std::string end_time;
    std::string author_id;
    std::string first_file;
    std::string second_file;
    std::string third_file;
    std::string release_time;
    int page_view;

    friend void to_json(nlohmann::json &j,const action_info & action);
    friend void from_json(const nlohmann::json &j,action_info & action);
};
REFLECTION(action_info, id, action_id, action_title, action_content, action_city, begin_time, end_time, author_id, first_file, second_file, third_file, release_time, page_view);

struct message_info
{
    int id;
    std::string message_id;
    std::string messgae_body;
    std::string sender_id;
    std::string accepter_id;
    std::string session_id;
    std::string send_time;
    int message_state;

    friend void to_json(nlohmann::json &j,const message_info & message);
    friend void from_json(const nlohmann::json &j,message_info & message);
};
REFLECTION(message_info, id, message_id, messgae_body, sender_id, accepter_id, session_id, send_time, message_state);

struct interest_list
{
    int id;
    std::string user_id;
    std::string follower_id;
    std::string date_subscribed;

    friend void to_json(nlohmann::json &j,const interest_list & interest);
    friend void from_json(const nlohmann::json &j,interest_list & interest);
};
REFLECTION(interest_list, id, user_id, follower_id, date_subscribed);

struct file_base_info
{
    int id;
    std::string file_md5;
    int file_size;
    int file_type;
    std::string local_path;
};
REFLECTION(file_base_info,id,file_md5,file_size,file_type,local_path);

enum BC_FILE_TYPE
{
    FileTypeOther = 0,
    FileTypeDir = 1,
    FileTypeDoc = 2,
    FileTypePicture = 3,
    FileTypeAideo = 4,
    FileTypeVideo = 5
};

#endif //BOOKCLUBSERVER_BOOKCLUBENTITY_HPP
