uniform sampler2D u_texture;

uniform vec3 u_lightColour;
uniform float u_ambientStrength;

varying vec2 v_texCoords;

void main()
{
	vec3 ambient = u_ambientStrength * u_lightColour;
	vec4 tex = texture2D(u_texture, v_texCoords);
	gl_FragColor = vec4(ambient, 1.0) * tex;
}