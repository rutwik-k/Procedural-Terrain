#define RANDOM_SEED 56

f32 Lerp(float a, float b, float t){
    return a + t * (b-a);
}

Vec3 Vec3Lerp(Vec3 a, Vec3 b, float t){
    Vec3 result = {};
    result.x = Lerp(a.x, b.x, t);
    result.y = Lerp(a.y, b.y, t);
    result.z = Lerp(a.z, b.z, t);
    return result;
}

b32 Vec4Intersects(Vec4 a, Vec4 b){
    b32 result = 0;
    if(a.x < b.x + b.z && a.x + a.z > b.x && a.y < b.y + b.w && a.y + a.w > b.y){
        result = 1;
    }
    return result;
}

Vec2 Vec2Direction(Vec2 a, Vec2 b){
    return Vec2(a.x - b.x, a.y - b.y);
}

f32 Noise2D(i32 x, i32 y){
    i32 val = perlin_hash[(y + RANDOM_SEED) % 256];
    return (perlin_hash[(val + x) % 256] / 256.0f) * 2 - 1.0f;
}

f32 SmoothNoise2D(f32 x, f32 y){
    f32 corners = (Noise2D(x-1, y-1)+Noise2D(x+1, y-1)+Noise2D(x-1, y+1)+Noise2D(x+1, y+1)) / 16.0f;
    f32 sides = (Noise2D(x-1, y)+Noise2D(x+1, y)+Noise2D(x, y+1)+Noise2D(x, y-1)) / 8.0f;
    f32 center = Noise2D(x, y) / 4.0f;
    return corners + sides + center;
}

f32 CosInterpolate(f32 a, f32 b, f32 x){
    f32 ft = x * 3.1415927;
    f32 f = (1 - cos(ft)) * 0.5f;
    
    return a * (1 - f) + b * f;
}

f32 InterpolatedNoise2D(f32 x, f32 y){
    f32 x_fraction = x - ((i32)x);
    f32 y_fraction = y - ((i32)y);
    
    f32 v1 = SmoothNoise2D((i32)x, (i32)y);
    f32 v2 = SmoothNoise2D((i32)x + 1, (i32)y);
    f32 v3 = SmoothNoise2D((i32)x, (i32)y + 1);
    f32 v4 = SmoothNoise2D((i32)x + 1, (i32)y + 1);
    
    f32 i1 = CosInterpolate(v1, v2, x_fraction);
    f32 i2 = CosInterpolate(v3, v4, x_fraction);
    
    return CosInterpolate(i1, i2, y_fraction);
}