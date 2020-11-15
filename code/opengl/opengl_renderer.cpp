#include "opengl_renderer.h"
#include "opengl_shader.cpp"

#include "graphics/primitives.h"
#include "graphics/terrain.cpp"

internal void RendererInit(Renderer *renderer){
    /* 
    Terrain terrain = CreateTerrain(5);
    
    glGenVertexArrays(1, &renderer->terrain_vao);
    glBindVertexArray(renderer->terrain_vao);
    
    glGenBuffers(1, &renderer->terrain_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->terrain_vbo);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * terrain.size * terrain.size * 3, terrain.vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &renderer->terrain_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->terrain_ibo);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * (terrain.size - 1) * (terrain.size - 1) * 6, terrain.indices, GL_STATIC_DRAW);
    
    
    
    renderer->terrain_shader = CreateOpenGLShader("terrain_vertex.glsl", "terrain_fragment.glsl");
    
    glUseProgram(renderer->terrain_shader);
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (void *)0);
    glEnableVertexAttribArray(0);
    */ 
    
    renderer->view = Mat4Identity();
    Mat4Translate(&renderer->view, Vec3(0, 0, 0));
    renderer->proj = CreateProjectionMat4(90.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    ShaderLoadMat4(renderer->terrain_shader, renderer->proj, "proj");
    
    
}

internal void RendererStart(Renderer *renderer, Vec3 camera_pos){
    glClearColor(91.0f / 255.0f, 163.0f / 255.0f, 171.0f / 255.0f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(renderer->mode == WIREFRAME){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    Mat4Translate(&renderer->view, Vec3(-camera_pos.x, -camera_pos.y, -camera_pos.z));
}

//elements model
internal void RendererDrawModelE(Renderer *renderer, Model *model){
    glUseProgram(model->shader);
    glBindVertexArray(model->vao);
    ShaderLoadMat4(model->shader, renderer->proj, "proj");
    ShaderLoadMat4(model->shader, renderer->view, "view");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->ibo);
    glDrawElements(GL_TRIANGLES, model->index_count, GL_UNSIGNED_INT, 0);
}

internal void RendererFinish(Renderer *renderer){
    
}

