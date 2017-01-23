#version 410

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 texture_coord;

uniform mat4 view, proj, model;

uniform vec3 light;

out vec3 position_eye, normal_eye, light_position_eye;


void main(){

  position_eye = vec3(view*model*vec4(vertex_position, 1.0));
  normal_eye = mat3(transpose(inverse(view*model))) * vertex_normal;  
  light_position_eye = light;
  gl_Position = proj* vec4(position_eye, 1.0);

  //light_position_eye = vec3(view*vec4(light, 1.0));
}


  