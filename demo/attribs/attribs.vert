#version 450

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

layout(location = 0) out vec4 fs_color;

out gl_PerVertex {
	vec4 gl_Position;
};

void main() {
	fs_color = color;
	gl_Position = position;
}