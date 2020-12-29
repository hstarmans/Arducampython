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
        cv::Mat *capture(uint32_t exptime);
        int close();
    protected:
        // settings for sensor OV2311
        CAMERA_INSTANCE camera_instance;
        int width = 1600;
        int height = 1300;
        IMAGE_FORMAT fmt = {IMAGE_ENCODING_I420, 80};
};