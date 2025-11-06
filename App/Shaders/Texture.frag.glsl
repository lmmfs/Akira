#version 460 core
out vec4 FragColor;

in vec2 v_TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, v_TexCoord);
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
