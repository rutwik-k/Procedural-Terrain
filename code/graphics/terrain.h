#ifndef TERRAIN_H
#define TERRAIN_H

struct Terrain{
    f32 *data; //vertices and normals
    u32 *indices;
    u32 size;
    u32 data_count;
    u32 index_count;
};

#endif //TERRAIN_H
