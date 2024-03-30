#version 460 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emissive;
    float luster;
};
struct DirectionalLight {
    vec3 direction;

    vec3 diffuse;
    vec3 specular;
};

uniform DirectionalLight u_global_illumination;
#define u_light u_global_illumination
uniform Material u_material0;

vec3 calculate_global_illumination(vec3 norm, vec3 initial_diffuse, vec3 view_dir, vec3 initial_specular) {
    // diffuse
    vec3 light_dir = normalize(-u_light.direction);
    float diffuse_dot = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = u_light.diffuse * diffuse_dot * initial_diffuse;

    // specular
    vec3 reflect_dir = reflect(-light_dir, norm);
    float specular_dot = pow(max(dot(view_dir, reflect_dir), 0.0), u_material0.luster);
    vec3 specular = u_light.specular * specular_dot * initial_specular;

    return diffuse + specular;
}
