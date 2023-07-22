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

#define MAX_POINT_LIGHTS 3

layout(location = 0) out vec4 FragColor;

in vec3 o_worldPosition;
in vec3 o_worldNormal;

uniform float u_specularIntensities[MAX_POINT_LIGHTS];
uniform float u_specularPowers[MAX_POINT_LIGHTS];
uniform float u_radiusRcp[MAX_POINT_LIGHTS];
uniform vec3 u_colors[MAX_POINT_LIGHTS];
uniform vec3 u_positions[MAX_POINT_LIGHTS];
uniform vec3 u_cameraPosition;

void main()
{
	float distanceToLights[MAX_POINT_LIGHTS];
	float attenuation[MAX_POINT_LIGHTS];
	float diffuse[MAX_POINT_LIGHTS];
	float specular[MAX_POINT_LIGHTS];
	vec3 dirToLights[MAX_POINT_LIGHTS];
	vec3 dirToCamera = normalize(u_cameraPosition - o_worldPosition);
	vec3 halfWay = vec3(0.0, 0.0, 0.0);
	vec3 totalColor = vec3(0.0, 0.0, 0.0);

	for (uint i = 0; i < MAX_POINT_LIGHTS; ++i) {
		dirToLights[i] = normalize(u_positions[i] - o_worldPosition);
		distanceToLights[i] = length(u_positions[i] - o_worldPosition);
		attenuation[i] = 1.0 - min(distanceToLights[i] * u_radiusRcp[i], 1.0);
		diffuse[i] = max(dot(o_worldNormal, dirToLights[i]), 0.0);

		halfWay = normalize(dirToLights[i] + dirToCamera);
		specular[i] = pow(max(dot(halfWay, o_worldNormal), 0.0), u_specularPowers[i]) * u_specularIntensities[i];

		totalColor += u_colors[i] * (diffuse[i] + specular[i]) * (attenuation[i] * attenuation[i]);
	}

	FragColor = vec4(totalColor, 1.0);
}
