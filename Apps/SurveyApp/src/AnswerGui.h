#pragma once

#include "ofMain.h"
#include "ofxFontStash2.h"

class AnswerGui {
public:
    AnswerGui() {}
    ~AnswerGui() {}
    ofEvent<bool> onAnswer;

    void setup();
    void update();
    void draw(float x, float y, float width, float height);
    ofTexture getCameraCopy();

    void mouseDragged(int x, int y);
    void mousePressed(int x, int y);
    void mouseReleased(int x, int y);    

    void disable();
    void enable();
private:
    bool insideImage(float x, float y);
    void releaseImage(int x, int y);

    ofShader filterShader;

    float imgX = 0.0;
    float imgY = 0.0;
    bool dragging = false;
    float dragX = -1.0;
    float dragY = -1.0;
    float imgWidth = 200;
    float imgHeight = 200;
    ofRectangle yesRect, noRect;
    bool dragEnable = true;
    ofVideoGrabber vidGrabber;
};
