// A simple color shader
#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec4 vColor;
in vec2 vTexCoord;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float specularPower;

uniform vec3 Ga;
uniform vec3 Gd;
uniform vec3 Gs;
uniform vec3 LightDirection;

uniform vec3 CameraPosition;

uniform sampler2D diffuseTexture;

vec4 LightColor;
vec4 TextureColor;

out vec4 FragColor;

void main()
{
	//Ensure normal and light direction are normalized
	vec3 N = normalize(vNormal);
	vec3 L = normalize(LightDirection);

	//Calculate lambert term (negate light direction)
	float lambertTerm = max(0, min(1, dot(N, -L)));

	//Calculate view vector and reflection vector
	vec3 V = normalize(CameraPosition - vPosition.xyz);
	vec3 R = reflect(L, N);

	//Calculate the specular term
	float specularTerm = pow(max(0, dot(R, V)), specularPower);

	//Output  the color
	vec3 ambient = (Ka + vColor.rgb) * Ga;
	vec3 diffuse = (Kd + vColor.rgb) * Gd * lambertTerm;
	vec3 specular = (Ks + vColor.rgb) * Gs * specularTerm;
	LightColor = vec4(ambient + diffuse + specular, 1.0f);

	//Add the texture and color
	TextureColor = texture(diffuseTexture, vTexCoord) + vColor;

	FragColor = (LightColor / 2) + (TextureColor / 3);
}