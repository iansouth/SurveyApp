#pragma once

#include "ofMain.h"
#include "ofxImGui.h"

#define QSIZE 50

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        // We need to use internal int representation instead of int64_t, so that ImGui can directly modify the references
        using json = nlohmann::basic_json<std::map, std::vector, std::string, bool, int, unsigned int, float>;
        json config, data;
        ofxImGui::Gui gui;
        std::vector<std::string> categories;
        std::map<std::string, char*> category_tracker;
        char newEntry[QSIZE];
        char newQuestion[1024];
};
