#shader vertex
#version 330 core 

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform vec4 offset;
uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec4 bColor;
out vec4 bPosition;
out vec2 bTexCoord;

void main() 
{ 
    gl_Position = projection * view * model * vec4(position, 1.0f);
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
	fragColor = texture(texture2, bTexCoord);
	//fragColor = mix(texture(texture1, bTexCoord), texture(texture2, bTexCoord), 0.9);
};