#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();

    ImGui::GetIO().MouseDrawCursor = false;
    ofFile("../../../config.json") >> config;
    ofFile("../../../data.json") >> data;

    categories = config["Categories"].get < std::vector<std::string> >();
    for (auto cat : categories)
    {
        char* str = new char[QSIZE];
        size_t copied = cat.copy(str, QSIZE - 1);
        str[copied] = 0;
        category_tracker[cat] = str;
    }

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.begin();
    bool save = false;
    ImGui::Begin("Categories");
    auto del=categories.end();
    for (auto it = categories.begin(); it != categories.end(); ++it)
    {
        auto& cat = *it;
        ImGui::PushID(cat.c_str());
        char* edited = category_tracker[cat];
        bool isDup = cat != edited && category_tracker.count(edited) != 0;
        if (isDup) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ofColor::grey));
        bool enter = ImGui::InputText("", edited, QSIZE,
            ImGuiInputTextFlags_EnterReturnsTrue);
        if (isDup) ImGui::PopStyleColor();
        ImGui::SameLine();
        if (ImGui::Button("-"))
            del = it;

        save |= enter;

        if (cat != edited)
        {
            ImGui::SameLine();
            ImGui::Text("*");
        }

        if (enter && !isDup)
        {
            std::string new_cat = edited;
            category_tracker.erase(cat);
            category_tracker[new_cat] = edited;
            cat = new_cat;
        }


        ImGui::PopID();
    }




    if (del != categories.end())
    {
        save = true;
        category_tracker.erase(*del);
        categories.erase(del);
    }

    {
        ImGui::PushID("NewEntry");
        bool isDup = category_tracker.count(newEntry) != 0;

        if (isDup) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ofColor::grey));
        bool enter = ImGui::InputText("<return>", newEntry, QSIZE,
            ImGuiInputTextFlags_EnterReturnsTrue);
        if (isDup) ImGui::PopStyleColor();
        
        save |= enter;
        if (enter && !isDup) {
            std::string cat = newEntry;
            char* str = new char[QSIZE];
            size_t copied = cat.copy(str, QSIZE - 1);
            str[copied] = 0;
            category_tracker[cat] = str;
            categories.push_back(cat);
            newEntry[0] = 0;
        }
        ImGui::PopID();
    }
    ImGui::End();

    ImGui::Begin("Scores");
    for (auto& cat : categories)
    {
        if (data["Count"][cat].is_null()) {
            data["Count"][cat] = 0;
        }
        auto& score = data["Count"][cat];
        ImGui::PushItemWidth(100);
        save |= ImGui::InputInt(cat.c_str(), &score.get_ref<json::number_integer_t&>());
    }
    ImGui::End();

    ImGui::Begin("Questions");
    for (auto& Q : config["Questions"])
    {
        if (Q.empty()) 
            continue;

        auto& q = Q["question"].get_ref<json::string_t&>();
        q.reserve(1024);

        if (ImGui::TreeNodeEx(&q, ImGuiTreeNodeFlags_Framed, q.c_str()))
        {
            ImGui::Spacing();
            ImGui::PushID(&q);
            ImGui::Columns(1);
            ImGui::Text("Question: ");
            ImGui::SameLine();
            ImGui::PushItemWidth(-1);

            char* qstr = &q[0];
            bool thisOne = ImGui::InputText("", &q[0], q.capacity());
            // fixes the internal size count
            q.assign(q.c_str());

            save |= thisOne;
            if (thisOne) 
                std::cout << Q["question"].dump(4);
            ImGui::PopItemWidth();
            ImGui::PopID();
            ImGui::Separator();

            auto& yes = Q["yes"];
            auto& no =  Q["no"];

            for (auto cat : categories) {
                if (yes[cat].is_null()) {
                    yes[cat] = 0;
                }
                if (no[cat].is_null()) {
                    no[cat] = 0;
                }
            }

            ImGui::Columns(std::min(4u, categories.size()) + 1);

            for (auto cat : categories) {
                if (ImGui::GetColumnIndex() == 0) {
                    ImGui::Text("");
                    ImGui::Text("yes");
                    ImGui::Text("no");
                    ImGui::NextColumn();
                }

                ImGui::PushID(&cat);
                ImGui::Text(cat.c_str());
                auto& y = yes[cat];
                auto& n = no[cat];
            
                ImGui::Indent();
                ImGui::PushItemWidth(75);
                ImGui::PushID(&y);
                save |= ImGui::InputInt("", &y.get_ref<json::number_integer_t&>());
                ImGui::PopID();
                ImGui::PushID(&n);
                save |= ImGui::InputInt("", &n.get_ref<json::number_integer_t&>());
                ImGui::PopID();
                ImGui::PopItemWidth();
                ImGui::Unindent();

                ImGui::PopID();
                ImGui::NextColumn();
            }
            ImGui::Columns(1);
            if (ImGui::Button("Delete question"))
            {
                Q.clear();
            }
            ImGui::TreePop();
        }
        ImGui::Separator();
    }
    if (ImGui::Button("+ New Question"))
    {
        config["Questions"].push_back({ { "question",""},{"yes",{}},{ "no",{} } });
        save = true;
    }
    ImGui::End();

    if (save) {
        config["Categories"] = categories;
        ofFile("../../../config.json", ofFile::WriteOnly) << config.dump(4);
        ofFile("../../../data.json", ofFile::WriteOnly) << data.dump(4);
    }

    gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
