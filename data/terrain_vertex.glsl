#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normals;
//layout (location = 2) in vec2 tex_coords;

uniform mat4 proj;
uniform mat4 view;

out vec3 pass_normals;
out vec3 pass_vertices;
out vec3 pass_colour;

void main()
{
   // out_colour = colour;
    //gl_Position = ortho * view * vec4(pos.x, pos.y, pos.z, 1.0);
    gl_Position = proj * view * vec4(pos.x, pos.y, pos.z, 1.0);
	pass_normals = normals;
	pass_vertices = pos;

	//calculate lighting
	float ambient_strength = 0.5;
	
	vec3 light_direction = normalize(vec3(1, 1, 1));
	vec3 light_colour = vec3(1.0, 1.0, 1.0);
	
	float diff = max(dot(pass_normals, light_direction), 0.0);
	vec3 diffuse = diff * light_colour;
	
	vec3 final_colour;
	if(pass_vertices.y > 1.9f){
		final_colour = vec3(1.0, 1.0, 1.0);
	} else{
		final_colour = vec3(0.0, 0.48, 0.0);
	}

	vec3 ambient = ambient_strength * light_colour;
    pass_colour = (ambient + diffuse) * final_colour;
}