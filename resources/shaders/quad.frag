#version 150

in vec2 pass_tex_coordinates;

out vec4 out_Color;

uniform sampler2D screen_texture;
uniform vec2 texture_size;
uniform bool horizontal_mirroring, vertical_mirroring, greyscale, blur;

void main(){

    if(horizontal_mirroring){
        pass_tex_coordinates.y = 1.0 - pass_tex_coordinates.y;
    }

    if(vertical_mirroring){
        pass_tex_coordinates.x = 1.0 - pass_tex_coordinates.x;
    }

    if(blur){
        vec2 pixel_size = vec2(1.0, 1.0)/texture_size;

        // neighbouing pixels 3x3 group
        vec2 pixel_neighbourhood[9] = vec[](
            vec2(-pixel_size.x, pixel_size.y),  vec2(0.0f, pixel_size.y),  vec2(pixel_size.x, pixel_size.y),
            vec2(-pixel_size.x, 0.0f),          vec2(0.0f, 0.0f),          vec2(pixel_size.x, 0.0f),
            vec2(-pixel_size.x, -pixel_size.y), vec2(0.0f, -pixel_size.y), vec2(pixel_size.x, -pixel_size.y)
        );

        // weigting matrix
        float gaussian3x3_kernel_lane[9] = float[](
            1.0/16, 1.0/8, 1.0/16,
            1.0/8 , 1.0/4, 1.0/8 ,
            1.0/16, 1.0/8, 1.0/16
        );

        // calculating colour for all positions and adding them up to one
        vec3 out_colour_rgb = vec3(0.0, 0.0, 0.0);
        for(int i = 0; i < 9; i++){
            out_colour_rgb += vec3(texture(screen_texture, pass_tex_coordinates.xy + pixel_neighbourhood[i]))
            * gaussian3x3_kernel_lane[i];
        }
        out_Color = vec4(out_colour_rgb, 1.0);
    } else {
        out_Color = texture(screen_texture, pass_tex_coordinates);
    }

    if(greyscale) {
        // using luminance formula given in the exercise
        float luminance = (0.2126*out_Color.r+0.7152*out_Color.g+0.0722*out_Color.b);
        out_Color = vec4(luminance,luminance,luminance,1.0);
    }
}
