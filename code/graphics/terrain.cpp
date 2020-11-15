#include "terrain.h"

Vec3 CalculateVertexNormalFromSurrounding(f32 height_l, f32 height_r, f32 height_u, f32 height_d){
    Vec3 normal = Vec3(height_l - height_r, height_d - height_u, 2.0);
    normal = NormaliseVec3(normal);
    return normal;
}

Terrain CreateTerrain(u32 tiles, u32 vertices_per_tile = 2){
    
    Terrain terrain = {};
    terrain.data_count = tiles * tiles * vertices_per_tile * vertices_per_tile * 6; //3 floats for vertices, 3 floats for normals
    terrain.index_count = ((tiles * vertices_per_tile) - 1) * ((tiles * vertices_per_tile) - 1) * 6;
    terrain.data = (f32 *)MemoryArenaAllocate(&app->permanent_arena, terrain.data_count * sizeof(f32));
    terrain.indices = (u32 *)MemoryArenaAllocate(&app->permanent_arena, terrain.index_count * sizeof(f32));
    u32 count = 0;
    for(u32 i = 0; i < vertices_per_tile * vertices_per_tile * tiles * tiles; i++){
        u32 x = i % (vertices_per_tile * tiles);
        u32 z = (u32) (i / (vertices_per_tile * tiles));
        //positions
        Vec3 terrain_vertex = Vec3(x, InterpolatedNoise2D(x / 4.0f, z / 4.0f) * 10.0f, z);
        terrain.data[count * 6]     = (f32)terrain_vertex.x / (vertices_per_tile - 1);
        terrain.data[count * 6 + 1] = terrain_vertex.y;
        terrain.data[count * 6 + 2] = (f32)terrain_vertex.z / (vertices_per_tile - 1);
        
        //get surrounding heights for normal
        f32 height_l = 0.0f;
        if(x > 0){
            height_l = terrain.data[(count * 6 + 1) - 6];
        }
        
        f32 height_r = 0.0f;
        if(x < (vertices_per_tile * tiles) - 1){
            height_r = terrain.data[(count * 6 + 1) + 6];
        }
        
        f32 height_u = 0.0f;
        if(z < (vertices_per_tile * tiles) - 1){
            height_u = terrain.data[(count * 6 + 1) + (vertices_per_tile * tiles)];
        }
        
        f32 height_d = 0.0f;
        if(z > 0){
            height_d = terrain.data[(count * 6 + 1) - (vertices_per_tile * tiles)];
        }
        
        Vec3 normal = CalculateVertexNormalFromSurrounding(height_l, height_r, height_u, height_d);
        //normals
        terrain.data[count * 6 + 3] = normal.x;
        terrain.data[count * 6 + 4] = normal.y;
        terrain.data[count * 6 + 5] = normal.z;
        count++;
    }
    
    count = 0;
    for(u32 i = 0; i < (tiles * vertices_per_tile) - 1; i++){
        for(u32 j = 0; j < (tiles * vertices_per_tile) - 1; j++){
            u32 top_left = (i + 1) * (tiles * vertices_per_tile) + j;
            u32 top_right = top_left + 1;
            u32 bottom_left = ((i * (tiles * vertices_per_tile)  + j));
            u32 bottom_right = bottom_left + 1;
            
            terrain.indices[count++] = top_right;
            terrain.indices[count++] = bottom_right;
            terrain.indices[count++] = top_left;
            terrain.indices[count++] = bottom_right;
            terrain.indices[count++] = bottom_left;
            terrain.indices[count++] = top_left;
        }
    }
    
    return terrain;
}