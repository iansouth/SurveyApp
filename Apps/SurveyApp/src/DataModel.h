#pragma once

#include "ofMain.h"

class DataModel final {
public:
    static DataModel& get()
    {
        static DataModel inst;
        return inst;
    }

    using Category = std::string;
    using Score = int;
 
    std::vector< Category > categories;
    std::map< Category, Score > scores;

    struct ScoreChange {
        Category category;
        Score change;
    };

    using ResponseChanges = std::vector<ScoreChange>;

    struct Question {
        std::string text;
        ResponseChanges yes;
        ResponseChanges no;
    };

    std::string getQuestion();
    void respond(bool yes);

private:
    DataModel();
    ~DataModel() = default;

    //ofxJSONElement config;
    //ofxJSONElement data;

    ofJson config;
    ofJson data;

    std::vector<Question> questions;
    int currentQ = 0;
};

