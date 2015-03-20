#include <math.h>

#include "Planets.h"
#include "SolarSystemConstants.h"

GenericPlanet::GenericPlanet(GLuint planetName, GLfloat radius, GLfloat orbitRadius, 
			GLfloat orbitDuration, GLfloat rotationDuration,
				GLfloat inclination, GLuint textureName) {
					this->planetName = planetName;
					this->radius = radius;
					this->orbitRadius = orbitRadius;
					this->orbitDuration = orbitDuration;
					this->rotationDuration = rotationDuration;
					this->inclination = inclination;
					this->textureName = textureName;

					this->quadro = gluNewQuadric();							
					gluQuadricNormals(this->quadro, GLU_SMOOTH);		
					gluQuadricTexture(this->quadro, GL_TRUE);
}

void GenericPlanet :: drawPlanet(GLfloat EarthDaysPassed, GLfloat CurrentEarthRotation) {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPushMatrix();
			glRotatef( inclination, 0.0, 0.0, 1.0);
			glRotatef( 360.0 * (EarthDaysPassed/orbitDuration), 0.0, 1.0, 0.0);
			glTranslatef(SUN_RADIUS_OFFSET + (AU_CONST * orbitRadius), 0.0, 0.0 );
			glRotatef( 360.0 * (CurrentEarthRotation/rotationDuration), 0.0, 1.0, 0.0 );
			glRotatef( -90.0, 1.0, 0.0, 0.0 );
			glBindTexture(GL_TEXTURE_2D, textureName);
			gluSphere(this->quadro, RADIUS_CONST * radius, 48, 48);
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(this->quadro);
}

GLfloat GenericPlanet::getOrbitDuration() {
	return this->orbitDuration;
}

GLfloat GenericPlanet::getOrbitRadius() {
	return this->orbitRadius;
}

GLfloat GenericPlanet::getRadius() {
	return this->radius;
}

GLfloat GenericPlanet::getInclination() {
	return this->inclination;
}

GLfloat GenericPlanet::getRotationDuration() {
	return this->rotationDuration;
}