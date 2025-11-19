#type vertex
#version 460 core

layout(location = 0) in vec3 attribute_position;

uniform mat4 uniform_view_projection;
uniform mat4 uniform_transform;

out vec2 output_texture;

void main()
{
    gl_Position = uniform_view_projection * uniform_transform * vec4(attribute_position, 1.0);
}

#type fragment
#version 460 core

layout(location = 0) out vec4 color;

uniform vec4 uniform_color;

void main()
{
    color = uniform_color;
}