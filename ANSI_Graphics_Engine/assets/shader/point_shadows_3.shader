# shader_vertex
# version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

/* Output */
out vec3 o_worldPosition;
out vec3 o_worldNormal;

/* Object */
uniform mat4 u_MVP;
uniform mat4 u_worldMatrix;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);

	o_worldPosition = (u_worldMatrix * vec4(position, 1.0)).xyz;
	o_worldNormal = normalize(mat3(u_worldMatrix) * normalize(normal));
}


# shader_fragment
# version 460 core

#define LIGHT_COUNT 3

layout(location = 0) out vec4 FragColor;

/* Output */
in vec3 o_worldPosition;
in vec3 o_worldNormal;

/* Camera */
uniform vec3 u_cameraPosition;

/* Light */
uniform float u_lightCameraFars[LIGHT_COUNT];
uniform float u_lightRadiusRcps[LIGHT_COUNT];
uniform vec3 u_lightColors[LIGHT_COUNT];
uniform vec3 u_lightPositions[LIGHT_COUNT];

/* Material */
uniform float u_specularIntensity;
uniform float u_specularPower;
uniform vec4 u_diffuseColor;

/* Texture */
uniform samplerCube u_shadowMaps[3];

void main()
{
	float distanceToLight;
	float sphereAtt;
	float diffuse;
	float specular;
	float shadowMapDepth;
	float shadow;
	float depthBias;
	vec3 dirToLight;
	vec3 dirToCamera = normalize(u_cameraPosition - o_worldPosition);
	vec3 halfWay;
	vec3 totalLight;

	for (uint i = 0; i < LIGHT_COUNT; ++i)
	{
		distanceToLight = length(u_lightPositions[i] - o_worldPosition);
		dirToLight = (u_lightPositions[i] - o_worldPosition) / distanceToLight;

		/* Diffuse */
		diffuse = max(dot(o_worldNormal, dirToLight), 0.0);

		/* Specular */
		halfWay = normalize(dirToLight + dirToCamera);
		specular = pow(max(dot(halfWay, o_worldNormal), 0.0), u_specularPower) * u_specularIntensity;

		/* Sphere Attenuation */
		sphereAtt = 1.0 - min(distanceToLight * u_lightRadiusRcps[i], 1.0);

		/* Shadow */
		depthBias = tan(acos(diffuse)) * 0.005;
		depthBias = clamp(depthBias, 0.0, 0.001);
		shadowMapDepth = texture(u_shadowMaps[i], -dirToLight).x + depthBias;
		distanceToLight *= u_lightRadiusRcps[i];
		distanceToLight += 0.005;

		shadow = (distanceToLight > shadowMapDepth) ? 0.5 : 1.0;

		/* Combine */
		totalLight += u_lightColors[i] * (diffuse + specular) * (sphereAtt * sphereAtt) * shadow;
	}

	FragColor = vec4(u_diffuseColor.rgb * totalLight, u_diffuseColor.a);
}
