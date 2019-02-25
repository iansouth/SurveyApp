#include "ResponseGui.h"
#include "ofApp.h"

void ResponseGui::draw(float x, float y, float width, float height)
{

    int min = 0;
    int max = 0;
    for (auto score : scores) {
        min = std::min(score.second, min);
        max = std::max(score.second, max);
    }

    std::map<std::string, ofRectangle> bounds;
    float maxHeight = 0;
    for (auto score : scores) {
        bounds[score.first] = ofApp::fonts.getTextBounds(score.first, ofApp::fonts.getStyle("response"), 0, 0);
        maxHeight = std::max(bounds[score.first].getHeight(), maxHeight);
    }

    float margin = 50.0f;
    float padding = (height - 2*margin - maxHeight * scores.size()) / (scores.size() - 1);
    int range = max - min;

    ofFill();
    float zeroPoint = margin - min * maxHeight;

    int c = 0;
    for (auto score : scores) {
        float top = margin + (c++)*(maxHeight + padding);
        if (score.second > 0)
        {
            for (int i = 0; i < score.second; ++i)
            {
                ofSetHexColor(0x00ff00);
                ofDrawRectangle(zeroPoint + i * maxHeight, top, maxHeight, maxHeight);
            }
        }
        
        
        if (score.second < 0)
        {
            for (int i = 0; i < -score.second; ++i)
            {
                ofSetHexColor(0x0000ff);
                ofDrawRectangle(zeroPoint - (i+1) * maxHeight, top, maxHeight, maxHeight);
            }
        }

        ofSetHexColor(0xffffffff);
        ofApp::fonts.draw(
            score.first,
            ofApp::fonts.getStyle("response"),
            margin, top);
    }


}
