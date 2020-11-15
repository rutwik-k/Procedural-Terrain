#ifndef APP_H
#define APP_H

/* App specific state is here, independent of platform */
struct App {
    MemoryArena permanent_arena;
    Renderer renderer;
    
    Camera camera;
};

global App *app = 0;
global Platform *app_platform = 0;

#endif //APP_H
