#pragma once

#include "ofMain.h"
#include "ofxFontStash2.h"

class AnswerGui {
public:
    AnswerGui() {}
    ~AnswerGui() {}

    void setCameraTexture(ofTexture* tex);
    void setup();
    void update();
    void draw(float x, float y, float width, float height);

    void mouseDragged(int x, int y);
    void mousePressed(int x, int y);
    void mouseReleased(int x, int y);    

private:
    bool insideImage(float x, float y);
    void releaseImage();

    ofTexture* texture = nullptr;
    ofShader filterShader;

    float imgX = 0.0;
    float imgY = 0.0;
    bool dragging = false;
    float dragX = -1.0;
    float dragY = -1.0;
    float imgWidth = 200;
    float imgHeight = 200;
};
