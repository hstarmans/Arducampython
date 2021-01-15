#include "arducam_mipicamera.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <stdio.h>
#include <string.h>

class Camera{
    public:
        int init();
        int set_mode(uint8_t mode);
        int set_resolution(int width, int height);
        cv::Mat capture(uint32_t exptime);
        void live_view(uint32_t exptime, float scale);
        int close();
    protected:
        int width = 1600;
        int height = 1300;
        // settings for sensor OV2311
        CAMERA_INSTANCE camera_instance;
        IMAGE_FORMAT fmt = {IMAGE_ENCODING_I420, 80};
};