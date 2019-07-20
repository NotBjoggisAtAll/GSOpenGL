#version 330 core
struct Material
{
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 Position;

    vec3 Color;

    float constant;
    float linear;
    float quadratic;
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
    vec3 lightDir = normalize(light.Position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.Color * (diff * material.diffuse);

    // specular
    vec3 viewDir = normalize(CameraPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.Color * (spec * material.specular);

    float distance = length(light.Position - FragPos);
    float attenutaion = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance*distance));

    Ambient  *= attenutaion;
    diffuse  *= attenutaion;
    specular *= attenutaion;

    vec3 result = Ambient + diffuse + specular;


    FragColor = vec4(result, 1.0);
}
