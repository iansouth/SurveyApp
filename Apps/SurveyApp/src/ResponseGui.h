#pragma once

#include "ofMain.h"
#include "ofxApp.h"

#include <map>
#include <vector>
#include <algorithm>

class ResponseGui {
public:
    ResponseGui() {}
    ~ResponseGui() {}

    void setup() {
    }

    void update() {}

    void draw(float x, float y, float width, float height);

    //void mouseDragged(int x, int y);
    //void mousePressed(int x, int y);
    //void mouseReleased(int x, int y);    

private:
    std::map<std::string, int> scores =
        {
            { "Science", -3 },
            { "Technology", 12 },
            { "Engineering", 1 },
            { "Art", 10 },
            { "Mathematics", 1 }
        };

};
