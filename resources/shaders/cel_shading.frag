#version 150

in  vec3 pass_Normal, pass_Camera_Position, pass_Position, pass_Camera_Position_outline;
out vec4 out_Color;

uniform vec3 sunlight_colour, sunlight_position, planet_colour;
uniform float sunlight_intensity, ambient_intensity;

void main() {

    // 5 vectors need for calculating Blinn-Phong. R(reflection on the surface), V the viewer, L the light-source, N the normalized surface normal, H the half vector between light and the viewer
    vec3 normal = normalize(pass_Normal);
    vec3 spec_color = vec3(1.0,1.0,1.0);

    vec3 light_dir = normalize(sunlight_position - pass_Position); //postition of the surface (3D) & normalize (pass_position)
    vec3 view_dir = normalize(pass_Camera_Position - pass_Position); //position of the viewer
    vec3 half_dir = normalize(light_dir + view_dir); //half vector between the light and the viewer

    vec3 view_dir_outline = normalize(pass_Camera_Position_outline - pass_Position); //position of the viewer

    float shininess = 20.0f;

    float spec_angle = max(dot(half_dir, normal), 0.0);
    float specular_intensity = sunlight_intensity * pow(spec_angle, shininess); //for changing the intensity just multiply with a float value
    float diffuse_intensity = sunlight_intensity * max(dot(normal, light_dir), 0);

    vec3 specular = specular_intensity * spec_color; //specular light factorimg
    vec3 diffuse = diffuse_intensity * sunlight_colour; //diffuse light factoring
    vec3 ambient= ambient_intensity * sunlight_colour; //ambient light factoring

    // settings of the outline
    vec4 outline_colour = vec4(0.0,1.0,1.0,1.0);
    float outline_thickness = 0.25;

    if (abs(dot(normal, view_dir_outline)) < outline_thickness){
        out_Color = outline_colour;
    } else {
        if (diffuse_intensity > 0.8)
        diffuse = 1.0 * sunlight_colour;
        else if (diffuse_intensity > 0.6)
        diffuse = 0.7 * sunlight_colour;
        else if (diffuse_intensity > 0.4)
        diffuse = 0.5 * sunlight_colour;
        else if (diffuse_intensity > 0.2)
        diffuse = 0.3 * sunlight_colour;
        else
        diffuse = 0.15 * sunlight_colour;

        out_Color = vec4((ambient + diffuse) * planet_colour + specular * sunlight_colour, 1.0);
        //out_Color = vec4(abs(normalize(pass_Normal)), 1.0);
    }
}
