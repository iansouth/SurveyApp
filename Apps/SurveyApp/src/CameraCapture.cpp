#include "CameraCapture.h"

ofShader CaptureImage::filterShader;

CameraCapture::CameraCapture(int width, int height)
    : camWidth(width), camHeight(height)
{
}

CameraCapture::~CameraCapture()
{
    vidGrabber.close();
}

void CameraCapture::setup()
{
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.setup(1280,720,true);
}

void CameraCapture::update()
{
    vidGrabber.update();
}

ofTexture* CameraCapture::getPreviewTexture()
{
    return &vidGrabber.getTexture();
}

CaptureImage* CameraCapture::captureImage()
{
    return new CaptureImage(vidGrabber.getPixels(), ofGetCurrentTime());
}

CaptureImage::CaptureImage(const ofPixels & pixels, ofTime time)
    : captureTime(time)
{
    texture.loadData(pixels);
}


void CaptureImage::draw(int x, int y, int width, int height)
{
    if(!filterShader.isLoaded()) 
    {
        filterShader.load("shader");
        filterShader.printActiveUniforms();
    }

    filterShader.begin();
    texture.draw(x, y, width, height);
    filterShader.end();
}

double CaptureImage::getCaptureAgeSeconds() 
{
    ofTime now = ofGetCurrentTime();
    return now.getAsSeconds()-captureTime.getAsSeconds();
}