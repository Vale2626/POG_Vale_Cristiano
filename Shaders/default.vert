
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTex;

out vec3 vColor;
out vec2 vTex;
out vec3 vFragPos;     // in world space
out vec3 vNormal;      // in world space

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main() {
    vColor = aColor;
    vTex   = aTex;

    vec4 worldPos = Model * vec4(aPos, 1.0);
    vFragPos = worldPos.xyz;

    mat3 normalMatrix = mat3(transpose(inverse(Model)));
    vNormal = normalize(normalMatrix * aNormal);

    gl_Position = Projection * View * worldPos;
}