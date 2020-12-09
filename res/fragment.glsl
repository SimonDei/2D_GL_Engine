#version 330 core

in vec3 fCol;

out vec4 fragColor;

void main() {
	fragColor = vec4(fCol, 1.0f);
}
