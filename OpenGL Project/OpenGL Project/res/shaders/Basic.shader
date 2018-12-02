#shader vertex
#version 330 core 

layout (location = 0) in vec4 position;
layout(location = 1) in vec4 aColor;

uniform vec4 offset;
out vec4 bColor;
out vec4 bPosition;

void main() 
{ 
    gl_Position = position + offset;
	bColor = aColor;
	bPosition = gl_Position;
};

#shader fragment
#version 410 core

out vec4 fragColor;
in vec4 bColor;
in vec4 bPosition;

uniform vec4 u_Color;

void main() 
{ 
	fragColor = vec4(bColor + bPosition);
};