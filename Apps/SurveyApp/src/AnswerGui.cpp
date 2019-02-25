#include "AnswerGui.h"
#include "ofxApp.h"
#include <algorithm>
#include "ofApp.h"

void AnswerGui::setCameraTexture(ofTexture * tex) 
{
    texture = tex;
}

void AnswerGui::setup()
{
}

void AnswerGui::update()
{
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
    ofApp::fonts.drawFormattedColumn(yesText, x, y + imgHeight / 2, width, OF_ALIGN_HORZ_CENTER, false);
    ofApp::fonts.drawFormattedColumn(noText, x, y+height-imgHeight/2, width, OF_ALIGN_HORZ_CENTER, false);
    ofSetColor(ofColor::black);
    ofNoFill();
    ofSetLineWidth(3.0f);
    ofDrawRectangle(x, y, width, imgHeight*1.1);
    ofDrawRectangle(x, y + height - imgHeight*1.1, width, imgHeight*1.1);
    // clamp image to boundary
    if (dragX < 0)
        imgX = x + width / 2 - imgWidth/2;
    if (dragX < 0)
        imgY = y + height / 2 - imgHeight / 2;
    imgX = ofClamp(imgX, x, x+width-imgWidth);
    imgY = ofClamp(imgY, y, y+height-imgHeight);

    if(!filterShader.isLoaded()) 
    {
        filterShader.load("shader");
        filterShader.printActiveUniforms();
    }

    if(texture)
    {
        ofPushMatrix();
        filterShader.begin();
        filterShader.setUniform1f("Answer", ofMap(imgY, y, y+height-imgHeight, -1.0, 1.0));
        filterShader.setUniform1f("Center", ofMap(imgX, x, x+width-imgWidth, 0.25, 0.75));
        ofSetHexColor(0xffffff);
        float tw = texture->getWidth();
        float th = texture->getHeight();
        texture->drawSubsection(
            imgX, imgY, imgWidth, imgHeight, 
            (tw-th)/2, 0, th, th);
        ofPopMatrix();
        filterShader.end();
    }
}

bool AnswerGui::insideImage(float x, float y)
{
    return x > imgX && x < imgX+imgWidth && y > imgY && y < imgY+imgHeight;
}

void AnswerGui::releaseImage()
{
    dragX = dragY = -1;
}

void AnswerGui::mouseDragged(int x, int y)
{
    // Are we still within?
    if(dragX > 0 && dragY)// > 0 && insideImage(x,y))
    {
        imgX += x-dragX;
        imgY += y-dragY;
        dragX = x;
        dragY = y;
    }
    else
    {
        ///releaseImage();
    }
}

void AnswerGui::mousePressed(int x, int y)
{
    // Is click within?
    if(insideImage(x,y))
    {
        dragX = x;
        dragY = y;
    }
}

//--------------------------------------------------------------
void AnswerGui::mouseReleased(int x, int y)
{
    if(insideImage(x,y))
    {
        releaseImage();
    }
}
