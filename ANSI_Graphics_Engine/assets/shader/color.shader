# shader_vertex

layout(location = 0) in vec4 position;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
}


# shader_fragment

layout(location = 0) out vec4 FragColor;

uniform vec4 u_color;

void main()
{
	FragColor = u_color;
}
