#type vertex
#version 460 core

layout(location = 0) in vec3 attribute_position;
layout(location = 1) in vec2 attribute_texture;

uniform mat4 uniform_view_projection;
uniform mat4 uniform_transform;

out vec2 output_texture;

void main()
{
    output_texture = attribute_texture;
    gl_Position = uniform_view_projection * uniform_transform * vec4(attribute_position, 1.0);
}

#type fragment
#version 460 core

layout(location = 0) out vec4 color;

in vec2 output_texture;

uniform sampler2D uniform_texture;

void main()
{
    color = texture(uniform_texture, output_texture);
}