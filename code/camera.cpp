internal void CameraUpdate(Camera *camera){
    camera->velocity = Vec3(0, 0, 0);
    
    camera->yaw   += app_platform->cursor_dx;
    camera->pitch += app_platform->cursor_dy;
    
    Vec3 direction;
    direction.x = cos(camera->yaw) * cos(camera->pitch);
    direction.y = sin(camera->pitch);
    direction.z = sin(camera->yaw) * cos(camera->pitch);
    
    //normalize this
    
    
    if(app_platform->key_down[KEY_W]){
        camera->velocity = Vec3(-camera->front.x, -camera->front.y, -camera->front.z);
    }
    if(app_platform->key_down[KEY_A]){
        camera->velocity = Vec3(-camera->right.x, -camera->right.y, -camera->right.z);
    }
    if(app_platform->key_down[KEY_S]){
        camera->velocity = Vec3(camera->front.x, camera->front.y, camera->front.z);
    }
    if(app_platform->key_down[KEY_D]){
        camera->velocity = camera->right;
    }
    if(app_platform->key_down[KEY_SPACE]){
        camera->velocity = camera->up;
    }
    if(app_platform->key_down[KEY_SHIFT]){
        camera->velocity = Vec3(-camera->up.x, -camera->up.y, -camera->up.z);
    }
    
    camera->pos.z += camera->velocity.z * CAMERA_SPEED * app_platform->dt;
    camera->pos.x += camera->velocity.x * CAMERA_SPEED * app_platform->dt;
    camera->pos.y += camera->velocity.y * CAMERA_SPEED * app_platform->dt;
}