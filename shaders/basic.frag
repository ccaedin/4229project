#version 330 core

in vec2 UV;
in vec3 positionWorld;
in vec3 cameraDirectionCamera;
in vec3 lightDirectionCamera;

in vec3 lightDirectionTangent;
in vec3 cameraDirectionTangent;

uniform sampler2D colorTexture;
uniform sampler2D normalTexture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;
uniform float lightPower;

void main()
{

	vec4 LightColor = vec4(1,1,1,1);
	float LightPower = lightPower;
	float ambientStrength = 0.5f;

	mat4 mvp = projection * view * model;
	mat3 mv3x3 = mat3(view * model);   
	//color is white

	// color = texture(texture1, TexCoords);
	vec4 materialColor = texture(colorTexture, UV);
	vec4 ambient = vec4(ambientStrength, ambientStrength, ambientStrength, 1.0f) * materialColor;

	vec4 normalTangent = normalize(texture(normalTexture, vec2(UV.x,-UV.y) )*2.0 - 1.0);

	float distanceToLight = length(lightPos - positionWorld);

	vec4 n = normalTangent;

	//direction of light
	vec4 l = normalize(vec4(lightDirectionTangent, 1.0f));

	float cosTheta = clamp(dot(n, l), 0, 1);

	vec4 E = normalize(vec4(cameraDirectionTangent, 1.0f));
	vec4 R = reflect(-l, n);

	float cosAlpha = clamp(dot(E, R), 0, 1);

	gl_FragColor =

		ambient +

		materialColor * LightColor * LightPower * cosTheta / (distanceToLight*distanceToLight);


	// gl_FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
