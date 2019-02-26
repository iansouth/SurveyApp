#include "QuestionDisplay.h"
#include "Text.h" 
#include "DataModel.h"

void QuestionDisplay::draw(int x, int y, int width, int height)
{
    ofFill();
    Text::get().drawFormattedColumn(
        "<question>"+DataModel::get().getQuestion()+"</question>", 
        x, y + height / 2, width, OF_ALIGN_HORZ_CENTER);
}
