#version 330 core

out vec4 FragColor;
in vec3 FragPos;
in vec3 ModelPos;

uniform int ID;

void main()
{
    vec3 dx = dFdx(ModelPos);
    vec3 dy = dFdy(ModelPos);
    vec3 N = normalize(cross(dx, dy));
    vec3 absN = abs(N);
    vec3 color;

    if (ID == 0)
        color = vec3(0.75, 0.3, 0.3);
    else if (ID == 1) 
        color = vec3(0.5, 0.5, 0.5);
    else if (ID == 2)
    {
        if (abs(ModelPos.x) < 0.25)
            color = vec3(0.75, 0.75, 0.75);
        else 
            color = vec3(0.05, 0.05, 0.05);
    }

    vec3 viewDir = normalize(-FragPos);
    float fresnel = pow(1.0 - abs(dot(viewDir, N)), 3.0);
    color += fresnel * 0.15;
    FragColor = vec4(color, 1.0);
}