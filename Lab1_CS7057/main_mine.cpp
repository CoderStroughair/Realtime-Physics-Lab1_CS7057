
#include <windows.h>
#include "Antons_maths_funcs.h"
#include "teapot.h" // teapot mesh
#include "Utilities.h"
#include "Particle.h"

using namespace std;

const float width = 800, height = 800;
/*----------------------------------------------------------------------------
						MESH AND TEXTURE VARIABLES
----------------------------------------------------------------------------*/
/// this mesh is a dae file format but you should be able to use any other format too, obj is typically what is used
/// put the mesh in your project directory, or provide a filepath for it here
///for each new mesh, create new #define for the object, and the texture if required 
#define MONKEYHEAD_MESH	"../Meshes/suzanne.obj"
#define SPHERE_MESH		"../Meshes/polysphere.obj"
#define GEM_MESH		"../Meshes/gem.obj"
#define WALL_MESH		"../Meshes/wall.obj"
#define BEAR_MESH		"../Meshes/bear.obj"
#define LAMP_MESH		"../Meshes/lamp.obj"
#define TORCH_MESH		"../Meshes/torch.obj"
#define SIGN_MESH		"../Meshes/sign.obj"
#define BUDDHA_MESH		"../Meshes/buddha.dae"
#define PARTICLE_MESH	"../Meshes/particle.dae"


#define BEAR_TEXTURE	"../Textures/bear.tga"
#define BEAR_TEXTURE2	"../Textures/bear2.tga"
#define CUBE_TEXTURE	"../Textures/cubemap.png"
#define REFLECT_TEXTURE	"../Textures/reflection.png"
#define REFRACT_TEXTURE	"../Textures/refraction.png"
#define NORMAL_TEXTURE	"../Textures/normalmapped.png"
#define BRICK_TEXTURE	"../Textures/brickwall.jpg"
#define BRICK_NORMAL	"../Textures/brickwall_normal.jpg"



Mesh monkeyhead_object, torch_object, wall_object, cube, bear_object, signReflect_object, signRefract_object, signNormal_object;
Mesh gem_object, sphere_object, particle_object;


//Cube Vertices for the Skybox
GLfloat vertices[] = {
	-10.0f, -10.0f, -10.0f,  0.0f,  0.0f, -1.0f,
	10.0f, -10.0f, -10.0f,  0.0f,  0.0f, -1.0f,
	10.0f,  10.0f, -10.0f,  0.0f,  0.0f, -1.0f,
	10.0f,  10.0f, -10.0f,  0.0f,  0.0f, -1.0f,
	-10.0f,  10.0f, -10.0f,  0.0f,  0.0f, -1.0f,
	-10.0f, -10.0f, -10.0f,  0.0f,  0.0f, -1.0f,

	-10.0f, -10.0f,  10.0f,  0.0f,  0.0f,  1.0f,
	10.0f, -10.0f,  10.0f,  0.0f,  0.0f,  1.0f,
	10.0f,  10.0f,  10.0f,  0.0f,  0.0f,  1.0f,
	10.0f,  10.0f,  10.0f,  0.0f,  0.0f,  1.0f,
	-10.0f,  10.0f,  10.0f,  0.0f,  0.0f,  1.0f,
	-10.0f, -10.0f,  10.0f,  0.0f,  0.0f,  1.0f,

	-10.0f,  10.0f,  10.0f, -1.0f,  0.0f,  0.0f,
	-10.0f,  10.0f, -10.0f, -1.0f,  0.0f,  0.0f,
	-10.0f, -10.0f, -10.0f, -1.0f,  0.0f,  0.0f,
	-10.0f, -10.0f, -10.0f, -1.0f,  0.0f,  0.0f,
	-10.0f, -10.0f,  10.0f, -1.0f,  0.0f,  0.0f,
	-10.0f,  10.0f,  10.0f, -1.0f,  0.0f,  0.0f,

	10.0f,  10.0f,  10.0f,  1.0f,  0.0f,  0.0f,
	10.0f,  10.0f, -10.0f,  1.0f,  0.0f,  0.0f,
	10.0f, -10.0f, -10.0f,  1.0f,  0.0f,  0.0f,
	10.0f, -10.0f, -10.0f,  1.0f,  0.0f,  0.0f,
	10.0f, -10.0f,  10.0f,  1.0f,  0.0f,  0.0f,
	10.0f,  10.0f,  10.0f,  1.0f,  0.0f,  0.0f,

	-10.0f, -10.0f, -10.0f,  0.0f, -1.0f,  0.0f,
	10.0f, -10.0f, -10.0f,  0.0f, -1.0f,  0.0f,
	10.0f, -10.0f,  10.0f,  0.0f, -1.0f,  0.0f,
	10.0f, -10.0f,  10.0f,  0.0f, -1.0f,  0.0f,
	-10.0f, -10.0f,  10.0f,  0.0f, -1.0f,  0.0f,
	-10.0f, -10.0f, -10.0f,  0.0f, -1.0f,  0.0f,

	-10.0f,  10.0f, -10.0f,  0.0f,  1.0f,  0.0f,
	10.0f,  10.0f, -10.0f,  0.0f,  1.0f,  0.0f,
	10.0f,  10.0f,  10.0f,  0.0f,  1.0f,  0.0f,
	10.0f,  10.0f,  10.0f,  0.0f,  1.0f,  0.0f,
	-10.0f,  10.0f,  10.0f,  0.0f,  1.0f,  0.0f,
	-10.0f,  10.0f, -10.0f,  0.0f,  1.0f,  0.0f
}; 

/*----------------------------------------------------------------------------
								SHADER VARIABLES
----------------------------------------------------------------------------*/


#define SKY_VERT	"../Shaders/skyboxVertexShader.txt"
#define SKY_FRAG	"../Shaders/skyboxFragmentShader.txt"

#define NOTEXTURE_VERT	"../Shaders/noTextureVertexShader.txt"
#define NOTEXTURE_FRAG	"../Shaders/noTextureFragmentShader.txt"

#define REFLECTIVE_FRAG "../Shaders/reflectiveFragmentShader.txt"

#define FRESNEL_FRAG	"../Shaders/fresnelFragmentShader.txt"

#define TEXTURE_VERT	"../Shaders/textureVertexShader.txt"
#define TEXTURE_FRAG	"../Shaders/textureFragmentShader.txt"

#define NORMAL_VERT		"../Shaders/normalisedVertexShader.txt"
#define NORMAL_FRAG		"../Shaders/normalisedFragmentShader.txt"

#define MIRROR_VERT		"../Shaders/mirrorVertexShader.txt"
#define MIRROR_FRAG		"../Shaders/mirrorFragmentShader.txt"

#define TEST_VERT "../Shaders/testVertex.txt"
#define TEST_FRAG "../Shaders/testFragment.txt"

#define DEBUG_VERT "../Shaders/debugSkyboxVertex.txt"
#define DEBUG_FRAG "../Shaders/debugSkyboxFragment.txt"

GLuint noTextureShaderID, textureShaderID, cubeMapTextureID, refractiveShaderID, cubeMapShaderID;
GLuint testID, normalisedShaderID, reflectiveShaderID, multiTextureShaderID, mirrorShaderID, debugSkyboxID;
Shader shaderFactory;
/*----------------------------------------------------------------------------
							CAMERA VARIABLES
----------------------------------------------------------------------------*/

vec3 startingPos = { 0.0f, 0.0f, -20.0f };
vec3 startingFront = { 0.0f, 0.0f, 1.0f };
GLfloat pitCam = 0, yawCam = 0, rolCam = 0, frontCam = 0, sideCam = 0, speed = 1;
float rotateY = 50.0f, rotateLight = 0.0f;
Camera cam(startingPos, startingFront, vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 0.0f);

/*----------------------------------------------------------------------------
							OTHER VARIABLES
----------------------------------------------------------------------------*/

const char* atlas_image = "../freemono.png";
const char* atlas_meta = "../freemono.meta";

float fontSize = 25.0f;
int textID = -1;
void drawloop(mat4 view, mat4 proj, GLuint framebuffer);

const int numGems = 300;
vec3 gemLocation[numGems];
vec3 gemColour[numGems];
bool simple = true, mesh = true;

ParticleSystem ps;
/*--------------------------------------------------------------------------*/

void init()
{
	if (!init_text_rendering(atlas_image, atlas_meta, width, height)) 
	{
		fprintf(stderr, "ERROR init text rendering\n");
		exit(1);
	}
	cam.setSensitivity(2.0f);
	//*************************//
	//*****Compile Shaders*****//
	//*************************//
	refractiveShaderID = shaderFactory.CompileShader(NOTEXTURE_VERT, FRESNEL_FRAG);
	noTextureShaderID = shaderFactory.CompileShader(NOTEXTURE_VERT, NOTEXTURE_FRAG);
	cubeMapShaderID = shaderFactory.CompileShader(SKY_VERT, SKY_FRAG);
	textureShaderID = shaderFactory.CompileShader(TEXTURE_VERT, TEXTURE_FRAG);
	normalisedShaderID = shaderFactory.CompileShader(NORMAL_VERT, NORMAL_FRAG);
	reflectiveShaderID = shaderFactory.CompileShader(NOTEXTURE_VERT, REFLECTIVE_FRAG);
	multiTextureShaderID = shaderFactory.CompileShader(TEXTURE_VERT, TEXTURE_FRAG);
	mirrorShaderID = shaderFactory.CompileShader(MIRROR_VERT, MIRROR_FRAG);
	debugSkyboxID = shaderFactory.CompileShader(DEBUG_VERT, DEBUG_FRAG);
	testID = shaderFactory.CompileShader(TEST_VERT, TEST_FRAG);
	//*********************//
	//*****Init Objects*****//
	//*********************//
	monkeyhead_object.init(MONKEYHEAD_MESH);
	cube.initCubeMap(vertices, 36, "desert");
	torch_object.init(TORCH_MESH);
	bear_object.init(BEAR_MESH, BEAR_TEXTURE, BEAR_TEXTURE2);
	wall_object.init(WALL_MESH, NULL, BRICK_NORMAL);
	signReflect_object.init(SIGN_MESH, REFLECT_TEXTURE);
	signRefract_object.init(SIGN_MESH, REFRACT_TEXTURE);
	signNormal_object.init(SIGN_MESH, NORMAL_TEXTURE);
	sphere_object.init(SPHERE_MESH);
	gem_object.init(GEM_MESH);
	particle_object.init(GEM_MESH);

	ps.init(1000, particle_object);
}

void display() 
{
	mat4 proj = perspective(87.0, (float)width / (float)(height), 1, 1000.0);
	mat4 view;
	glViewport(0, 0, width, height);
		
	view = look_at(cam.getPosition(), cam.getPosition() + cam.getFront(), cam.getUp());
	proj = perspective(60.0, (float)width / (float)height, 1, 1000.0);
	glViewport(0, 0, width, height);
	drawloop(view, proj, 0);
	//draw_texts();
	glutSwapBuffers();
}

void updateScene() {
	static DWORD  last_frame;	//time when last frame was drawn
	static DWORD last_timer = 0;	//time when timer was updated
	DWORD  curr_time = timeGetTime();//for frame Rate Stuff.
	static bool first = true;
	if (first)
	{
		last_frame = curr_time;
		first = false;
	}
	float  delta = (curr_time - last_frame) * 0.001f;
	if (delta >= 0.03f) 
	{
		last_frame = curr_time;
		glutPostRedisplay();
		rotateY = rotateY + 0.5f;
		rotateLight = rotateLight + 0.01f;
		if (rotateY >= 360.0f)
			rotateY = 0.0f;
		if (rotateLight >= 360.0f)
			rotateLight = 0.0f;
		cam.movForward(frontCam*speed);
		cam.movRight(sideCam*speed);
		cam.changeFront(pitCam, yawCam, rolCam);
		ps.applyForces(delta);
		ps.checkCollisions(vec3(0.0, -6.5, 0.0), vec3(0.0, 0.5, -0.5), delta);
		ps.checkCollisions(vec3(0.0, -6.5, 0.0), vec3(0.0, 0.5, 0.5), delta);
		ps.checkCollisions(vec3(0.0, -6.5, 0.0), vec3(0.5, 0.5, 0.0), delta);
		ps.checkCollisions(vec3(0.0, -6.5, 0.0), vec3(-0.5, 0.5, 0.0), delta);
		ps.checkCollisions(vec3(0.0, +2.5, 0.0), vec3(0.0, 1.0, 0.0), delta);
	}
	
}

#pragma region INPUT FUNCTIONS

void keypress(unsigned char key, int x, int y) 
{
	if (key == (char)27)	//Pressing Escape Ends the game
	{
		exit(0);
	}
	else if (key == 'w' || key == 'W')
		frontCam = 1;
	else if ((key == 's') || (key == 'S'))
		frontCam = -1;
	if ((key == 'a') || (key == 'A'))
		sideCam = -1;
	else if ((key == 'd') || (key == 'D'))
		sideCam = 1;
	if (key == ' ')
	{
		simple = !simple;
		if (simple)
			update_text(textID, "Simplified Version - This only shows a single cubemap");
		else
			update_text(textID, "Complex Version - This shows the use of all four cubemaps");
	}
	if (key == 'm')
	{
		mesh = !mesh;
	}
}

void keypressUp(unsigned char key, int x, int y)
{
	if ((key == 'w') || (key == 'W'))
		frontCam = 0;
	else if ((key == 's') || (key == 'S'))
		frontCam = 0;
	if ((key == 'a') || (key == 'A'))
		sideCam = 0;
	else if ((key == 'd') || (key == 'D'))
		sideCam = 0;
}

void specialKeypress(int key, int x, int y) 
{
	switch (key)
	{
	case (GLUT_KEY_SHIFT_L):
	case (GLUT_KEY_SHIFT_R):
		speed = 4;
		break;
	case (GLUT_KEY_LEFT):
		yawCam = -1;
		break;
	case (GLUT_KEY_RIGHT):
		yawCam = 1;
		break;
	case (GLUT_KEY_UP):
		pitCam = 1;
		break;
	case (GLUT_KEY_DOWN):
		pitCam = -1;
		break;
	}
}

void specialKeypressUp(int key, int x, int y) 
{
	switch (key)
	{
	case (GLUT_KEY_SHIFT_L):
	case (GLUT_KEY_SHIFT_R):
		speed = 1;
		break;
	case (GLUT_KEY_LEFT):
		yawCam = 0;
		break;
	case (GLUT_KEY_RIGHT):
		yawCam = 0;
		break;
	case (GLUT_KEY_UP):
		pitCam = 0;
		break;
	case (GLUT_KEY_DOWN):
		pitCam = 0;
		break;
	}
}

void (mouse)(int x, int y)
{
	
}

#pragma endregion INPUT FUNCTIONS

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("GameApp");
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);


	// Tell glut where the display function is
	glutWarpPointer(width / 2, height / 2);
	glutDisplayFunc(display);
	glutIdleFunc(updateScene);

	// Input Function Initialisers //
	glutKeyboardFunc(keypress);
	glutPassiveMotionFunc(mouse);
	glutSpecialFunc(specialKeypress);
	glutSpecialUpFunc(specialKeypressUp);
	glutKeyboardUpFunc(keypressUp);

	// A call to glewInit() must be done after glut is initialized!
	GLenum res = glewInit();
	// Check for any errors
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	init();
	textID = add_text(
		"Simplified Version - This only shows a single cubemap",
		-0.9, 0.8, fontSize, 1.0f, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < sizeof(gemLocation) / sizeof(*gemLocation); i++)
	{
		gemLocation[i] = vec3(rand() % 50 - 25, -6.5f, rand() % 50 - 23);
		int colourNumber = rand() % 4;
		if (colourNumber == 0)
			gemColour[i] = RED;
		else if (colourNumber == 1)
			gemColour[i] = PURPLE;
		else if (colourNumber == 2)
			gemColour[i] = GREEN;
		else
			gemColour[i] = YELLOW;
	}
	glutMainLoop();
	return 0;
}

void drawloop(mat4 view, mat4 proj, GLuint framebuffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glEnable(GL_DEPTH_TEST);								// enable depth-testing
	glDepthFunc(GL_LESS);									// depth-testing interprets a smaller value as "closer"
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear the color and buffer bits to make a clean slate
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);					//Create a background


	mat4 model;
	model = identity_mat4();
	// light properties
	vec3 Ls = vec3(1.0f, 1.0f, 1.0f);	//Specular Reflected Light
	vec3 Ld = vec3(0.99f, 0.99f, 0.99f);	//Diffuse Surface Reflectance
	vec3 La = vec3(1.0f, 1.0f, 1.0f);	//Ambient Reflected Light
	vec3 light = vec3(5 * sin(rotateLight), 10, -5.0f*cos(rotateLight));//light source location
	vec3 coneDirection = light + vec3(0.0f, -1.0f, 0.0f);
	float coneAngle = 10.0f;
	// object colour
	vec3 Ks = vec3(0.1f, 0.1f, 0.1f); // specular reflectance
	vec3 Kd = BROWN;
	vec3 Ka = vec3(0.05f, 0.05f, 0.05f); // ambient reflectance
	float specular_exponent = 0.5f; //specular exponent - size of the specular elements

	model = identity_mat4();
	drawCubeMap(cubeMapShaderID, cube.tex, view, proj, model, Ld, La, cam, cube, GL_TRIANGLES);

	model = scale(identity_mat4(), vec3(0.01f, 0.01f, 0.01f));
	model = translate(model, light);
	drawObject(noTextureShaderID, view, proj, model, light, Ls, La, Ld, Ks, Ka, WHITE, specular_exponent, cam, cube, coneAngle, coneDirection, GL_TRIANGLES);

	model = translate(identity_mat4(), vec3(0.0f, -6.3f, 0.0f));
	drawObject(noTextureShaderID, view, proj, model, light, Ls, La, Ld, Ks, Ka, Kd, specular_exponent, cam, torch_object, coneAngle, coneDirection, GL_QUADS);


	model = rotate_z_deg(identity_mat4(), 90.0f);
	model = translate(model, vec3(-7.5, -6.5f, -7.5));
	mat4 root = model;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			model = translate(root, vec3(15.0f*i, 0.0, 0.0));
			model = translate(model, vec3(0.0, 0.0, 15.0f*j));
			drawObject(normalisedShaderID, view, proj, model, vec3(-light.v[0], -light.v[1], -light.v[2]), Ls, La, Ld, Ks, Ka, GREY, 50.0f, cam, wall_object, coneAngle, coneDirection, GL_TRIANGLES);
		}
	}


	specular_exponent = 0.3f; //specular exponent - size of the specular elements
	for (int i = 0; i < sizeof(gemLocation)/sizeof(*gemLocation); i++)
	{
		model = rotate_y_deg(identity_mat4(), 300*rotateLight);
		vec3 location = gemLocation[i];//light source location
		model = translate(model, location);
		//drawObject(normalisedShaderID, view, proj, model, light, Ls, gemColour[i], Ld, vec3(0.8, 0.8, 0.8), vec3(0.1, 0.1, 0.1), gemColour[i], specular_exponent, cam, gem_object, NULL, coneDirection, GL_TRIANGLES);
	}
	for (int i = 0; i < ps.numParticles; i++)
	{
		ps.particles[i].evolve();
		model = identity_mat4();
		model = scale(model, vec3(ps.particles[i].scale, ps.particles[i].scale, ps.particles[i].scale));
		model = translate(model, ps.particles[i].position);
		drawObject(normalisedShaderID, view, proj, model, light, Ls, ps.particles[i].colour, Ld, vec3(0.8, 0.8, 0.8), vec3(0.1, 0.1, 0.1), ps.particles[i].colour, specular_exponent, cam, ps.particles[i].mesh, NULL, coneDirection, GL_TRIANGLES);
	}
	model = scale(identity_mat4(), vec3(2.0, 2.0, 2.0));
	model = rotate_z_deg(model, 132);
	model = translate(model, vec3(0.0, 21.0, 0.0));
	drawObject(normalisedShaderID, view, proj, model, light, Ls, ps.particles[0].colour, Ld, vec3(0.8, 0.8, 0.8), vec3(0.1, 0.1, 0.1), ps.particles[0].colour, specular_exponent, cam, ps.particles[0].mesh, NULL, coneDirection, GL_TRIANGLES);
}