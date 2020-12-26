#include "arducam_mipicamera.h"

class Camera{
    public:
        int init();
        int set_mode(uint8_t mode);
        int capture(uint32_t exptime);
        int close();
    protected:
        CAMERA_INSTANCE camera_instance;
        IMAGE_FORMAT fmt = {IMAGE_ENCODING_PNG, 80};
};