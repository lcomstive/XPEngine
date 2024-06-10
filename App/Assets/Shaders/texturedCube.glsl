@module TexturedCube

@ctype mat4 glm::mat4

@vs vs
uniform vs_params
{
	mat4 mvp;
};

in vec3 inPosition;
in vec2 inTexCoords;

out vec2 texCoords;

void main()
{
	gl_Position = mvp * vec4(inPosition, 1);
	texCoords = inTexCoords;
}
@end

@fs fs
in vec2 texCoords;
out vec4 fragColour;

uniform sampler smp;
uniform texture2D tex;

void main()
{
	fragColour = texture(sampler2D(tex, smp), texCoords);
}
@end

@program program vs fs