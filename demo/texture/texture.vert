#version 450

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 tex;

layout(location = 0) out vec2 fs_tex;

out gl_PerVertex {
	vec4 gl_Position;
};

void main() {
	fs_tex = tex;
	vec4 pos = position;
	gl_Position = pos;
}