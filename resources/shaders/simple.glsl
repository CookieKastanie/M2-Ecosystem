#AKILA_VERTEX
	
out vec2 uv;
out vec3 normal;

uniform mat4 M;
	
void main() {
	gl_Position = u_camera.pv * M * a_position;
	uv = a_uv.xy;
	normal = mat3(M) * a_normal.xyz;
}

#AKILA_FRAGMENT
	
in vec2 uv;
in vec3 normal;
out vec4 fragColor;

uniform sampler2D albedo;

void main() {
	float l = dot(vec3(0, 1, 0), normalize(normal)) * 0.5 + 0.5;

	vec3 color = texture(albedo, uv).rgb;
	fragColor = vec4(color * l, 1.0);
}
