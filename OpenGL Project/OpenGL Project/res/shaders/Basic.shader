#shader vertex
#version 330 core 

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform vec4 offset;
out vec4 bColor;
out vec4 bPosition;
out vec2 bTexCoord;

void main() 
{ 
    gl_Position = position + offset;
	bColor = aColor;
	bPosition = gl_Position;
	bTexCoord = aTexCoord;
};

#shader fragment
#version 410 core

out vec4 fragColor;
in vec4 bColor;
in vec4 bPosition;
in vec2 bTexCoord;

uniform vec4 u_Color;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() 
{ 
	//fragColor = vec4(bColor + bPosition);
	fragColor = texture(texture1, bTexCoord) * vec4(bColor);
	//fragColor = mix(texture(texture1, bTexCoord), texture(texture2, bTexCoord), 0.2);
};