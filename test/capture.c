#include "arducam_mipicamera.h"
#include <stdio.h>
#include <string.h>
#define LOG(fmt, args...) fprintf(stderr, fmt "\n", ##args)

IMAGE_FORMAT fmt = {IMAGE_ENCODING_JPEG, 80};

int main(int argc, char **argv) {
    CAMERA_INSTANCE camera_instance;
    LOG("Open camera...");
    int res = arducam_init_camera(&camera_instance);
    if (res) {
        LOG("init camera status = %d", res);
        return -1;
    }
    uint8_t mode = 0;
    res= arducam_set_mode(camera_instance, mode);
    char file_name[100];
    if(fmt.encoding == IMAGE_ENCODING_JPEG){
        sprintf(file_name, "mode%d.jpg", mode);
    }
    LOG("Capture image %s...", file_name);
    uint16_t time = 1200;
    BUFFER *buffer = arducam_capture(camera_instance, &fmt, time);
    if (!buffer){
        LOG("capture timeout.");
        return -1;
    }
    FILE *file = fopen(file_name, "wb");
    fwrite(buffer->data, buffer->length, 1, file);
    fclose(file);
    arducam_release_buffer(buffer);
    LOG("Close camera...");
    res = arducam_close_camera(camera_instance);
    if (res) {
        LOG("close camera status = %d", res);
    }
    return 0;
}
