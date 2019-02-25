#include "ResponseGui.h"
#include "Text.h"

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
        bounds[score.first] = Text::get().getTextBounds(score.first, Text::get().getStyle("response"), 0, 0);
        maxHeight = std::max(bounds[score.first].getHeight(), maxHeight);
    }

    float margin = 50.0f;
    float padding = (height - 2*margin - maxHeight * scores.size()) / (scores.size() - 1);
    int range = max - min;

    ofFill();
    float zeroPoint = margin - min * maxHeight;
    int c = 0;
    for (auto name : order) {
        auto score = scores[name];
        float top = margin + (c++)*(maxHeight + padding);
        if (score > 0)
        {
            for (int i = 0; i < score; ++i)
            {
                ofSetHexColor(0x00ff00);
                ofDrawRectangle(zeroPoint + i * maxHeight, top, maxHeight, maxHeight);
            }
        }
        
        
        if (score < 0)
        {
            for (int i = 0; i < -score; ++i)
            {
                ofSetHexColor(0x0000ff);
                ofDrawRectangle(zeroPoint - (i+1) * maxHeight, top, maxHeight, maxHeight);
            }
        }

        ofSetHexColor(0xaaaaaa);
        ofDrawLine(zeroPoint, 0, zeroPoint, height);

        ofSetHexColor(0xffffff);
        Text::get().draw(
            name,
            Text::get().getStyle("response"),
            margin, top);
    }


}

void ResponseGui::onUpdate(Change & change)
{
    for (auto entry : change) {
        if (scores.count(entry.category) > 0)
            scores[entry.category] += entry.change;
    }
}
