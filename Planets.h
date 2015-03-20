#include "glut.h"

class GenericPlanet {

	private:
		GLuint planetName; 
		GLfloat radius;
		GLfloat orbitRadius;
		GLfloat orbitDuration;
		GLfloat rotationDuration;
		GLfloat inclination;
		GLuint textureName;

		GLUquadricObj* quadro;

	public:
		GenericPlanet(void) {
			radius = 0.18;
			orbitDuration = 365;
			orbitRadius = 3.0;
		}

		GenericPlanet(GLuint planetName, GLfloat radius, GLfloat orbitRadius, 
			GLfloat orbitDuration, GLfloat rotationDuration,
				GLfloat inclination, GLuint textureName);
		~GenericPlanet(void);
		void drawPlanet(GLfloat EarthDaysPassed, GLfloat CurrentEarthRotation);
		GLfloat getOrbitDuration(void);
		GLfloat getOrbitRadius(void);
		GLfloat getRadius(void);
		GLfloat getInclination(void);
		GLfloat getRotationDuration(void);
};

class Moon {
	private:
		GenericPlanet *planet;
		GLfloat radius;
		GLfloat orbitRadius;
		GLfloat lunarCycle;
		GLfloat inclination;
		GLuint textureName;

		GLUquadricObj* quadro;
	public:
		Moon(GenericPlanet *planet, GLfloat radius, GLfloat orbitRadius, GLfloat lunarCycle, GLfloat inclination, GLuint textureName);
		~Moon(void);
		void drawMoon(GLfloat EarthDaysPassed, GLfloat CurrentEarthRotation);
};

class Sun {
	private:
		GLfloat radius;
		GLuint textureName;

		GLUquadricObj* quadro;

	public:
		Sun(GLfloat radius, GLuint textureName);
		~Sun(void);
		void drawSun(void);
};

class Rings {
	private:
		GenericPlanet *planet;
		GLuint textureName;

		GLUquadricObj* quadro;

	public:
		Rings(GenericPlanet *planet, GLuint textureName);
		~Rings(void);
		void drawRings(GLfloat EarthDaysPassed, GLfloat CurrentEarthRotation);
};

class Asteroid {
	private:
		GLfloat orbitRadius;
		GLuint textureName;
		GLUquadricObj* quadro;

	public:
		Asteroid(GLfloat orbitRadius, GLuint textureName);
		void drawAsteroid(GLfloat EarthDaysPassed, GLfloat CurrentEarthRotation, int value);
};