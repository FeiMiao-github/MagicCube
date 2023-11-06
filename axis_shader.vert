#version 330 core

layout (location = 0) in vec3 ug_Pos;

uniform mat4 ug_Model;
uniform mat4 ug_View;
uniform mat4 ug_Proj;

void main(void)
{
    // gl_Position = ug_Proj * ug_View * ug_Model * vec4(ug_Pos.xyz, 1);
    gl_Position = ug_Proj * ug_View * ug_Model * vec4(ug_Pos.xyz, 1);
}
