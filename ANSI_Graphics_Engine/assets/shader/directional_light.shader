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

uniform float u_specularIntensity;
uniform float u_specularPower;
uniform vec3 u_color;
uniform vec3 u_lightDirection;
uniform vec3 u_cameraDirection;

void main()
{
	float directionalLightDiffuse = max(dot(o_worldNormal, -u_lightDirection), 0.0);

	vec3 halfWay = -normalize(u_lightDirection + u_cameraDirection);
	float directionalLightSpecular = pow(max(dot(halfWay, o_worldNormal), 0.0), u_specularPower) * u_specularIntensity;
	vec3 directionalLightColor = u_color * (directionalLightDiffuse + directionalLightSpecular);

	FragColor = vec4(directionalLightColor, 1.0);
}
