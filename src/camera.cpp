#include "camera.h"

#define LOG(fmt, args...) fprintf(stderr, fmt "\n", ##args)
#define VCOS_ALIGN_DOWN(p,n) (((ptrdiff_t)(p)) & ~((n)-1))
#define VCOS_ALIGN_UP(p,n) VCOS_ALIGN_DOWN((ptrdiff_t)(p)+(n)-1,(n))

int Camera::init()
{
    return arducam_init_camera(&camera_instance);
}

int Camera::set_mode(uint8_t mode)
{
    return arducam_set_mode(camera_instance, mode);
}

int Camera::close()
{
    return arducam_close_camera(camera_instance);
}

cv::Mat *Camera::capture(uint32_t exptime)
{
    LOG("Disable Software Auto Exposure...");
    arducam_software_auto_exposure(camera_instance, 0);
    LOG("Disable Software Auto White Balance...");
    arducam_software_auto_white_balance(camera_instance, 0);
    BUFFER *buffer = arducam_capture(camera_instance, &fmt, exptime);
    if (!buffer) 
       LOG("Capture returns nullpointer!!");
       return NULL;
    // The actual width and height of the IMAGE_ENCODING_RAW_BAYER format and the IMAGE_ENCODING_I420 format are aligned, 
    // width 32 bytes aligned, and height 16 byte aligned.
    //int width_new = VCOS_ALIGN_UP(width, 32);
    //int height_new = VCOS_ALIGN_UP(height, 16);
    cv::Mat *image = new cv::Mat(cv::Size(width, height), CV_8UC1, buffer->data);
    arducam_release_buffer(buffer);
    return image;
}