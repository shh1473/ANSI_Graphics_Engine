# shader_vertex
# version 460 core

layout(location = 0) in vec4 position;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
}


# shader_fragment
# version 460 core

layout(location = 0) out vec4 FragColor;

uniform vec4 u_diffuseColor;

void main()
{
	FragColor = u_diffuseColor;
}
