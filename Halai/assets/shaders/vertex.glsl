#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_Transform;

out vec3 v_Position;
out vec4 v_Color;

void main()
{
	v_Position = a_Position;
	v_Color = vec4(a_TexCoord.x, a_TexCoord.y, 0.0, 0.0);
	gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
}