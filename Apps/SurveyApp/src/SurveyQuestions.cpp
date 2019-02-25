#include "SurveyQuestions.h"
#include "Text.h" 

void QuestionDisplay::draw(int x, int y, int width, int height)
{
    ofFill();
    Text::get().drawFormattedColumn(
        "<question>"+iter->text+"</question>", 
        x, y + height / 2, width, OF_ALIGN_HORZ_CENTER);
}

void QuestionDisplay::next()
{
    ++iter;
    if (iter == qs.end()) {
        iter = qs.begin();
    }
}

void QuestionDisplay::answered(bool yes)
{
    if (yes)
        ofNotifyEvent(onResponseChange, iter->resultYes);
    else
        ofNotifyEvent(onResponseChange, iter->resultNo);
}
