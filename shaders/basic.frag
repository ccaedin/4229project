#version 330 core

in vec2 UV;
in vec3 positionWorld;
in vec3 cameraDirectionCamera;

in vec3 cameraDirectionTangent;

uniform sampler2D colorTexture;
uniform sampler2D normalTexture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
struct Light {
	vec3 pos;
	float power;
    vec4 color;

	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct FlashLight {
    Light light;
    vec3 dir;
    float cutOff;
    float outerCutOff;
	
    // float constant;
    // float linear;
    // float quadratic;
};
uniform FlashLight flashLight;
in vec3 flashlightDirectionTangent;
#define MAX_LIGHTS 21 //for some reason it errors out if I use > 12 

in mat3 TBN;

uniform bool flashLightEnabled;
uniform int numLights;
uniform Light lights[MAX_LIGHTS];

in vec3 lightDirectionTangent[MAX_LIGHTS];

vec4 normalTangent = normalize(texture(normalTexture, vec2(UV.x,UV.y) )*2.0 - 1.0);
vec4 normalizeCameraTanget = normalize(vec4(cameraDirectionTangent, 1.0f));


vec4 calculateLight(int index) {


	Light light = lights[index];
	vec4 color = light.color;
	float ambientStrength = 0.00;

	vec4 matColor = texture(colorTexture, UV);
	vec4 ambient = vec4(ambientStrength, ambientStrength, ambientStrength, 1.0f) * matColor;

	float distToLight = length(light.pos - positionWorld);

	vec4 n = normalTangent;

	//direction of light
	vec4 l = normalize(vec4(lightDirectionTangent[index], 1.0f));

	//test if 0 return white
	float cosTheta = clamp(dot(n, l), 0, 1);
	vec4 R = reflect(-l, n);

	// float cosAlpha = 1/clamp(dot(normalizeCameraTanget, R), 0, 1);
	// if(distToLight > 0.0f && cosTheta > 0.0f){
	// 	return vec4(1.0f, 1.0f, 1.0f, 1.0f);
	// }
	return 
		ambient +
		matColor * color * light.power * cosTheta / (distToLight*distToLight);
}

vec4 calculateFlashLight() {
	vec3 lightDir = normalize(flashLight.light.pos - positionWorld);
	float theta = dot(lightDir, normalize(-flashLight.dir));
	float ambientStrength = 0.5;

	vec4 matColor = texture(colorTexture, UV);
	vec4 ambient = vec4(ambientStrength, ambientStrength, ambientStrength, 1.0f) * matColor;
	if(theta > flashLight.cutOff){
		//inside of flash
		Light light = flashLight.light;
		vec4 color = light.color;


		float distToLight = length(light.pos - positionWorld);

		vec4 n = normalTangent;

		//direction of light
		vec4 l = normalize(vec4(flashlightDirectionTangent, 1.0f));

		//test if 0 return white
		float cosTheta = clamp(dot(n, l), 0, 1);
		vec4 R = reflect(-l, n);

		// float cosAlpha = 1/clamp(dot(normalizeCameraTanget, R), 0, 1);
		// if(distToLight > 0.0f && cosTheta > 0.0f){
		// 	return vec4(1.0f, 1.0f, 1.0f, 1.0f);
		// }
		return 
			ambient +
			matColor * color * light.power * cosTheta / (distToLight*distToLight);
		}
	else
	{
		//outside of flash so use light from other 
		return vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

}

void main()
{
	mat4 mvp = projection * view * model;
	mat3 mv3x3 = mat3(view * model);   
	//color is white

	// color = texture(texture1, TexCoords);
	vec4 finalColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	for(int i =0; i< numLights; i++){
		finalColor += calculateLight(i);
	}
	if(flashLightEnabled)
		finalColor += calculateFlashLight();
	gl_FragColor = finalColor;
}