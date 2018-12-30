#versione core 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoords;

uniform mat4 model;
unform mat4 view;
uniform mat4 projection;

out vec3 TexCoords;

void main()
{
	TexCoords = texCoords;

	gl_Position = projection * view * model * vec4(pos,1.0f);
}