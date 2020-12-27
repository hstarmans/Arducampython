#include "camera.h"

int Camera::init()
{
    return arducam_init_camera(&camera_instance);
}

int Camera::set_mode(uint8_t mode)
{
    return arducam_set_mode(&camera_instance, mode);
}

int Camera::close()
{
    return arducam_close_camera(&camera_instance);
}

int Camera::capture(uint32_t exptime)
{
    BUFFER *buffer = arducam_capture(&camera_instance, &fmt, exptime);
    return 0;
}
// you need to release the buffer!?
// arducam_release_buffer(buffer);