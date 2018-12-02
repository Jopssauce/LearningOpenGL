#shader vertex
#version 330 core 

layout (location = 0) in vec4 position;
layout(location = 1) in vec4 aColor;

out vec4 bColor;

void main() 
{ 
    gl_Position = position;
	bColor = aColor;
};

#shader fragment
#version 410 core

out vec4 fragColor;
in vec4 bColor;

uniform vec4 u_Color;

void main() 
{ 
	fragColor = vec4(bColor);
};