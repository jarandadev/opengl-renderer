#version 330 core
out vec4 FragColor;

in vec3 v_fragPos;
in vec3 v_normal;
in vec2 v_texCoord;

struct Light {
    vec3 position;
    vec3 color;
    float intensity;
    int type; // 0 = Point, 1 = Directional
};

uniform Light u_lights[8];
uniform int u_numLights;

uniform sampler2D u_diffuse;
uniform sampler2D u_specular;
uniform vec3 u_color;
uniform float u_shininess;
uniform bool u_hasDiffuse;
uniform bool u_hasSpecular;

uniform vec3 u_viewPos;

void main() {
    vec3 norm = normalize(v_normal);
    vec3 viewDir = normalize(u_viewPos - v_fragPos);

    vec3 diffuseColor = u_hasDiffuse ? texture(u_diffuse, v_texCoord).rgb : u_color;
    vec3 specularColor = u_hasSpecular ? texture(u_specular, v_texCoord).rgb : vec3(0.8);

    vec3 ambient = 0.08 * diffuseColor;
    vec3 result = ambient;

    for(int i = 0; i < u_numLights; ++i) {
        vec3 lightDir;
        float attenuation = 1.0;

        if(u_lights[i].type == 0) // Point
        {
            vec3 delta = u_lights[i].position - v_fragPos;
            float dist = length(delta);
            lightDir = normalize(delta);
            attenuation = 1.0 / (1.0 + 0.09 * dist + 0.032 * dist * dist);
        } else // Directional
        {
            lightDir = normalize(-u_lights[i].position);  // position = dirección
        }

        // Diffuse
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * diffuseColor * u_lights[i].color * u_lights[i].intensity;

        // Specular (Blinn-Phong)
        vec3 halfDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(norm, halfDir), 0.0), u_shininess);
        vec3 specular = spec * specularColor * u_lights[i].color * u_lights[i].intensity;

        result += (diffuse + specular) * attenuation;
    }

    FragColor = vec4(result, 1.0);
}