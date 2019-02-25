#pragma once

#include "ofMain.h"
#include "ofxApp.h"

#include <map>
#include <vector>
#include <algorithm>
#include "SurveyQuestions.h"

class ResponseGui {
public:
    ResponseGui() {}
    ~ResponseGui() {}

    void setup() {
    }

    void update() {}

    void draw(float x, float y, float width, float height);

    void onUpdate(Change& change);
private:
    std::map<std::string, int> scores =
        {
            { "Science", -3 },
            { "Technology", 12 },
            { "Engineering", 1 },
            { "Art", 10 },
            { "Mathematics", 1 }
        };

    std::vector< std::string > order =
    {
        "Science",
        "Technology",
        "Engineering",
        "Art",
        "Mathematics",
    };

};
