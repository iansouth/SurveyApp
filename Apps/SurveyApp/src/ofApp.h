#pragma once

#include "ofMain.h"
#include <ofxApp.h>

class ofApp : public ofBaseApp, public ofxAppDelegate {

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
		
		// Inherited via ofxAppDelegate
		virtual void ofxAppPhaseWillBegin(ofxApp::Phase) override;
		virtual void ofxAppContentIsReady(const std::string & contentID, vector<ContentObject*>) override;
};
