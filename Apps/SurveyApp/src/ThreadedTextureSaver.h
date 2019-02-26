#pragma once

#include "ofMain.h"
#include <Poco/Condition.h>

class ThreadedTextureSaver : public ofThread {
public:
    ThreadedTextureSaver() 
    {
    }

    void saveTexture(ofTexture texture) {
        ofPixels* pixels = new ofPixels();
        
        // need to do this on main/gl thread
        texture.readToPixels(*pixels);

        mutex.lock();
        condition.signal();
        dataQueue.push(pixels);
        mutex.unlock();
    }


    void signal()
    {
        mutex.lock();
        condition.signal();
        mutex.unlock();
    }


protected:
    virtual void threadedFunction() override
    {
        while (isThreadRunning()) {
            ofPixels* pixels = nullptr;
            mutex.lock();
            if (dataQueue.empty()) {
                condition.wait(mutex);

                // Maybe we got signaled at shutdown
                if (dataQueue.empty())
                {
                    mutex.unlock();
                    continue;
                }
            }
            pixels = dataQueue.front();
            dataQueue.pop();
            mutex.unlock();

            ofImage image;
            image.setFromPixels(*pixels);

            int w = pixels->getWidth();
            int h = pixels->getHeight();
            delete pixels;

            // crop to square
            image.crop((w - h) / 2, 0, h, h);
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
    }

    Poco::Condition condition;
    std::queue<ofPixels*> dataQueue;
};

