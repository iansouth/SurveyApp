#pragma once

#include "ofMain.h"
#include <ofxApp.h>
#include "AnswerGui.h"
#include "QuestionDisplay.h"
#include "ResponseGui.h"
#include <list>
#include "ThreadedTextureSaver.h"

class ofApp : public ofBaseApp, public ofxAppDelegate {

    public:
        void setup();
        void update();
        void draw();
        void exit();

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
        void onAnswer(bool& yes);
        // Inherited via ofxAppDelegate
        virtual void ofxAppPhaseWillBegin(ofxApp::Phase) override;
        virtual void ofxAppContentIsReady(const std::string & contentID, vector<ContentObject*>) override;

private:
        AnswerGui answerPanel;
        ResponseGui responsePanel;
        QuestionDisplay questionDisplay;
        ofFbo responseFbo;
        ofShader blurShader;
        ofTexture camera;
        ThreadedTextureSaver textureSaver;
        enum State {
            START, SHOW_QUESTION, SHOW_CAMERA, SHOW_RESPONSES
        };

        void changeState(State s) {
            state = s;
            stateChangeTime = ofGetCurrentTime();
        }
        float stateTime() {
            return ofGetCurrentTime().getAsSeconds() - stateChangeTime.getAsSeconds();
        }
        State state = START;
        ofTime stateChangeTime = ofGetCurrentTime();
};
