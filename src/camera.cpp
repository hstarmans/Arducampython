#include "camera.h"

int Camera::init():
{
    return arducam_init_camera(&CAMERA_INSTANCE);
}

int Camera::set_mode(uint8_t mode):
{
    return arducam_set_mode(&CAMERA_INSTANCE, mode)
}

int Camera::close():
{
    return arducam_close_camera(&CAMERA_INSTANCE);
}

int Camera::capture(uint32_t exptime):
{
    BUFFER *buffer = arducam_capture(&CAMERA_INSTANCE, &fmt, exptime);
    return 0;
}
// you need to release the buffer!?
// arducam_release_buffer(buffer);