#pragma once

#include "SurveyQuestions.h"
#include <map>

class SurveyAnswers {
public:
    void answer(const std::vector<ResponseResult>& response)
    {
        for(auto result : response) {
            scores[result.category] += result.change;
        }
    }

private:
    std::map<std::string, int> scores;
};