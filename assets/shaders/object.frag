#version 460 core
#define M_PI 3.1415926535897932384626433832795
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emissive;
    float luster;
};
struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct SpotLight {
    vec3 position;
    vec3 direction;
    float cos_phi;
};

out vec4 FragColor;

in vec3 frag_pos;
in vec3 normal;
in vec2 texcoord;

uniform PointLight u_light;
uniform Material u_material;

void main() {
    float light_distance = length(u_light.position - frag_pos);
    float attenuation = 1.0 / (u_light.constant + u_light.linear * light_distance + u_light.quadratic * (light_distance * light_distance));

    // ambient
    vec3 ambient = u_light.ambient * texture(u_material.diffuse, texcoord).rgb;

    // diffuse
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(u_light.position - frag_pos);
    // vec3 light_dir = normalize(-u_light.direction);
    float diffuse_dot = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = u_light.diffuse * diffuse_dot * texture(u_material.diffuse, texcoord).rgb;

    // specular
    vec3 view_dir = normalize(-frag_pos); // view_pos - frag_pos
    vec3 reflect_dir = reflect(-light_dir, norm);
    float specular_dot = pow(max(dot(view_dir, reflect_dir), 0.0), u_material.luster);
    vec3 specular = u_light.specular * specular_dot * texture(u_material.specular, texcoord).rgb;

    vec3 emissive = texture(u_material.emissive, texcoord).rgb;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}
