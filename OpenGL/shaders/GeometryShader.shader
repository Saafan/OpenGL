#shader vertex
#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 normals;

void main()
{
	gl_Position = proj * view * model * vec4(vPosition, 1.0);
	normals = aNormal;
}


#shader geometry
#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

float length = 0.035f;
float width = 0.035f;
float height = 0.035f;

float vertices[] = {
	// positions		 Normals       Texture Coords
	-0.5f * length, -0.5f * width, -0.5f * height, 1.0f,
	 0.5f * length, -0.5f * width, -0.5f * height, 1.0f,
	 0.5f * length,  0.5f * width, -0.5f * height, 1.0f,
	 0.5f * length,  0.5f * width, -0.5f * height, 1.0f,
	-0.5f * length,  0.5f * width, -0.5f * height, 1.0f,
	-0.5f * length, -0.5f * width, -0.5f * height, 1.0f,

	-0.5f * length, -0.5f * width,  0.5f * height, 1.0f,
	 0.5f * length, -0.5f * width,  0.5f * height, 1.0f,
	 0.5f * length,  0.5f * width,  0.5f * height, 1.0f,
	 0.5f * length,  0.5f * width,  0.5f * height, 1.0f,
	-0.5f * length,  0.5f * width,  0.5f * height, 1.0f,
	-0.5f * length, -0.5f * width,  0.5f * height, 1.0f,

	-0.5f * length,  0.5f * width,  0.5f * height, 1.0f,
	-0.5f * length,  0.5f * width, -0.5f * height, 1.0f,
	-0.5f * length, -0.5f * width, -0.5f * height, 1.0f,
	-0.5f * length, -0.5f * width, -0.5f * height, 1.0f,
	-0.5f * length, -0.5f * width,  0.5f * height, 1.0f,
	-0.5f * length,  0.5f * width,  0.5f * height, 1.0f,

	 0.5f * length,  0.5f * width,  0.5f * height, 1.0f,
	 0.5f * length,  0.5f * width, -0.5f * height, 1.0f,
	 0.5f * length, -0.5f * width, -0.5f * height, 1.0f,
	 0.5f * length, -0.5f * width, -0.5f * height, 1.0f,
	 0.5f * length, -0.5f * width,  0.5f * height, 1.0f,
	 0.5f * length,  0.5f * width,  0.5f * height, 1.0f,

	-0.5f * length, -0.5f * width, -0.5f * height, 1.0f,
	 0.5f * length, -0.5f * width, -0.5f * height, 1.0f,
	 0.5f * length, -0.5f * width,  0.5f * height, 1.0f,
	 0.5f * length, -0.5f * width,  0.5f * height, 1.0f,
	-0.5f * length, -0.5f * width,  0.5f * height, 1.0f,
	-0.5f * length, -0.5f * width, -0.5f * height, 1.0f,

	-0.5f * length,  0.5f * width, -0.5f * height, 1.0f,
	 0.5f * length,  0.5f * width, -0.5f * height, 1.0f,
	 0.5f * length,  0.5f * width,  0.5f * height, 1.0f,
	 0.5f * length,  0.5f * width,  0.5f * height, 1.0f,
	-0.5f * length,  0.5f * width,  0.5f * height, 1.0f,
	-0.5f * length,  0.5f * width, -0.5f * height, 1.0f,
};

in vec4 normals;

vec4 TriangleDistance(vec4 position, vec4 normal)
{
	return position + normal;
}

void main()
{
	gl_Position = TriangleDistance(gl_in[0].gl_Position, normals);
	EmitVertex();
	
	gl_Position = TriangleDistance(gl_in[1].gl_Position, normals);
	EmitVertex();

	gl_Position = TriangleDistance(gl_in[2].gl_Position, normals);
	EmitVertex();

	EndPrimitive();
}

#shader fragment
#version 330 core

out vec4 color;

void main()
{
	color = vec4(0.0f, 0.0f, 0.7f, 1.0f);
}