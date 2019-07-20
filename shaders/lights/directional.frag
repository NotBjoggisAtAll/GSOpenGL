#version 330 core
struct Material
{
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 Direction;
    vec3 Color;
};


in vec3 Normals;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 CameraPosition;

uniform Light light;
uniform Material material;

void main()
{


    // Ambient
    vec3 Ambient = material.diffuse * 0.1;

    // diffuse
    vec3 norm = normalize(Normals);
    vec3 lightDir = normalize(-light.Direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.Color * (diff * material.diffuse);

    // specular
    vec3 viewDir = normalize(CameraPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.Color * (spec * material.specular);

    vec3 result = Ambient + diffuse + specular;


    FragColor = vec4(result, 1.0);
}
