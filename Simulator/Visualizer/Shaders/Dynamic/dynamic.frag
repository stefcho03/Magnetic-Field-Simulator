#version 330 core

uniform vec3 u_fieldStrength;
out vec4 FragColor;

void main() {
    FragColor = vec4(u_fieldStrength, 1.0); 
}
