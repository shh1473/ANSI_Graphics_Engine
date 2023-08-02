# shader_vertex
# version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

/* Light */
out vec4 o_lightClipPositions[3];

/* Object */
out vec3 o_worldPosition;
out vec3 o_worldNormal;

/* Light */
uniform mat4 u_lightMVPs[3];

/* Object */
uniform mat4 u_MVP;
uniform mat4 u_worldMatrix;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);

	for (uint i = 0; i < 3; ++i) { o_lightClipPositions[i] = u_lightMVPs[i] * vec4(position, 1.0); }

	o_worldPosition = (u_worldMatrix * vec4(position, 1.0)).xyz;
	o_worldNormal = normalize(mat3(u_worldMatrix) * normalize(normal));
}


# shader_fragment
# version 460 core

#define LIGHT_COUNT 3

layout(location = 0) out vec4 FragColor;

/* Light */
smooth in vec4 o_lightClipPositions[3];

/* Object */
in vec3 o_worldPosition;
in vec3 o_worldNormal;

/* Camera */
uniform vec3 u_cameraPosition;

/* Light */
uniform float u_lightRadiusRcps[LIGHT_COUNT];
uniform float u_lightSmoothRangeRcps[LIGHT_COUNT];
uniform float u_lightCosAngles[LIGHT_COUNT];
uniform vec3 u_lightColors[LIGHT_COUNT];
uniform vec3 u_lightDirections[LIGHT_COUNT];
uniform vec3 u_lightPositions[LIGHT_COUNT];

/* Material */
uniform float u_specularIntensity;
uniform float u_specularPower;
uniform vec4 u_diffuseColor;

/* Texture */
uniform sampler2D u_shadowMaps[3];

void main()
{
	float distanceToLight;
	float cosAngle;
	float sphereAtt;
	float coneAtt;
	float diffuse;
	float specular;
	float shadowMapDepth;
	float shadow;
	float depthBias;
	vec3 lightPosition;
	vec3 dirToLight;
	vec3 dirToCamera = normalize(u_cameraPosition - o_worldPosition);
	vec3 halfWay;
	vec3 totalLight;

	for (uint i = 0; i < LIGHT_COUNT; ++i)
	{
		dirToLight = normalize(u_lightPositions[i] - o_worldPosition);
		distanceToLight = length(u_lightPositions[i] - o_worldPosition);

		/* Diffuse */
		diffuse = max(dot(o_worldNormal, dirToLight), 0.0);

		/* Specular */
		halfWay = normalize(dirToLight + dirToCamera);
		specular = pow(max(dot(halfWay, o_worldNormal), 0.0), u_specularPower) * u_specularIntensity;

		/* Sphere Attenuation */
		sphereAtt = 1.0 - min(distanceToLight * u_lightRadiusRcps[i], 1.0);

		/* Cone Attenuation */
		cosAngle = max(dot(-u_lightDirections[i], dirToLight), 0.0);
		coneAtt = (cosAngle - u_lightCosAngles[i]) / (1.0 - u_lightCosAngles[i]);
		coneAtt = clamp(coneAtt * u_lightSmoothRangeRcps[i], 0.0, 1.0);

		/* Shadow */
		lightPosition = o_lightClipPositions[i].xyz / o_lightClipPositions[i].w;
		shadowMapDepth = texture(u_shadowMaps[i], lightPosition.xy * 0.5 + 0.5).x;

		depthBias = tan(acos(diffuse)) * 0.005;
		depthBias = clamp(depthBias, 0, 0.001);
		shadow = (lightPosition.z > shadowMapDepth + depthBias) ? 0.5 : 1.0;

		/* Combine */
		totalLight += u_lightColors[i] * (diffuse + specular) * (sphereAtt * sphereAtt) * (coneAtt * coneAtt) * shadow;
	}

	

	FragColor = vec4(u_diffuseColor.rgb * totalLight, u_diffuseColor.a);
}
