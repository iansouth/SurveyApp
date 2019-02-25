#pragma once

#include "ofMain.h"

class ThreadedTextureSaver : public ofThread {
public:
    ThreadedTextureSaver(ofTexture texture) 
    {
        texture.readToPixels(pixels);
    }

protected:
    virtual void threadedFunction() override
    {

        ofImage image;
        image.setFromPixels(pixels);

        // crop to square
        image.crop((pixels.getWidth() - pixels.getHeight()) / 2, 0, pixels.getHeight(), pixels.getHeight());
        image.resize(100, 100);
        std::string end = "0000";

        ofDirectory dir("images");
        if (!dir.exists())
        {
            dir.create(true);
        }
        else
        {
            char buff[100];
            dir.allowExt("png");
            snprintf(buff, sizeof(buff), "%04d", dir.listDir());
            end = buff;
        }

        image.save("images/file"+end+".png");
    }

    ofPixels pixels;
};

