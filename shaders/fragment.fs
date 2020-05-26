#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D tex;
uniform sampler2D tex2;

void main()
{
	FragColor = mix(texture(tex, TexCoord), texture(tex2, TexCoord), 0.2);
	//FragColor = vec4(0.5, 0.5, 0.5, 1.0);
};