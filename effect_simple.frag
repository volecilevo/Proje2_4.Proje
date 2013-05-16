#version 120

/*
	ramp_texture için sampler1D ve texture1D(ramp_texture, initial_color.r) 
	denedim ancak bu durumda doğru çalışmadı ekrana resim değil sadece siyah
	renk çizildi. Sanırım nedeni, opengl kodunda da texture yüklerken Texture2D
	olarak yüklemek.
*/

uniform sampler2D in_texture;
uniform sampler2D ramp_texture;   
uniform sampler2D fbo_texture;
uniform float offset;
varying vec2 f_texcoord;
 
void main(void) {

	vec3 initial_color = texture2D(in_texture, f_texcoord).xyz;
	vec3 final_color;
	final_color.r = texture2D(ramp_texture, vec2(initial_color.r, 1)).r;
	final_color.g = texture2D(ramp_texture, vec2(initial_color.g, 1)).g;
	final_color.b = texture2D(ramp_texture, vec2(initial_color.b, 1)).b;
    gl_FragColor = vec4(final_color, 1.0);
}

