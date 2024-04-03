#version 450

layout(location = 0) in vec2 inPosition;

layout(push_constant) uniform Push 
{
  vec2 Offset;
  vec3 Color;
} push;

void main() 
{
  gl_Position = vec4(inPosition + push.Offset, 0.0, 1.0);
}