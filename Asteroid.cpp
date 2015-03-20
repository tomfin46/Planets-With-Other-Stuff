#include <math.h>
#include <stdlib.h>

#include "Planets.h"
#include "SolarSystemConstants.h"

Asteroid::Asteroid(GLfloat orbitRadius, GLuint textureName) {
	this->orbitRadius = orbitRadius;
	this->textureName = textureName;

	this->quadro = gluNewQuadric();							
	gluQuadricNormals(this->quadro, GLU_SMOOTH);		
	gluQuadricTexture(this->quadro, GL_TRUE);
}

void Asteroid::drawAsteroid(GLfloat EarthDaysPassed, GLfloat CurrentEarthRotation, int value) {			
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPushMatrix();
			glRotatef( 0.0, 0.0, 0.0, 1.0);
			glRotatef( 360.0 * (EarthDaysPassed/ASTEROID_ORBIT_DUR), 0.0, 1.0, 0.0);
			glTranslatef((SUN_RADIUS_OFFSET + (AU_CONST * this->orbitRadius)) * sinf(value), 0.0f, (SUN_RADIUS_OFFSET + (AU_CONST * this->orbitRadius)) * cosf(value));
			glBindTexture(GL_TEXTURE_2D, textureName);
			gluSphere(this->quadro, RADIUS_CONST * ASTEROID_RADIUS, 48, 48);
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(this->quadro);
}