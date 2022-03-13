uniform sampler2D u_texture;

uniform vec3 u_lightColour;
uniform float u_ambientStrength;
uniform vec3 u_lightPos;

varying vec2 v_texCoords;
varying vec3 v_normal;
varying vec3 v_fragPos;

void main()
{
	vec3 norm = normalize(v_normal);
	vec3 lightDir = normalize(u_lightPos - v_fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_lightColour;
	vec3 ambient = u_ambientStrength * u_lightColour;
	vec3 light = ambient + diffuse;
	vec4 tex = texture2D(u_texture, v_texCoords);
	gl_FragColor = vec4(light, 1.0) * tex;
}