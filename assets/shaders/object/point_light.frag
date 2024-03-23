#version 460 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emissive;
    float luster;
};
struct PointLight {
    vec3 position;

    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 frag_pos;

uniform Material u_material;

vec3 calculate_point_light(PointLight light, vec3 norm, vec3 initial_diffuse, vec3 view_dir, vec3 initial_specular) {
    float light_distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * light_distance + light.quadratic * (light_distance * light_distance));
    
    // diffuse
    vec3 light_dir = normalize(light.position - frag_pos);
    float diffuse_dot = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = light.diffuse * diffuse_dot * initial_diffuse;

    // specular
    vec3 reflect_dir = reflect(-light_dir, norm);
    float specular_dot = pow(max(dot(view_dir, reflect_dir), 0.0), u_material.luster);
    vec3 specular = light.specular * specular_dot * initial_specular;

    diffuse *= attenuation;
    specular *= attenuation;

    return diffuse + specular;
}
