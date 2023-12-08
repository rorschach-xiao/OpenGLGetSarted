#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;

// cubemap
uniform samplerCube skybox;


void main()
{
    vec3 norm = normalize(Normal);

    vec3 I = normalize(FragPos - viewPos);
    vec3 R = reflect(I, norm);
    vec3 result = texture(skybox, R).rgb;

    FragColor = vec4(result, 1.0);
}

