#include "glut.h"
#include <math.h>
#include <Windows.h>

#include <string>

#include "SolarSystemConstants.h"
#include "Planets.h"
#include "SOIL.h"

using namespace std;

//*********************//
//  Global Variables  //
//*******************//

// Viewer positioning angles.
GLfloat viewerAzimuth = INITIAL_VIEWER_AZIMUTH;
GLfloat viewerZenith  = INITIAL_VIEWER_ZENITH;
GLfloat viewerDistance = INITIAL_VIEWER_DISTANCE;

// Camera Position
POINT mousePos;
GLfloat lookAtPosition[] = { INITIAL_LOOK_AT_POSITION[0], INITIAL_LOOK_AT_POSITION[1], INITIAL_LOOK_AT_POSITION[2] };
GLfloat dragXStart = 0.0;
GLfloat dragYStart = 0.0;
bool dragging = false;

// Variables to keep track of current day status.
GLfloat CurrentEarthRotation = 0.00;
GLfloat EarthDaysPassed = 0.00;
GLfloat EarthDayIncrement = 0.01;

// The initial window and viewport sizes (in pixels), set to ensure that
// the aspect ratio for the viewport, will be a constant. If the window
// is resized, the viewport will be adjusted to preserve the aspect ratio.
GLint currentWindowSize[2]   = { 1200, 1200/ASPECT_RATIO };
GLint currentViewportSize[2] = { 1200, 1200/ASPECT_RATIO };

const char* planetNames[9] = { "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto" };
GLfloat planetNamesOffsets[9][3] = { {MERCURY_ORBIT_RADIUS, MERCURY_INCLINATION, 0.2}, {VENUS_ORBIT_RADIUS, VENUS_INCLINATION, -0.3}, {EARTH_ORBIT_RADIUS, EARTH_INCLINATION, 0.3}, {MARS_ORBIT_RADIUS, MARS_INCLINATION, -0.4}, {JUPITER_ORBIT_RADIUS, JUPITER_INCLINATION, 0.2}, {SATURN_ORBIT_RADIUS, SATURN_INCLINATION, -0.3}, {URANUS_ORBIT_RADIUS, URANUS_INCLINATION, 0.3}, {NEPTUNE_ORBIT_RADIUS, NEPTUNE_INCLINATION, -0.4}, {PLUTO_ORBIT_RADIUS, PLUTO_INCLINATION, 0.2} };

// IDs for texture maps.
GLuint texture[100];
GLuint SunTextureName = 0;
GLuint SkyboxTextureName = 10;
GLuint AsteroidTextureName = 11;

GLuint MercuryTextureName = 1;

GLuint VenusTextureName = 2;

GLuint EarthTextureName = 3;
GLuint MoonTextureName = 31;

GLuint MarsTextureName = 4;
GLuint PhobosTextureName = 41;
GLuint DeimosTextureName = 42;

GLuint JupiterTextureName = 5;
GLuint IoTextureName = 51;
GLuint EuropaTextureName = 52;
GLuint GanymedeTextureName = 53;
GLuint CallistoTextureName = 54;

GLuint SaturnTextureName = 6;
GLuint SaturnRingsTextureName = 61;
GLuint TitanTextureName = 62;

GLuint UranusTextureName = 7;
GLuint TitaniaTextureName = 71;
GLuint OberonTextureName = 72;
GLuint UmbrielTextureName = 73;
GLuint ArielTextureName = 74;
GLuint MirandaTextureName = 75;

GLuint NeptuneTextureName = 8;
GLuint TritonTextureName = 81;

GLuint PlutoTextureName = 9;
GLuint CharonTextureName = 91;

//************************//
//  Function Signitures  //
//**********************//
void reshapeWindow(GLsizei w, GLsizei h);
void keyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition);
void directionalKeysPress(int pressedKey, int mouseXPosition, int mouseYPosition);
void mouseClick(int button, int state, int x, int y);
void mouseMoveActive(int x, int y);

void timerFunction(int value);
void display();

void setLights();
void updateLight();

void createAllPlanets(void);
void createAndDrawPlanet(GLuint planetName, GLfloat radius, GLfloat orbitRadius, GLfloat orbitDuration, GLfloat rotationDuration, GLfloat inclination, GLuint textureName);
void createAndDrawMoon(GenericPlanet *planet, GLfloat radius, GLfloat orbitRadius, GLfloat lunarCycle, GLfloat inclination, GLuint textureName);
void createAndDrawRings(GenericPlanet *planet, GLuint textureName);
void drawAsteroids();

void drawOrbits();
void drawAsteroidBelt();

void drawSkybox();

void generateTextures();
void generateTexture(const char *imgName, GLuint textureName);

void initWindow(void);
void initLightingShadingDepth(void);

int main(int argc, char** argv)
{
	glutInit (&argc, argv);
	initWindow();

	glutReshapeFunc( reshapeWindow );
	glutKeyboardFunc( keyboardPress );
	glutSpecialFunc( directionalKeysPress );
	glutMouseFunc( mouseClick );
	glutMotionFunc( mouseMoveActive );

	glutDisplayFunc( display );
	glutTimerFunc( 20, timerFunction, 1 );
	glViewport(0, 0, currentWindowSize[0], currentWindowSize[1]);

	initLightingShadingDepth();

	glutMainLoop();
	return 0;
}

void reshapeWindow(GLsizei w, GLsizei h) {
	
	currentWindowSize[0] = w;
	currentWindowSize[1] = h;

	if(ASPECT_RATIO > currentWindowSize[0]/currentWindowSize[1]) {
		currentViewportSize[0] = w;
		currentViewportSize[1] = w / ASPECT_RATIO;
	}
	else {
		currentViewportSize[0] = h * ASPECT_RATIO;
		currentViewportSize[1] = h;
	}

	glViewport(0.5*(w-currentViewportSize[0]), 0.5*(h-currentViewportSize[1]), currentViewportSize[0], currentViewportSize[1]);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition) {
	
	char pressedChar = char(pressedKey);
	switch(pressedKey)
	{
		case '+': {
			EarthDayIncrement *= 2.0;
			if (EarthDayIncrement > 10.0) { EarthDayIncrement = 10.0; }
			break;
		}
		case '-': {		
			EarthDayIncrement *= 0.5;
			if (EarthDayIncrement < 0.01) { EarthDayIncrement = 0.01; }
			break;
		}
		//Zooming In/Out
		case 'z': {
			viewerDistance -= VIEWER_DISTANCE_INCREMENT;
			if(viewerDistance < MINIMUM_VIEWER_DISTANCE) { viewerDistance = MINIMUM_VIEWER_DISTANCE; }
			break;
		}
		case 'x': {
			viewerDistance +=VIEWER_DISTANCE_INCREMENT;
			if(viewerDistance > MAXIMUM_VIEWER_DISTANCE) { viewerDistance = MAXIMUM_VIEWER_DISTANCE; }
			break;
		}
		//Reset Planets
		case 'R': {
			CurrentEarthRotation = 0.00;
			EarthDaysPassed = 0.00;
			EarthDayIncrement = 0.01;
			break;
		}
		//Reset Camera to origin
		case 'C': {
			lookAtPosition[0] = INITIAL_LOOK_AT_POSITION[0];
			lookAtPosition[1] = INITIAL_LOOK_AT_POSITION[1];
			lookAtPosition[2] = INITIAL_LOOK_AT_POSITION[2];
			break;
		}
	}
}

void directionalKeysPress(int pressedKey, int mouseXPosition, int mouseYPosition) {
	glutIgnoreKeyRepeat(false);
	switch(pressedKey) {
		case GLUT_KEY_UP: {
			viewerZenith -= VIEWER_ANGLE_INCREMENT;
			if(viewerZenith < VIEWER_ANGLE_INCREMENT) { viewerZenith = VIEWER_ANGLE_INCREMENT; }
			break;
		}
		case GLUT_KEY_DOWN: {
			viewerZenith += VIEWER_ANGLE_INCREMENT;
			if(viewerZenith > PI - VIEWER_ANGLE_INCREMENT) { viewerZenith = PI - VIEWER_ANGLE_INCREMENT; }
			break;
		}
		case GLUT_KEY_LEFT: {
			viewerAzimuth -= VIEWER_ANGLE_INCREMENT;
			if(viewerAzimuth < 0.0) { viewerAzimuth += 2*PI; }
			break;
		}
		case GLUT_KEY_RIGHT: {
			viewerAzimuth += VIEWER_ANGLE_INCREMENT;
			if(viewerAzimuth > 2*PI) { viewerAzimuth -= 2*PI; }
			break;
		}
	}
}

void mouseClick(int button, int state, int x, int y) {
	if(state == GLUT_DOWN) {
		if(button == GLUT_LEFT_BUTTON){
			dragging = true;
			dragXStart = x;
			dragYStart = y;
		}
	}
	else {
		dragging = false;
	}
}

void mouseMoveActive(int x, int y) {
    if(dragging) {
		lookAtPosition[0] -= (x - dragXStart)*0.3;
		lookAtPosition[1] -= (y - dragYStart)*0.3;
        dragXStart = x;
        dragYStart = y;
    }
}

void timerFunction(int value) {
	CurrentEarthRotation += EarthDayIncrement;
	EarthDaysPassed += EarthDayIncrement;
	if (EarthDaysPassed == EARTH_ORBIT_DUR)
		EarthDaysPassed = 0;
	glutPostRedisplay();
	glutTimerFunc(20, timerFunction, 1);
}

void display() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(100.0, ASPECT_RATIO, 2.5, 1000.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Position Camera location
	gluLookAt(lookAtPosition[0] + viewerDistance * sin(viewerZenith) * sin(viewerAzimuth), 
				lookAtPosition[1] + viewerDistance * cos(viewerZenith), 
				lookAtPosition[2] + viewerDistance * sin(viewerZenith) * cos(viewerAzimuth),
				lookAtPosition[0], lookAtPosition[1], lookAtPosition[2],
				0.0, 1.0, 0.020);

	drawSkybox();
	updateLight();

	Sun *sun = new Sun(SUN_RADIUS_OFFSET, texture[SunTextureName]);
	sun->drawSun();

	createAllPlanets();
	drawAsteroids();

	drawOrbits();
	drawAsteroidBelt();

	glutSwapBuffers();
	glFlush();
}

void createAllPlanets(void) {
	createAndDrawPlanet(MERCURY, MERCURY_RADIUS, MERCURY_ORBIT_RADIUS, MERCURY_ORBIT_DUR, MERCURY_ROTATION_DUR, MERCURY_INCLINATION, texture[MercuryTextureName]);
	createAndDrawPlanet(VENUS, VENUS_RADIUS, VENUS_ORBIT_RADIUS, VENUS_ORBIT_DUR, VENUS_ROTATION_DUR, VENUS_INCLINATION, texture[VenusTextureName]);
	createAndDrawPlanet(EARTH, EARTH_RADIUS, EARTH_ORBIT_RADIUS, EARTH_ORBIT_DUR, EARTH_ROTATION_DUR, EARTH_INCLINATION, texture[EarthTextureName]);
	createAndDrawPlanet(MARS, MARS_RADIUS, MARS_ORBIT_RADIUS, MARS_ORBIT_DUR, MARS_ROTATION_DUR, MARS_INCLINATION, texture[MarsTextureName]);
	createAndDrawPlanet(JUPITER, JUPITER_RADIUS, JUPITER_ORBIT_RADIUS, JUPITER_ORBIT_DUR, JUPITER_ROTATION_DUR, JUPITER_INCLINATION, texture[JupiterTextureName]);
	createAndDrawPlanet(SATURN, SATURN_RADIUS, SATURN_ORBIT_RADIUS, SATURN_ORBIT_DUR, SATURN_ROTATION_DUR, SATURN_INCLINATION, texture[SaturnTextureName]);
	createAndDrawPlanet(URANUS, URANUS_RADIUS, URANUS_ORBIT_RADIUS, URANUS_ORBIT_DUR, URANUS_ROTATION_DUR, URANUS_INCLINATION, texture[UranusTextureName]);
	createAndDrawPlanet(NEPTUNE, NEPTUNE_RADIUS, NEPTUNE_ORBIT_RADIUS, NEPTUNE_ORBIT_DUR, NEPTUNE_ROTATION_DUR, NEPTUNE_INCLINATION, texture[NeptuneTextureName]);
	createAndDrawPlanet(PLUTO, PLUTO_RADIUS, PLUTO_ORBIT_RADIUS, PLUTO_ORBIT_DUR, PLUTO_ROTATION_DUR, PLUTO_INCLINATION, texture[PlutoTextureName]);
}

void createAndDrawPlanet(GLuint planetName, GLfloat radius, GLfloat orbitRadius, GLfloat orbitDuration, GLfloat rotationDuration, GLfloat inclination, GLuint textureName) {
	GenericPlanet *planet = new GenericPlanet(planetName, radius, orbitRadius,  orbitDuration, rotationDuration, inclination, textureName);
	planet->drawPlanet(EarthDaysPassed, CurrentEarthRotation);
	switch(planetName) {
		case MERCURY:
			break;
		case VENUS:
			break;
		case EARTH:
			createAndDrawMoon(planet, MOON_RADIUS, MOON_ORBIT_RADIUS, MOON_LUNAR_CYCLE, MOON_INCLINATION, texture[MoonTextureName]);
			break;
		case MARS:
			createAndDrawMoon(planet, PHOBOS_RADIUS, PHOBOS_ORBIT_RADIUS, PHOBOS_LUNAR_CYCLE, PHOBOS_INCLINATION, texture[PhobosTextureName]);
			createAndDrawMoon(planet, DEIMOS_RADIUS, DEIMOS_ORBIT_RADIUS, DEIMOS_LUNAR_CYCLE, DEIMOS_INCLINATION, texture[DeimosTextureName]);
			break;
		case JUPITER:
			createAndDrawMoon(planet, IO_RADIUS, IO_ORBIT_RADIUS, IO_LUNAR_CYCLE, IO_INCLINATION, texture[IoTextureName]);
			createAndDrawMoon(planet, EUROPA_RADIUS, EUROPA_ORBIT_RADIUS, EUROPA_LUNAR_CYCLE, EUROPA_INCLINATION, texture[EuropaTextureName]);
			createAndDrawMoon(planet, GANYMEDE_RADIUS, GANYMEDE_ORBIT_RADIUS, GANYMEDE_LUNAR_CYCLE, GANYMEDE_INCLINATION, texture[GanymedeTextureName]);
			createAndDrawMoon(planet, CALLISTO_RADIUS, CALLISTO_ORBIT_RADIUS, CALLISTO_LUNAR_CYCLE, CALLISTO_INCLINATION, texture[CallistoTextureName]);
			break;
		case SATURN:
			createAndDrawRings(planet, texture[SaturnRingsTextureName]);
			createAndDrawMoon(planet, TITAN_RADIUS, TITAN_ORBIT_RADIUS, TITAN_LUNAR_CYCLE, TITAN_INCLINATION, texture[TitanTextureName]);
			break;
		case URANUS:
			createAndDrawMoon(planet, TITANIA_RADIUS, TITANIA_ORBIT_RADIUS, TITANIA_LUNAR_CYCLE, TITANIA_INCLINATION, texture[TitaniaTextureName]);
			createAndDrawMoon(planet, OBERON_RADIUS, OBERON_ORBIT_RADIUS, OBERON_LUNAR_CYCLE, OBERON_INCLINATION, texture[OberonTextureName]);
			createAndDrawMoon(planet, UMBRIEL_RADIUS, UMBRIEL_ORBIT_RADIUS, UMBRIEL_LUNAR_CYCLE, UMBRIEL_INCLINATION, texture[UmbrielTextureName]);
			createAndDrawMoon(planet, ARIEL_RADIUS, ARIEL_ORBIT_RADIUS, ARIEL_LUNAR_CYCLE, ARIEL_INCLINATION, texture[ArielTextureName]);
			createAndDrawMoon(planet, MIRANDA_RADIUS, MIRANDA_ORBIT_RADIUS, MIRANDA_LUNAR_CYCLE, MIRANDA_INCLINATION, texture[MirandaTextureName]);
			break;
		case NEPTUNE:
			createAndDrawMoon(planet, TRITON_RADIUS, TRITON_ORBIT_RADIUS, TRITON_LUNAR_CYCLE, TRITON_INCLINATION, texture[TritonTextureName]);
			break;
		case PLUTO:
			createAndDrawMoon(planet, CHARON_RADIUS, CHARON_ORBIT_RADIUS, CHARON_LUNAR_CYCLE, CHARON_INCLINATION, texture[CharonTextureName]);
			break;
		default:
			break;
	}
}

void createAndDrawMoon(GenericPlanet *planet, GLfloat radius, GLfloat orbitRadius, GLfloat lunarCycle, GLfloat inclination, GLuint textureName) {
	Moon *moon = new Moon(planet, radius, orbitRadius, lunarCycle, inclination, textureName);
	moon->drawMoon(EarthDaysPassed, CurrentEarthRotation);
}

void createAndDrawRings(GenericPlanet *planet, GLuint textureName) {
	Rings *rings = new Rings(planet, textureName);
	rings->drawRings(EarthDaysPassed, CurrentEarthRotation);
}

void drawAsteroids() {
	glPushMatrix();
		int slices = 60;
			int count = 0;
			for(int a=0; a<slices; ++a) {
				const float value = (float)a * ((float) PI/(float)slices * (float)a);
				Asteroid *asteroid = new Asteroid(ASTEROID_ORBIT_RADIUS[count], texture[AsteroidTextureName]);
				asteroid->drawAsteroid(EarthDaysPassed, CurrentEarthRotation, value);
				if(count < 21) { count++; } else { count = 0; }
			}
	glPopMatrix();
}

void drawOrbits() {
	glRotatef( -90.0, 1.0, 0.0, 0.0 );
	for (int a = 0; a < 9; a++) {	
		glPushMatrix();
			glRotatef(planetNamesOffsets[a][1], 0.0, -1.0, 0.0);
			glBegin(GL_LINE_LOOP);
				int slices = 400;
				for (int i = 0; i < slices; ++i) {
					const float value = 2 * (float) PI/(float)slices * (float)i;
					glColor3f(1.0f,1.0f,1.0f);
					glVertex3f((SUN_RADIUS_OFFSET + (AU_CONST * planetNamesOffsets[a][0])) * sinf(value), (SUN_RADIUS_OFFSET + (AU_CONST * planetNamesOffsets[a][0])) * cosf(value), 0.0f);
				}
			glEnd();

			const char *c = planetNames[a];
			glRasterPos3f((SUN_RADIUS_OFFSET + (AU_CONST * planetNamesOffsets[a][0])), 0.0, planetNamesOffsets[a][2]);
			for (c; *c != '\0'; c++) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
			}
		glPopMatrix();
	}
}

void drawAsteroidBelt() {
	glPushMatrix();
		for(float a=1.8; a < 4.0; a = a+0.01) {
			glBegin(GL_POINTS);
				int slices = 400;
				for (int i = 0; i < slices; ++i) {
					const float value = 2 * (float) PI/(float)slices * (float)i;
					int random = rand() % 3 + 1;
					glColor3f(1.0f,1.0f,1.0f);
					glVertex3f((SUN_RADIUS_OFFSET + (AU_CONST * a)) * sinf(value), (SUN_RADIUS_OFFSET + (AU_CONST * a)) * cosf(value), (float) random);
				}
			glEnd();
		}
	glPopMatrix();
}

void drawSkybox()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		GLUquadricObj* quadro = gluNewQuadric();							
		gluQuadricNormals(quadro, GLU_SMOOTH);		
		gluQuadricTexture(quadro, GL_TRUE);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPushMatrix();
			glRotatef( -90.0, 1.0, 0.0, 0.0 );
			glBindTexture(GL_TEXTURE_2D, texture[SkyboxTextureName]);
			gluSphere(quadro, SKYBOX_OFFSET + (SUN_RADIUS_OFFSET + (AU_CONST * PLUTO_ORBIT_RADIUS)), 100, 100);
			glCullFace(GL_FRONT);
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quadro);
}

void generateTextures() {
	generateTexture(SUN_IMG, SunTextureName);
	generateTexture(SKYBOX, SkyboxTextureName);
	generateTexture(ASTEROID_IMG, AsteroidTextureName);

	generateTexture(MERCURY_IMG, MercuryTextureName);
	generateTexture(VENUS_IMG, VenusTextureName);
	generateTexture(EARTH_IMG, EarthTextureName);
		generateTexture(MOON_IMG, MoonTextureName);
	generateTexture(MARS_IMG, MarsTextureName);
		generateTexture(PHOBOS_IMG, PhobosTextureName);
		generateTexture(DEIMOS_IMG, DeimosTextureName);
	generateTexture(JUPITER_IMG, JupiterTextureName);
		generateTexture(IO_IMG, IoTextureName);
		generateTexture(EUROPA_IMG, EuropaTextureName);
		generateTexture(GANYMEDE_IMG, GanymedeTextureName);
		generateTexture(CALLISTO_IMG, CallistoTextureName);
	generateTexture(SATURN_IMG, SaturnTextureName);
		generateTexture(TITAN_IMG, TitanTextureName);
		generateTexture(SATURN_RINGS_IMG, SaturnRingsTextureName);
	generateTexture(URANUS_IMG, UranusTextureName);
		generateTexture(TITANIA_IMG, TitaniaTextureName);
		generateTexture(OBERON_IMG, OberonTextureName);
		generateTexture(UMBRIEL_IMG, UmbrielTextureName);
		generateTexture(ARIEL_IMG, ArielTextureName);
		generateTexture(MIRANDA_IMG, MirandaTextureName);
	generateTexture(NEPTUNE_IMG, NeptuneTextureName);
		generateTexture(TRITON_IMG, TritonTextureName);
	generateTexture(PLUTO_IMG, PlutoTextureName);
		generateTexture(CHARON_IMG, CharonTextureName);
}

void generateTexture(const char *imgName, GLuint textureName) {
	texture[textureName] = SOIL_load_OGL_texture(imgName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	
	glBindTexture(GL_TEXTURE_2D, texture[textureName]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

void setLights() {
	glLightfv(GL_LIGHT0, GL_AMBIENT, LIGHT_AMBIENT);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT0_POSITION);
}

void updateLight()
{
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT0_POSITION);
	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

void initWindow(void) {
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL | GLUT_DEPTH );
    glutInitWindowPosition( INIT_WINDOW_POSITION[0], INIT_WINDOW_POSITION[1] );
	glutInitWindowSize( currentWindowSize[0], currentWindowSize[1] );
    glutCreateWindow( "Solar System" );
}

void initLightingShadingDepth(void) {
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_NORMALIZE);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	setLights();

	generateTextures();
}