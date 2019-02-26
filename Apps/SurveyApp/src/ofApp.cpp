#include "ofApp.h"
#include <functional>
#include "Text.h"
#include "ThreadedTextureSaver.h"
#include "ofxJsonSettings.h"
#include "DataModel.h"

//--------------------------------------------------------------
void ofApp::setup() {
    Text::get().setup();
    Text::get().addFont("VeraMono", "fonts/VeraMono-Bold.ttf");

    //define font styles
    ofxFontStash2::Style answer("VeraMono", 40, ofColor::black);
    answer.alignmentV = NVGalign::NVG_ALIGN_MIDDLE;

    ofxFontStash2::Style response("VeraMono", 40, ofColor::white);
    response.alignmentV = NVGalign::NVG_ALIGN_TOP;

    ofxFontStash2::Style question("VeraMono", 55, ofColor::white);
    question.alignmentV = NVGalign::NVG_ALIGN_MIDDLE;


    Text::get().addStyle("answer", answer);
    Text::get().addStyle("response", response);
    Text::get().addStyle("question", question);
    Text::get().pixelDensity = 2.0;

    //Settings::load()

    answerPanel.setup();
    responsePanel.setup();
    responseFbo.allocate(1920, 1080, GL_RGB, 4);
    blurShader.load("blur");
    textureSaver.startThread();

    ofAddListener(answerPanel.onAnswer, this, &ofApp::onAnswer);
    //ofAddListener(questionDisplay.onResponseChange, &responsePanel, &ResponseGui::onUpdate);

    changeState(SHOW_QUESTION);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(0, 0, 0);
    answerPanel.update();
    responsePanel.update();
    if (state == SHOW_CAMERA && stateTime() > 5)
    {
        changeState(SHOW_RESPONSES);
        answerPanel.enable();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    float divide = 0.7*ofGetWidth();
    ofSetHexColor(0xffffff);

    if (state == SHOW_QUESTION)
    {
        responseFbo.begin();
        ofClear(0);
    }
    responsePanel.draw(0, 0, divide, ofGetHeight());
    if (state == SHOW_QUESTION)
    {
        responseFbo.end();
        blurShader.begin();
        responseFbo.getTexture().draw(0, 0);
        blurShader.end();
        questionDisplay.draw(0, 0, divide, ofGetHeight());
    }

    answerPanel.draw(divide, 0, ofGetWidth()-divide, ofGetHeight());

    if (state == SHOW_CAMERA)
    {
        // draw camera
        camera.setAnchorPercent(0.5, 0.5);
        camera.draw(ofGetWidth()/2, ofGetHeight()/2);
    }
}

void ofApp::exit()
{
    textureSaver.stopThread();
    textureSaver.signal();
    textureSaver.waitForThread();
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
    answerPanel.mouseDragged(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (state == SHOW_RESPONSES && stateTime() > 0.5)
    {
        changeState(SHOW_QUESTION);
        answerPanel.enable();
    }
    answerPanel.mousePressed(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    answerPanel.mouseReleased(x, y);
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

void ofApp::onAnswer(bool& yes)
{
    camera = answerPanel.getCameraCopy();
    textureSaver.saveTexture(camera);

    DataModel::get().respond(yes);
    answerPanel.disable();
    changeState(SHOW_CAMERA);
}

void ofApp::ofxAppPhaseWillBegin(ofxApp::Phase phase)
{
    std::cout << "Phase " << (int)phase << std::endl;
}

void ofApp::ofxAppContentIsReady(const std::string & contentID, vector<ContentObject*>)
{
    std::cout << "Content " << contentID << std::endl;
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
