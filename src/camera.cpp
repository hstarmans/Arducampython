#include "camera.h"
#include <linux/v4l2-controls.h>
#include <thread>  // Required for sleep_for
#include <chrono>  // Required for milliseconds
#include <cstdio>  // Required for fprintf
#include <iostream>

#define LOG(fmt, args...) fprintf(stderr, fmt "\n", ##args)
#define VCOS_ALIGN_DOWN(p,n) (((ptrdiff_t)(p)) & ~((n)-1))
#define VCOS_ALIGN_UP(p,n) VCOS_ALIGN_DOWN((ptrdiff_t)(p)+(n)-1,(n))

int Camera::init()
{
    int max_retries = 5;
    int retry_delay_ms = 200;
    int res = -1;

    for(int i = 0; i < max_retries; i++) {
        LOG("Attempting to connect to camera (Attempt %d/%d)...", i+1, max_retries);
        
        // Try to init
        res = arducam_init_camera(&camera_instance);
        
        // 0 usually indicates success in C APIs
        if(res == 0) {
            LOG("Camera connected successfully!");
            break; 
        }

        LOG("Connection failed (Error: %d). Retrying in %d ms...", res, retry_delay_ms);
        // Don't sleep on the very last attempt if we are just going to fail anyway
        if (i < max_retries - 1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(retry_delay_ms));
        }
    }

    // If we exhausted all retries and still failed
    if(res != 0) {
        LOG("CRITICAL: Could not connect to camera after %d attempts.", max_retries);
        return -1; // Return error code to python
    }

    // --- Rest of your setup code ---
    arducam_set_mode(camera_instance, 0);
    
    // Safety check: verify mode set worked?
    // Some sensors need a moment after set_mode before accepting exposure commands
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); 

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
    this->width = newwidth;
    this->height = newheight;
    return arducam_set_resolution(camera_instance, &newwidth, &newheight);
}

int Camera::close()
{
    return arducam_close_camera(camera_instance);
}

cv::Mat Camera::capture()
{
    // FIX: Check if resolution is set to avoid division by zero or invalid ROI
    if (width == 0 || height == 0) {
        LOG("Error: Camera resolution not set.");
        return cv::Mat();
    }

    BUFFER *buffer = arducam_capture(camera_instance, &fmt, exposuretime);
    if (!buffer) {
       LOG("Capture returns nullpointer!!");
       return cv::Mat(); 
    }

    int width_new = VCOS_ALIGN_UP(width, 32);
    int height_new = VCOS_ALIGN_UP(height, 16);

    // FIX: Use separate variables for clarity and safety.
    // 'raw_wrapper' does NOT own the data (it points to buffer->data)
    cv::Mat raw_wrapper = cv::Mat(cv::Size(width_new, height_new * 1.5), CV_8UC1, buffer->data);
    
    cv::Mat bgr_image;
    // Converts and allocates NEW memory for bgr_image because the size changes
    cv::cvtColor(raw_wrapper, bgr_image, cv::COLOR_YUV2BGR_I420);

    // Release the driver buffer immediately after conversion. 
    // bgr_image is safe because it has its own copy of the data.
    arducam_release_buffer(buffer);

    // ROI Check to prevent crash
    if (height <= 20) {
         return bgr_image; // Cannot crop if too small
    }

    // Crop the result
    cv::Rect roi(0, 0, width, (height - 20));
    
    // .clone() forces a deep copy. 
    // This ensures the returned Mat is continuous in memory and detached from the larger buffer.
    return bgr_image(roi).clone();
}

void Camera::live_view(float scale)
{
    LOG("Starting Live View. Press ESC to exit.");
    
    // Important: Create window strictly so waitKey has context if capture fails
    cv::namedWindow("Arducam", cv::WINDOW_AUTOSIZE);

    while(1){
        cv::Mat image = capture();
        if(image.empty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            // Check for ESC key even during errors so you can exit the loop
            if(cv::waitKey(30) == 27) break;
            continue; 
        }
        
        if (scale != 1.0) {
            cv::resize(image, image, cv::Size(), scale, scale);
        }
        
        cv::imshow("Arducam", image);
        if(cv::waitKey(30)==27) break;
    }
    cv::destroyWindow("Arducam");
}