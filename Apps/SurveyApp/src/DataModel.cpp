#include "DataModel.h"
#include "ofMain.h"

std::string DataModel::getQuestion()
{
    if(questions.empty())
        return "";

    return questions[currentQ].text;
}

void DataModel::respond(bool yes)
{
    if (questions.empty())
        return;

    ResponseChanges& _changes = yes ? questions[currentQ].yes : questions[currentQ].no;
    for (auto change : _changes)
    {
        scores[change.category] += change.change;
    }

    // Write out
    for (auto cat : categories) {
        data["Count"][cat] = scores[cat];
    }

    ofSavePrettyJson("data.json", data);
    currentQ = (currentQ + 1) % questions.size();
}

DataModel::DataModel()
{
    config = ofLoadJson("config.json");
    data = ofLoadJson("data.json");

    for (auto cat : config["Categories"])
    {
        categories.push_back(cat);
    }

    for (auto Q : config["Questions"])
    {
        std::cout << Q << std::endl;
        Question q;
        q.text = Q["question"];
        
        auto yes = Q["yes"];
        auto no = Q["no"];

        for (auto it = yes.begin(); it != yes.end(); ++it) {
            q.yes.push_back({ it.key(), it.value() });
        }

        for (auto it = no.begin(); it != no.end(); ++it) {
            q.no.push_back({ it.key(), it.value() });
        }
        questions.push_back(q);
    }

    auto count = data["Count"];
    std::cout << count << std::endl;
    for (auto it = count.begin(); it != count.end(); ++it) {
        std::cout << it.key() << " " << it.value() << std::endl;
        scores[it.key()] = it.value();
    }

#if 0
    config.open("data/config2.json");

    auto C = config["Categories"];
    for (int i = 0; i < C.size(); ++i) {
        categories.push_back(C[i].asString());
    }

    auto QS = config["Questions"];
    for (int i = 0; i < QS.size(); ++i) {
        auto Q = QS[i];
        Question q;
        q.text = Q["question"].asString();

        auto yes = Q["yes"];
        for (auto cat : yes.getMemberNames())
            q.yes.push_back({ cat, yes[cat].asInt() });
        
        auto no = Q["no"];
        for (auto cat : no.getMemberNames())
            q.no.push_back({ cat, no[cat].asInt() });

        questions.push_back(q);
    }


    data.open("data/data2.json");
    auto R = data["Count"];
    for (auto cat : categories)
    {
        scores[cat] = R[cat].asInt();
    }
#endif
}
