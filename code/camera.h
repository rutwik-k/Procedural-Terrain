/* date = November 13th 2020 8:11 pm */

#ifndef CAMERA_H
#define CAMERA_H

#define CAMERA_SPEED 20

struct Camera{
    Vec3 pos;
    Vec3 velocity;
    Vec3 front;
    Vec3 up;
    Vec3 right;
    
    f32 yaw = -90.0f;
    f32 pitch;
    
    b32 moving;
};

#endif //CAMERA_H
