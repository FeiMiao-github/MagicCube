#version 330 core

layout (location = 0) in vec3 ug_Pos;
layout (location = 1) in vec3 ug_Col;

uniform mat4 ug_magiccube_Model;
uniform mat4 ug_Model;
uniform mat4 ug_View;
uniform mat4 ug_Proj;

out vec3 ug_Out_Col;

float normalize(float value, float start, float end)
{
    return (value - start) / (end - start);
}

vec3 normalize(vec3 value, vec3 start, vec3 end)
{
    return (value - start) / (end - start);
}

vec3 normalize(vec3 value)
{
    return (value + 1) / 2;
}

void main(void)
{
    gl_Position = ug_Proj * ug_View * ug_magiccube_Model * ug_Model * vec4(ug_Pos.xyz, 1);
    ug_Out_Col = ug_Col;    
}
