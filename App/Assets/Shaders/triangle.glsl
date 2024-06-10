@vs vs
in vec4 position;
in vec4 colour0;

out vec4 colour;

void main()
{
	gl_Position = position;
	colour = colour0;
}
@end

@fs fs
in vec4 colour;
out vec4 fragColour;

void main()
{
	fragColour = colour;
}
@end

@program triangle vs fs