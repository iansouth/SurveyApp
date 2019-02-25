#pragma once
#include "ofxFontStash2.h"

class Text final {
public:
    static ofxFontStash2::Fonts& get()
    {
        static ofxFontStash2::Fonts inst;
        return inst;
    }
private:
    Text() = default;
    ~Text() = default;
};


