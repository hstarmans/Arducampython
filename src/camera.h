#ifndef CAMERA_H  
#define CAMERA_H

#include "arducam_mipicamera.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <stdio.h>
#include <string.h>
#include <cstdint> // 2. Required for uint8_t

class Camera{
    public:
        // Optional: Constructor to zero-out variables
        Camera() : camera_instance(nullptr) {}

        // 3. Destructor: Auto-close camera if object is deleted/goes out of scope
        ~Camera() {
            if (camera_instance) {
                close();
            }
        }

        int init();
        int set_mode(uint8_t mode);
        int get_exposure();
        int set_exposure(int newexposuretime);
        int set_auto_white_balance(bool enable);
        int set_resolution(int width, int height);
        
        cv::Mat capture();
        
        void live_view(float scale = 1.0); 
        
        int close();

    protected:

        int exposuretime = 3000;
        int width = 1600;
        int height = 1300;
        
        // settings for sensor OV2311
        CAMERA_INSTANCE camera_instance;
        
        // This struct init is valid C++11
        IMAGE_FORMAT fmt = {IMAGE_ENCODING_I420, 50}; 
};

#endif 