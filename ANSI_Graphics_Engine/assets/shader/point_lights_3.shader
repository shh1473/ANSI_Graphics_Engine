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

/* Camera */
uniform vec3 u_cameraPosition;

/* Lights */
uniform float u_lightRadiusRcp[MAX_POINT_LIGHTS];
uniform vec3 u_lightColors[MAX_POINT_LIGHTS];
uniform vec3 u_lightPositions[MAX_POINT_LIGHTS];

/* Material */
uniform float u_specularIntensity;
uniform float u_specularPower;
uniform vec4 u_diffuseColor;

void main()
{
	float distanceToLights;
	float attenuation;
	float diffuse;
	float specular;
	vec3 dirToLights;
	vec3 dirToCamera = normalize(u_cameraPosition - o_worldPosition);
	vec3 halfWay;
	vec3 totalLight;

	for (uint i = 0; i < MAX_POINT_LIGHTS; ++i) {
		dirToLights = normalize(u_lightPositions[i] - o_worldPosition);
		distanceToLights = length(u_lightPositions[i] - o_worldPosition);
		attenuation = 1.0 - min(distanceToLights * u_lightRadiusRcp[i], 1.0);
		diffuse = max(dot(o_worldNormal, dirToLights), 0.0);

		halfWay = normalize(dirToLights + dirToCamera);
		specular = pow(max(dot(halfWay, o_worldNormal), 0.0), u_specularPower) * u_specularIntensity;

		totalLight += u_lightColors[i] * (diffuse + specular) * (attenuation * attenuation);
	}

	FragColor = vec4(u_diffuseColor.rgb * totalLight, u_diffuseColor.a);
}
