#include "memory.h"
#include "camera.h"
#include "renderer.h"
#include "app.h"
#include "assets.h"


#include "utility.cpp"
#include "memory.cpp"
#include "camera.cpp"
#include "renderer.cpp"
#include "assets.cpp"

Model terrain_model;

void InitApp(){
    //PerlinNoise1D(41215, 5, 1);
    app = (App *)app_platform->permanent_memory;
    app->permanent_arena = MemoryArenaInit((u8 *)app_platform->permanent_memory + sizeof(App), app_platform->permanent_memory_size - sizeof(App));
    RendererInit(&app->renderer);
    Terrain terrain = CreateTerrain(50);
    terrain_model = CreateModel(terrain.data, terrain.indices, terrain.data_count, terrain.index_count, "terrain_vertex.glsl", "terrain_fragment.glsl");
    app->camera.pos = Vec3(25, 10, 60);
    app->camera.front = Vec3(0, 0, 1);
    app->camera.right = Vec3(1, 0, 0);
    app->camera.up = Vec3(0, 1, 0);
}

void UpdateApp(Platform *_platform){
    app_platform = _platform;
    if(app_platform->is_initialised == 0){
        InitApp();
        app_platform->dt = 1 / app_platform->target_fps;
        app_platform->is_initialised = 1;
    }
    
    if(app_platform->key_down[KEY_1]){
        app->renderer.mode = WIREFRAME;
    }
    if(app_platform->key_down[KEY_2]){
        app->renderer.mode = FILL;
    }
    
    CameraUpdate(&app->camera);
    
    RendererStart(&app->renderer, app->camera.pos);
    RendererDrawModelE(&app->renderer, &terrain_model);
    RendererFinish(&app->renderer);
    
    PlatformUpdateInput(app_platform);
}