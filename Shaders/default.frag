
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
uniform bool forceUnlit;   // true = bypass illuminazione (per texture che devono restare piatte)

struct SpotLight
{
    vec3 position;
    vec3 direction;     //direzione in cui punta il cono di luce

    float cutOff;       //coseno(angolo interno)
    float outerCutOff;  //coseno(angolo esterno)

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

#define MAX_SPOTS 8
uniform int spotCount;
uniform SpotLight spotLights[MAX_SPOTS];    //vettore per le spotlight dato che ne voglio più di una

void main() {

    vec4 texel = texture(tex0, vTex);       //Un texel è l'unità fondamentale di una texture, texel = colore della texture
    vec3 albedo = texel.rgb;
    float alpha = texel.a;      //salvataggio del canale alpha

    // Se richiesto, salta tutta l'illuminazione per questa mesh
    if (forceUnlit) {
        FragColor = vec4(albedo, alpha);
        return;
    }

    float ambient = 0.36; // riduci luce ambiente costante per evitare scene bruciate
    vec3 N = normalize(vNormal);
    vec3 L = normalize(lightPos - vFragPos);    //direzione della luce
    float diff = max(dot(N, L), 0.0);

    vec3 V = normalize(camPos - vFragPos);
    vec3 R = reflect(-L, N);
    float specAmount = pow(max(dot(V, R), 0.0), 32.0);
    float ks = 0.5;

    vec3 lightingPoint = lightColor * (ambient + diff + ks * specAmount);
   

    // SPOT LIGHTS multiple
    vec3 lightingSpot = vec3(0.0);
    for (int i = 0; i < spotCount && i < MAX_SPOTS; ++i) {
        SpotLight sl = spotLights[i];
        vec3 Ls = normalize(vFragPos - sl.position); // vettore dalla luce verso il frammento

        float theta = dot(Ls, normalize(sl.direction));
        float epsilon = sl.cutOff - sl.outerCutOff;
        float intensity = clamp((theta - sl.outerCutOff) / epsilon, 0.0, 1.0);

        vec3 ambientS = sl.ambient;

        float diffS = max(dot(N, -Ls), 0.0); // luce in arrivo = -Ls
        vec3 diffuseS = sl.diffuse * diffS;

        vec3 Rs = reflect(-Ls, N);
        float specAmountS = pow(max(dot(V, Rs), 0.0), 32.0);
        float ksS = 0.5;
        vec3 specularS = sl.specular * specAmountS * ksS;

        float distanceS = length(sl.position - vFragPos);
        float attenuation = 1.0 / (sl.constant + sl.linear * distanceS + sl.quadratic * (distanceS * distanceS));

        diffuseS  *= intensity;
        specularS *= intensity;

        lightingSpot += (ambientS + diffuseS + specularS) * attenuation;
    }

    //somma di tutte le luci
    vec3 totalLight = lightingPoint + lightingSpot;


    //colore finale
    vec3 final_rgb = albedo * totalLight;
    FragColor = vec4(final_rgb, alpha);
}
   //Colore figura, texture modulata dal colore interpolato
