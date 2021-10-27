#AKILA_VERTEX
	
out vec2 uv;

uniform mat4 M;
	
void main() {
	gl_Position = a_position;
	uv = a_uv.xy;
}

#AKILA_FRAGMENT
	
in vec2 uv;
out vec4 fragColor;

uniform sampler2D albedo;

void main() {
	vec3 color = texture(albedo, uv).rgb;
	fragColor = vec4(color, 1.0);
}
