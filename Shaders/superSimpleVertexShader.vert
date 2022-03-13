uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;

attribute vec3 in_Position;
           
void main()
{
  gl_Position = u_projection * u_view * u_model * vec4(in_Position, 1.0);
}