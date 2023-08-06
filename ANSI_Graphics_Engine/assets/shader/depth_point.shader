# shader_vertex
# version 460 core

layout(location = 0) in vec3 position;

uniform mat4 u_worldMatrix;

void main()
{
	gl_Position = u_worldMatrix * vec4(position, 1.0);
}


# shader_geometry
# version 460 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 18) out;

out vec3 o_worldPosition;

uniform mat4 u_lightVPs[6];

void main()
{
	for (uint face = 0; face < 6; ++face)
	{
		gl_Layer = int(face);

		for (uint i = 0; i < 3; ++i)
		{
			gl_Position = u_lightVPs[face] * gl_in[i].gl_Position;

			o_worldPosition = gl_in[i].gl_Position.xyz;

			EmitVertex();
		}

		EndPrimitive();
	}
}


# shader_fragment
# version 460 core

in vec3 o_worldPosition;

uniform float u_radius;
uniform vec3 u_lightPosition;

void main()
{
	gl_FragDepth = length(u_lightPosition - o_worldPosition) / u_radius;
}
