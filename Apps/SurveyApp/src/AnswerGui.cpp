#include "AnswerGui.h"
#include "ofxApp.h"
#include <algorithm>
#include "Text.h"

void AnswerGui::setup()
{
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.setup(1280, 720, true);
    filterShader.load("shader");
}

void AnswerGui::update()
{
    vidGrabber.update();
}

void AnswerGui::draw(float x, float y, float width, float height)
{
    static const string yesText = "<answer>YES</answer>";
    static const string noText = "<answer>NO</answer>";
    ofSetColor(ofColor::wheat);
    ofFill();
    ofDrawRectangle(x, y, width, height);
    ofSetColor(ofColor::black);
    float offset = 100;
    imgWidth = imgHeight = std::min(width  /1.5, height / 4.0);
    Text::get().drawFormattedColumn(yesText, x, y + imgHeight / 2, width, OF_ALIGN_HORZ_CENTER, false);
    Text::get().drawFormattedColumn(noText, x, y+height-imgHeight/2, width, OF_ALIGN_HORZ_CENTER, false);
    ofSetColor(ofColor::black);
    ofNoFill();
    ofSetLineWidth(3.0f);
    yesRect = ofRectangle(x, y, width, imgHeight*1.1);
    noRect = ofRectangle(x, y + height - imgHeight * 1.1, width, imgHeight*1.1);
    ofDrawRectangle(yesRect);
    ofDrawRectangle(noRect);
    // clamp image to boundary
    if (dragX < 0)
        imgX = x + width / 2 - imgWidth/2;
    if (dragX < 0)
        imgY = y + height / 2 - imgHeight / 2;
    imgX = ofClamp(imgX, x, x+width-imgWidth);
    imgY = ofClamp(imgY, y, y+height-imgHeight);

    
    ofPushMatrix();
    filterShader.begin();
    filterShader.setUniform1f("Answer", ofMap(imgY, y, y+height-imgHeight, -1.0, 1.0));
    filterShader.setUniform1f("Center", ofMap(imgX, x, x+width-imgWidth, 0.25, 0.75));
    ofSetHexColor(0xffffff);
    float tw = vidGrabber.getTexture().getWidth();
    float th = vidGrabber.getTexture().getHeight();
    vidGrabber.getTexture().drawSubsection(
        imgX, imgY, imgWidth, imgHeight, 
        (tw-th)/2, 0, th, th);
    ofPopMatrix();
    filterShader.end();
}

ofTexture AnswerGui::getCameraCopy()
{
    ofFbo copyFbo;
    copyFbo.allocate(1280, 720, GL_RGB, 4);
    copyFbo.begin();
    filterShader.begin();
    ofClear(0);
    vidGrabber.getTexture().draw(0, 0, copyFbo.getWidth(), copyFbo.getHeight());
    filterShader.end();
    copyFbo.end();
    return copyFbo.getTexture();
}

bool AnswerGui::insideImage(float x, float y)
{
    return x > imgX && x < imgX+imgWidth && y > imgY && y < imgY+imgHeight;
}

void AnswerGui::releaseImage(int x, int y)
{
    static bool True = true;
    static bool False = false;

    if (insideImage(x, y))
    {
        if (yesRect.inside(x, y))
            ofNotifyEvent(onAnswer, True);
        else if (noRect.inside(x, y))
            ofNotifyEvent(onAnswer, False);
    }
    dragX = dragY = -1;
}

void AnswerGui::mouseDragged(int x, int y)
{
    if (!dragEnable) return;

    // Are we still within?
    if(dragX > 0)
    {
        imgX += x-dragX;
        imgY += y-dragY;
        dragX = x;
        dragY = y;
    }
    else
    {
        releaseImage(x, y);
    }
}

void AnswerGui::mousePressed(int x, int y)
{
    // Is click within?
    if(dragEnable && insideImage(x,y))
    {
        dragX = x;
        dragY = y;
    }
}

//--------------------------------------------------------------
void AnswerGui::mouseReleased(int x, int y)
{
    releaseImage(x, y);
}

void AnswerGui::disable()
{
    dragEnable = false;
    dragX = dragY = -1;
}

void AnswerGui::enable()
{
    dragEnable = true;
    dragX = dragY = -1;
}
