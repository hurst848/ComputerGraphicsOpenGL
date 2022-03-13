uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;

attribute vec3 in_Position;
attribute vec2 a_texCoords;

varying vec2 v_texCoords;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(in_Position, 1.0);
	v_texCoords = a_texCoords;
}