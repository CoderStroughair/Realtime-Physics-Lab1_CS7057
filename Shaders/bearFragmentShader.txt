#version 330

in vec3 position_eye;
in vec3 normal_eye;
in vec3 light_position_eye; 
in vec3 camPos;

//************//
//OBJECT COLOR//
//************//
vec3 Ks = vec3(1.0f, 1.0f, 1.0f); // specular reflectance
vec3 Kd = vec3(238.0f/255.0f, 202.0f/255.0f, 109f/255.0f); // diffuse reflectance
vec3 Ka = vec3(1.0f, 1.0f, 1.0f); // ambient reflectance
float specular_exponent = 10.0f; //specular 'power'?

//***********//
//LIGHT COLOR//
//***********//
uniform vec3 Ls; //white specular color
uniform vec3 Ld; // dull white diffuse light 
uniform vec3 La;  // grey ambient color


out vec4 fragment_color;

void main()
{    


    //ambient
    vec3 Ia = La * Ka;
    
	//diffuse
	vec3 norm = normalize(normal_eye);
	vec3 direction_to_light_eye = normalize(light_position_eye - position_eye);
	float diff = max(dot(norm, direction_to_light_eye), 0.0);
	//vec3 diffuse = diff * lightColor;

    vec3 Id = Ld * diff * Kd; 
    
    //Specular Intensity

	vec3 viewDir = normalize(camPos - position_eye);
	vec3 halfwayDir = normalize(direction_to_light_eye + viewDir);
    //vec3 reflection_eye = reflect(-direction_to_light_eye, normal_eye); 
	//float spec = pow(max(dot(viewDir, reflection_eye), 0.0), 32);
	float spec = pow(max(dot(normal_eye, halfwayDir), 0.0), 32);
	vec3 Is = specular_exponent * spec * Ks * Ls; 
    
	vec3 average = normalize(vec3((Ia.r+Id.r+Is.r)/3.0, (Ia.g+Id.g+Is.g)/3.0, (Ia.b+Id.b+Is.b)/3.0));
    fragment_color = vec4(average, 1.0);
}