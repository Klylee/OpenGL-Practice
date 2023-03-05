#shader vertex
#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texcoord;
out vec2 v_texcoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * position;
    v_texcoord = texcoord;
};

#shader fragment
#version 330 core
layout(location = 0) out vec4 fragment_color;
in vec2 v_texcoord;
uniform sampler2D texture_1;
void main()
{
    vec4 base=vec4(0.5, 1.0, 1.0, 1.0);
    fragment_color = mix(texture(texture_1, v_texcoord),
                         base, 0);
};
