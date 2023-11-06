#version 330 core

in vec3 ug_Out_Col;

void main(void)
{
    gl_FragColor = vec4(ug_Out_Col, 1);
}
