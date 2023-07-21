# shader_vertex

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

out vec3 o_worldNormal;

uniform mat4 u_MVP;
uniform mat4 u_worldMatrix;

void main()
{
	gl_Position = u_MVP * position;
	o_worldNormal = normalize(mat3(u_worldMatrix) * normal);
}


# shader_fragment

layout(location = 0) out vec4 FragColor;

in vec3 o_worldNormal;

uniform vec3 u_downColor;
uniform vec3 u_colorRange;

void main()
{
	float upNormal = (o_worldNormal.y * 0.5) + 0.5;
	vec3 ambientLightColor = u_downColor + (upNormal * u_colorRange);

	FragColor = vec4(ambientLightColor, 1.0);
}
