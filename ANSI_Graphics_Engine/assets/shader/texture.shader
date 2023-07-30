# shader_vertex
# version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 o_texCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	o_texCoord = texCoord;
}


# shader_fragment
# version 460 core

layout(location = 0) out vec4 FragColor;

in vec2 o_texCoord;

uniform sampler2D u_diffuseMap;
uniform vec4 u_diffuseColor;

void main()
{
	FragColor = u_diffuseColor * texture(u_diffuseMap, o_texCoord);
}
