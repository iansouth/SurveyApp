
#pragma once
#include <string>
#include <vector>

struct ResponseResult {
    std::string category;
    int change;
};

struct Question {
    std::string text;
    std::vector<ResponseResult> resultYes;
    std::vector<ResponseResult> resultNo;
};

static std::vector<Question> qs = {
{
    "When?", 
    { { "Industry", 5 }, {"Science", -2}, {"Art", -1}, {"Education", 1} }, // yes 
    { { "Industry", 3 },{ "Science", 2 },{ "Art", 3 },{ "Education",-3 }}  // no 
},
{
    "Why?",
    { { "Industry", -5 },{ "Science", 3 },{ "Art", 1 },{ "Education",-3 } }, // yes 
    { { "Industry", 1 },{ "Science", -1 },{ "Art", 3 },{ "Education", 3 } }  // no 
},
{
    "Hows?",
    { { "Industry", 2 },{ "Science", -2 },{ "Art", 1 },{ "Education",-3 } }, // yes 
    { { "Industry", 5 },{ "Science", 2 },{ "Art", 0 },{ "Education",2 } }  // no 
}
};