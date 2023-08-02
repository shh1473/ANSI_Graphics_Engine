# shader_vertex
# version 460 core

layout(location = 0) in vec3 position;

out float o_depth;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);
	o_depth = gl_Position.z / gl_Position.w;
}


# shader_fragment
# version 460 core

in float o_depth;

void main() { gl_FragDepth = o_depth; }
