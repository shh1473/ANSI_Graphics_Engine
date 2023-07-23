# shader_vertex
# version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

out vec3 o_worldPosition;
out vec3 o_worldNormal;

uniform mat4 u_MVP;
uniform mat4 u_worldMatrix;

void main()
{
	gl_Position = u_MVP * position;
	o_worldPosition = (u_worldMatrix * position).xyz;
	o_worldNormal = normalize(mat3(u_worldMatrix) * normalize(normal));
}


# shader_fragment
# version 460 core

layout(location = 0) out vec4 FragColor;

in vec3 o_worldPosition;
in vec3 o_worldNormal;

uniform float u_specularIntensity;
uniform float u_specularPower;
uniform vec3 u_lightColor;
uniform vec3 u_lightDirection;
uniform vec3 u_cameraPosition;

void main()
{
	float diffuse = max(dot(o_worldNormal, -u_lightDirection), 0.0);

	vec3 dirToCamera = normalize(u_cameraPosition - o_worldPosition);
	vec3 halfWay = normalize(dirToCamera - u_lightDirection);
	float specular = pow(max(dot(halfWay, o_worldNormal), 0.0), u_specularPower) * u_specularIntensity;
	vec3 color = u_lightColor * (diffuse + specular);

	FragColor = vec4(color, 1.0);
}
