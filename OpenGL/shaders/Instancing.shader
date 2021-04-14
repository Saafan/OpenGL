#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


void main()
{
	gl_Position = model * vec4(aPos, 1.0f);
}


#shader fragment
#version 330 core

out vec4 fragColor;


void main()
{
	fragColor = vec4(gl_FragCoord.x, gl_FragCoord.y, 1.0f, 1.0);
}