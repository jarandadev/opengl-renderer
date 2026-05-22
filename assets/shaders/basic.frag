#version 330 core
out vec4 FragColor;

in vec2 v_texCoord;
in vec3 v_normal;

uniform sampler2D u_diffuse;
uniform sampler2D u_specular;
uniform vec3 u_color;
uniform float u_shininess;
uniform bool u_hasDiffuse;
uniform bool u_hasSpecular;

void main() {
    vec3 diffuseColor = u_hasDiffuse ? texture(u_diffuse, v_texCoord).rgb : u_color;

    FragColor = vec4(diffuseColor, 1.0);
}