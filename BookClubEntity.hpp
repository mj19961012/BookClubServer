//
// Created by Jey on 2019/2/26.
//

#ifndef BOOKCLUBSERVER_BOOKCLUBENTITY_HPP
#define BOOKCLUBSERVER_BOOKCLUBENTITY_HPP
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
};
REFLECTION(user_info, id, article_id, article_title, article_content, author_id, article_type, release_time, supporting_number, page_view, comment_number, first_file, second_file, third_file);

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
};
REFLECTION(message_info, id, message_id, messgae_body, sender_id, accepter_id, session_id, send_time, message_state);

struct interest_list
{
    int id;
    std::string user_id;
    std::string follower_id;
    std::string date_subscribed;
};
REFLECTION(interest_list, id, user_id, follower_id, date_subscribed);
#endif //BOOKCLUBSERVER_BOOKCLUBENTITY_HPP
