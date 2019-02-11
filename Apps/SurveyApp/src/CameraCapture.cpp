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

void CameraCapture::init()
{
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(1280,720);
}

void CameraCapture::update()
{
	vidGrabber.update();
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