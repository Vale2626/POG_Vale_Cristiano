
#version 330 core
out vec4 FragColor;
in vec3 vColor;
in vec2 vTex;  
in vec3 vNormal;  
in vec3 vFragPos; 

uniform sampler2D tex0;    //texture del modello
uniform vec3 lightPos;     // posizione cubo-luce
uniform vec3 lightColor;   // es. (1,1,1)
uniform vec3 camPos;       // posizione camera

struct SpotLight
{
    vec3 position;
    vec3 direction;     //direzione in cui ounta il cono di luce

    float cutOff;       //coseno(angolo interno)
    float outerCutOff;  //coseno(angolo esterno)

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;


};

uniform SpotLight spotLight;

void main() {

    vec4 texel = texture(tex0, vTex);       //Un texel è l'unità fondamentale di una texture, texel = colore della texture
    vec3 albedo = texel.rgb;
    float alpha = texel.a;      //salvataggio del canale alpha

    float ambient = 0.20;
    vec3 N = normalize(vNormal);
    vec3 L = normalize(lightPos - vFragPos);    //direzione della luce
    float diff = max(dot(N, L), 0.0);

    vec3 V = normalize(camPos - vFragPos);
    vec3 R = reflect(-L, N);
    float specAmount = pow(max(dot(V, R), 0.0), 32.0);
    float ks = 0.5;

    vec3 lightingPoint = lightColor * (ambient + diff + ks * specAmount);
   

    // SPOT LIGHT

   vec3 Ls = normalize(spotLight.position - vFragPos);

    float theta = dot(Ls, normalize(-spotLight.direction));
    float epsilon = spotLight.cutOff - spotLight.outerCutOff;
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambientS = spotLight.ambient;

    float diffS = max(dot(N, Ls), 0.0);
    vec3 diffuseS = spotLight.diffuse * diffS;

    vec3 Rs = reflect(-Ls, N);
    float specAmountS = pow(max(dot(V, Rs), 0.0), 32.0);
    float ksS = 0.5;
    vec3 specularS = spotLight.specular * specAmountS * ksS;

    float distanceS = length(spotLight.position - vFragPos);
    float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distanceS + spotLight.quadratic * (distanceS * distanceS));

    diffuseS  *= intensity;
    specularS *= intensity;

    vec3 lightingSpot = (ambientS + diffuseS + specularS) * attenuation;

    //somma di tutte le luci

    vec3 totalLight = lightingPoint + lightingSpot;

    //colore finale
    vec3 final_rgb = albedo * totalLight;
    FragColor = vec4(final_rgb, alpha);
}
   //Colore figura, texture modulata dal colore interpolato