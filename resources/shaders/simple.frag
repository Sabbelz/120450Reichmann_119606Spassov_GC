#version 150

in  vec3 pass_Normal, pass_Camera_Position, pass_Position;
out vec4 out_Color;

uniform vec3 sunlight_colour, sunlight_position, planet_colour;
uniform float sunlight_intensity, ambient_intensity;

void main() {

  vec3 normal = normalize(pass_Normal);
  vec3 spec_color = vec3(1.0,1.0,1.0);

  vec3 light_dir = normalize(sunlight_position - pass_Position);
  vec3 view_dir = normalize(pass_Camera_Position - pass_Position);
  vec3 half_dir = normalize(light_dir + view_dir);

  float shininess = 20.0f;

  float spec_angle = max(dot(half_dir, normal), 0.0);
  float specular_intensity = sunlight_intensity * pow(spec_angle, shininess); //for changing the intensity just multiply with a float value
  float diffuse_intensity = sunlight_intensity * max(dot(normal, light_dir), 0);

  vec3 specular = specular_intensity * spec_color;
  vec3 diffuse = diffuse_intensity * sunlight_colour;
  vec3 ambient= ambient_intensity * sunlight_colour;


  out_Color = vec4((ambient + diffuse) * planet_colour + specular * sunlight_colour, 1.0);
  //out_Color = vec4(abs(normalize(pass_Normal)), 1.0);
}
