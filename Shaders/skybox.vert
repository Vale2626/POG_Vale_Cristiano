#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 View;
uniform mat4 Projection;

void main()
{
    // centra il cubo (0..1) in [-0.5..0.5] e usa solo la rotazione della view
    vec3 centered = aPos * 2.0 - 1.0; // da [0,1] a [-1,1]
    mat4 rotView = mat4(mat3(View));  // rimuove la traslazione

    TexCoords = centered;
    vec4 clipPos = Projection * rotView * vec4(centered, 1.0);
    gl_Position = vec4(clipPos.xy, clipPos.w, clipPos.w); // z impostato a 1.0 per tenerla sempre in fondo, in modo che se mi muovo non si mescolano la skybox con il modello 3D
}
