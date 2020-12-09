#version 330 core

layout (location = 0) in vec2 vPos;
layout (location = 1) in vec3 vCol;

out vec3 fCol;

void main() {
	fCol = vCol;
	gl_Position = vec4(vPos, 0.0f, 1.0f);
}
