#version 460 core
void main() {
    float light_distance = length(u_light.position - frag_pos);
    // float attenuation = 1.0 / (u_light.constant + u_light.linear * light_distance + u_light.quadratic * (light_distance * light_distance));
    float attenuation = 1.0;

    // ambient
    vec3 ambient = u_light.ambient * texture(u_material.diffuse, texcoord).rgb;

    float cos_theta = dot(normalize(-u_light.direction), normalize(u_light.position - frag_pos));
    // float intensity = 1.0;
    float cos_gamma = mix(u_light.cos_gamma, 0.0, light_distance / 256);
    float intensity = (cos_theta - cos_gamma) / (u_light.cos_phi - cos_gamma);
    intensity = clamp(intensity, 0.0, 1.0);
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

    diffuse *= attenuation;
    specular *= attenuation;

    diffuse *= intensity;
    specular *= intensity;

    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}
