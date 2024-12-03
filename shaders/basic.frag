#version 330 core

in vec2 UV;
in vec3 positionWorld;
in vec3 cameraDirectionCamera;

in vec3 cameraDirectionTangent;

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define POINT_LIGHTS 4
uniform PointLight pointLights[POINT_LIGHTS];

//struct SpotLight {
//	vec3 position;
//	vec3 direction;
//
//	vec3 ambient;
//	vec3 diffuse;
//	vec3 specular;
//};
////maybe turn this into uniform
//#define SPOT_LIGHTS 4;
//uniform SpotLight spotLights[SPOT_LIGHTS];

uniform sampler2D colorTexture;
uniform sampler2D normalTexture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// struct SpotLight
struct Light {
	vec3 pos;
	float power;
    vec3 directionCamera;
    vec3 directionTangent;
};
#define MAX_LIGHTS 5
uniform int numLights;
in Light lights[MAX_LIGHTS];
uniform vec3 lightPos[MAX_LIGHTS];
uniform float lightPower;


	vec4 normalTangent = normalize(texture(normalTexture, vec2(UV.x,-UV.y) )*2.0 - 1.0);
	vec4 normalizeCameraTanget = normalize(vec4(cameraDirectionTangent, 1.0f));

vec4 calculateLight(Light light) {
	vec4 color = vec4(1,1,1,1);
	float ambientStrength = 0.0;

	vec4 matColor = texture(colorTexture, UV);
	vec4 ambient = vec4(ambientStrength, ambientStrength, ambientStrength, 1.0f) * matColor;

	float distToLight = length(light.pos - positionWorld);

	vec4 n = normalTangent;

	//direction of light
	vec4 l = normalize(vec4(light.directionTangent, 1.0f));

	float cosTheta = clamp(dot(n, l), 0, 1);

	vec4 R = reflect(-l, n);

	// float cosAlpha = 1/clamp(dot(normalizeCameraTanget, R), 0, 1);

	return 
		ambient +
		matColor * color * light.power * cosTheta / (distToLight*distToLight);
}

void main()
{
	mat4 mvp = projection * view * model;
	mat3 mv3x3 = mat3(view * model);   
	//color is white

	// color = texture(texture1, TexCoords);
	vec4 finalColor = calculateLight(lights[0]);
	for(int i =1; i< numLights; i++){
		finalColor += calculateLight(lights[i]);
	}
	gl_FragColor = finalColor;
}
