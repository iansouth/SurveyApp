#pragma once

#include "ofMain.h"

class CaptureImage
{
public:
	CaptureImage(const ofPixels& pixels, ofTime time);
	~CaptureImage() {}

	void draw(int x, int y, int width, int height);
	double getCaptureAgeSeconds();
private:
	ofTexture texture;
	ofTime captureTime;
	static ofShader filterShader;
};

class CameraCapture
{
public:
	CameraCapture(int width=640, int height=480);
	~CameraCapture();

	void init();
	void update();
	CaptureImage* captureImage();

private:
	ofVideoGrabber vidGrabber;
	int camWidth, camHeight;
};

