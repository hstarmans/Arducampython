#include "camera.h"

#define LOG(fmt, args...) fprintf(stderr, fmt "\n", ##args)
#define VCOS_ALIGN_DOWN(p,n) (((ptrdiff_t)(p)) & ~((n)-1))
#define VCOS_ALIGN_UP(p,n) VCOS_ALIGN_DOWN((ptrdiff_t)(p)+(n)-1,(n))

int Camera::init()
{
    int res = arducam_init_camera(&camera_instance);
    if(!res){
        LOG("Can't connect to camera");
        return -1;
    }
    arducam_set_mode(camera_instance, 0);
    LOG("Disable Software Auto Exposure...");
    arducam_software_auto_exposure(camera_instance, 0);
    LOG("Disable Software Auto White Balance...");
    arducam_software_auto_white_balance(camera_instance, 0);
    return 0;
}

int Camera::set_mode(uint8_t mode)
{
    return arducam_set_mode(camera_instance, 0);
}

int Camera::close()
{
    return arducam_close_camera(camera_instance);
}

cv::Mat *Camera::capture(uint32_t exptime)
{
    BUFFER *buffer = arducam_capture(camera_instance, &fmt, exptime);
    if (!buffer) {
       LOG("Capture returns nullpointer!!");
       return NULL;
    }
    int width_new = VCOS_ALIGN_UP(width, 32);
    int height_new = VCOS_ALIGN_UP(height, 16);
    cv::Mat *image = new cv::Mat(cv::Size(width_new, height_new*1.5), CV_8UC1, buffer->data);
    cv::cvtColor(*image, *image, cv::COLOR_YUV2BGR_I420);
    arducam_release_buffer(buffer);
    return image;
}

cv::Mat *Camera::pythoncapture(uint32_t exptime)
{
    // data is sent over to python, you need to explicitly clear it
    // if cpature is called directly; this results in a memory leak 
    if(pyimage != NULL){delete pyimage;}
    pyimage = capture(exptime);
    return  pyimage;
}

void Camera::live_view(uint32_t exptime)
{
    while(1){
	cv::Mat *image = capture(exptime);
    if(!image) continue;
    cv::imshow("Arducam", *image);
    if(cv::waitKey(30)==27) break;
	delete image;
    }
}
