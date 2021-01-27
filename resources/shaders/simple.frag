#version 150

// input variables
in vec2 pass_tex_coordinates;
in vec3 pass_Normal, pass_Camera_Position, pass_Position;
in mat4 pass_normal_matrix, pass_model_matrix, pass_view_matrix;

//output variables
out vec4 out_Color;

// lokal variables
uniform vec3 sunlight_colour, sunlight_position, planet_colour;
uniform float sunlight_intensity, ambient_intensity;
uniform sampler2D TextureSampler, NormalSampler;

void main() {

    // get information from texture(colour) and normal map (normal)
    vec4 sphere_texture = texture(TextureSampler, pass_tex_coordinates);
    vec4 sphere_normal_texture = texture(NormalSampler, pass_tex_coordinates);

    // predefined normal scale
    float normal_scale = 0.5;
    vec3 map_normal = sphere_normal_texture.xyz * 2.0 - 1.0;
    map_normal.xy = map_normal.xy * normal_scale;
    vec3 vertex_pos = pass_Position;

    // 5 vectors need for calculating Blinn-Phong. R(reflection on the surface), V the viewer, L the light-source, N the normalized surface normal, H the half vector between light and the viewer
    vec3 normal = normalize(pass_Normal);
    vec3 spec_color = vec3(1.0,1.0,1.0);

    //vec3 trans_light_pos = (pass_view_matrix * vec4(sunlight_position,1.0)).xyz;
    vec3 light_dir = normalize(sunlight_position - pass_Position); //postition of the surface (3D) & normalize (pass_position)
    //vec3 light_dir = normalize(trans_light_pos - pass_Position);
    vec3 view_dir = normalize(pass_Camera_Position - pass_Position); //position of the viewer
    vec3 half_dir = normalize(light_dir + view_dir); //half vector between the light and the viewer

    float shininess = 20.0f;

    float spec_angle = max(dot(half_dir, normal), 0.0);
    float specular_intensity = sunlight_intensity * pow(spec_angle, shininess); //for changing the intensity just multiply with a float value
    float diffuse_intensity = sunlight_intensity * max(dot(normal, light_dir), 0);

    vec3 specular = specular_intensity * spec_color; //specular light factorimg
    vec3 diffuse = diffuse_intensity * sunlight_colour; //diffuse light factoring
    vec3 ambient= ambient_intensity * sunlight_colour; //ambient light factoring


    out_Color = vec4((ambient + diffuse) * sphere_texture.rgb + specular * sunlight_colour, 1.0);
    //out_Color = vec4((ambient + diffuse) * planet_colour + specular * sunlight_colour, 1.0);
    //out_Color = vec4(abs(normalize(pass_Normal)), 1.0);
}
