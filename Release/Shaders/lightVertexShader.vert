uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;

attribute vec3 in_Position;
attribute vec2 a_texCoords;
attribute vec3 a_normal;

varying vec2 v_texCoords;
varying vec3 v_normal;
varying vec3 v_fragPos;

void main()
{
	v_fragPos = vec3(u_model * vec4(in_Position, 1.0));
	gl_Position = u_projection * u_view * u_model * vec4(in_Position, 1.0);
	v_texCoords = a_texCoords;
	v_normal = vec3(u_model * vec4(a_normal, 0));
}