
#pragma once

#include "ofMain.h"
#include <string>
#include <vector>

struct ResponseResult {
    std::string category;
    int change;
};

using Change = std::vector<ResponseResult>;

struct Question {
    std::string text;
    Change resultYes;
    Change resultNo;
};

class QuestionDisplay 
{
public:
    QuestionDisplay() {
        iter = qs.begin();
    }

    ofEvent< Change > onResponseChange;

    void draw(int x, int y, int width, int height);
    void next();

private:
#define SIMPLE_Q(X) { #X "?", {{#X, 1}}, {{#X, -1}}}
    std::vector<Question> qs = {
        {
            "Hmm?",
            { { "Science",  5 },{ "Technology",  5 },{ "Engineering",  5 },{ "Art",  5 },{ "Mathematics",  5 } }, // yes
            { { "Science", -5 },{ "Technology", -5 },{ "Engineering", -5 },{ "Art", -5 },{ "Mathematics", -5 } }  // no
        },
        SIMPLE_Q(Science), SIMPLE_Q(Technology), SIMPLE_Q(Engineering), SIMPLE_Q(Art), SIMPLE_Q(Mathematics)
    };

    std::vector<Question>::iterator iter;
public:
    void answered(bool yes);
};
