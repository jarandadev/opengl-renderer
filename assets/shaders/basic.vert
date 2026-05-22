#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 v_texCoord;
out vec3 v_normal;

void main() {
    v_texCoord = aTexCoord;
    v_normal = mat3(transpose(inverse(u_model))) * aNormal;
    gl_Position = u_projection * u_view * u_model * vec4(aPos, 1.0);
}