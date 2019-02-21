#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3, 2);
    ofxApp::get().loadSettings(); //ofxApp settings loaded here!

    settings.stencilBits = 8;
    settings.numSamples = ofxApp::get().getInt("App/numAASamples", 8);

    ofCreateWindow(settings);

    TIME_SAMPLE_SET_FRAMERATE(60);	//if you want setup() to get automatically measured,
    //you need to create the instance once before setup() is called;
    //just call any TIME_SAMPLE_* method to do so

    ofRunApp(new ofApp());
}
