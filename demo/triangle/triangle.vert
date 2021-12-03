#version 450 core

const vec2 triangle_positions[3] = vec2[](
	vec2(0.5, -0.5),
	vec2(0.5, 0.5),
	vec2(-0.5, 0.5)
);

void main() {
	gl_Position = vec4(triangle_positions[gl_VertexIndex], 0.0, 1.0);
}