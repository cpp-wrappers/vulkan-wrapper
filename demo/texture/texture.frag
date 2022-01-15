#version 450

layout(location = 0) in vec2 fs_tex;
layout(location = 0) out vec4 out_color;

layout(set = 0, binding = 0) uniform sampler2D u_tex;

void main() {
	out_color = texture(u_tex, fs_tex);
}