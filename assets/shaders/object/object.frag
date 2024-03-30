#version 460 core
#define M_PI 3.1415926535897932384626433832795
#define MAX_NUM_LIGHTS 16
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
struct DirectionalLight {
    vec3 direction;

    vec3 diffuse;
    vec3 specular;
};
struct SpotLight {
    vec3 position;
    vec3 direction;
    float cos_phi;
    float cos_gamma;

    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 frag_pos;
in vec3 normal;
in vec2 texcoord;

uniform PointLight u_point_lights[MAX_NUM_LIGHTS];
uniform int u_num_lights;
uniform Material u_material0;
uniform vec3 u_ambient;

vec3 calculate_global_illumination(vec3 norm, vec3 initial_diffuse, vec3 view_dir, vec3 initial_specular);
vec3 calculate_point_light(PointLight light, vec3 norm, vec3 initial_diffuse, vec3 view_dir, vec3 initial_specular);

void main() {
    vec3 result;

    // ambient
    result += u_ambient * texture(u_material0.diffuse, texcoord).rgb;

    // diffuse
    vec3 norm = normalize(normal);
    vec4 diffuse_tex = texture(u_material0.diffuse, texcoord);
    vec3 initial_diffuse = diffuse_tex.a * diffuse_tex.rgb;

    // specular
    vec3 view_dir = normalize(-frag_pos); // view_pos - frag_pos
    vec4 specular_tex = texture(u_material0.specular, texcoord);
    vec3 initial_specular = specular_tex.a * specular_tex.rgb;

    result += calculate_global_illumination(norm, initial_diffuse, view_dir, initial_specular);

    for (int i = 0; i < u_num_lights; i++) {
        result += calculate_point_light(u_point_lights[i], norm, initial_diffuse, view_dir, initial_specular);
    }

    // emissive
    result += texture(u_material0.emissive, texcoord).rgb;

    FragColor = vec4(result, 1.0);
}
