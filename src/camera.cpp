#include "camera.h"
#include <linux/v4l2-controls.h>

#define LOG(fmt, args...) fprintf(stderr, fmt "\n", ##args)
#define VCOS_ALIGN_DOWN(p,n) (((ptrdiff_t)(p)) & ~((n)-1))
#define VCOS_ALIGN_UP(p,n) VCOS_ALIGN_DOWN((ptrdiff_t)(p)+(n)-1,(n))

int Camera::init()
{
    int res = arducam_init_camera(&camera_instance);
    if(!res){
        LOG("Something wrong with connect, camera might still function");
    }
    arducam_set_mode(camera_instance, 0);
    LOG("Disable Software Auto Exposure...");
    arducam_software_auto_exposure(camera_instance, 0);
    LOG("Disable Software Auto White Balance...");
    arducam_software_auto_white_balance(camera_instance, 0);
    return 0;
}

int Camera::set_auto_white_balance(bool enable){
    return arducam_software_auto_white_balance(camera_instance, enable);
}

int Camera::set_mode(uint8_t mode)
{
    return arducam_set_mode(camera_instance, mode);
}

int Camera::set_exposure(int newexposuretime)
{
    exposuretime = newexposuretime;
    return arducam_set_control(camera_instance, V4L2_CID_EXPOSURE, newexposuretime);
}

int Camera::get_exposure()
{
    arducam_get_control(camera_instance, V4L2_CID_EXPOSURE, &exposuretime);
    return exposuretime;
}

int Camera::set_resolution(int newwidth, int newheight){
    LOG("This function does not work yet");
    width, height = newwidth, newheight;
    return arducam_set_resolution(camera_instance, &newwidth, &newheight);
}

int Camera::close()
{
    return arducam_close_camera(camera_instance);
}

cv::Mat Camera::capture()
{
    cv::Mat image;
    BUFFER *buffer = arducam_capture(camera_instance, &fmt, exposuretime);
    if (!buffer) {
       LOG("Capture returns nullpointer!!");
       return image; 
    }
    int width_new = VCOS_ALIGN_UP(width, 32);
    int height_new = VCOS_ALIGN_UP(height, 16);
    image = cv::Mat(cv::Size(width_new, height_new*1.5), CV_8UC1, buffer->data);
    cv::cvtColor(image, image, cv::COLOR_YUV2BGR_I420);
    // arducam produces incorrect image and part of it needs to be cropped
    cv::Rect roi(0, 0, width, (height-20));
    cv::Mat crop = image(roi);
    arducam_release_buffer(buffer);
    return crop;
}

void Camera::live_view(float scale = 1.0)
{
    while(1){
        cv::Mat image = capture();
        if(image.empty()) continue;
        cv::resize(image, image, cv::Size(), scale, scale);
        cv::imshow("Arducam", image);
        if(cv::waitKey(30)==27) break;
    }
}