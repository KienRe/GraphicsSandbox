#shader vertex
#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 in_color;

out vec4 v_color;

uniform mat4 u_MVPMatrix;

void main()
{
	gl_Position = u_MVPMatrix * position;
	v_color = vec4(in_color, 1.0f);
};

#shader fragment
#version 430 core

layout(location = 0) out vec4 out_color;
in vec4 v_color;

void main()
{
	out_color = v_color;
};