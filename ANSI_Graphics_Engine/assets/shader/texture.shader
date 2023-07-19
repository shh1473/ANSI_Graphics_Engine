# shader-vertex

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 o_texCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	o_texCoord = texCoord;
}


# shader-fragment

layout(location = 0) out vec4 FragColor;

in vec2 o_texCoord;

uniform sampler2D u_diffuseMap;

void main()
{
	FragColor = texture(u_diffuseMap, o_texCoord);
}
