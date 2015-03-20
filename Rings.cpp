#include "Planets.h"
#include "SolarSystemConstants.h"

Rings::Rings(GenericPlanet *planet, GLuint textureName) {
	this->planet = planet;
	this->textureName = textureName;

	this->quadro = gluNewQuadric();							
	gluQuadricNormals(this->quadro, GLU_SMOOTH);		
	gluQuadricTexture(this->quadro, GL_TRUE);
}

void Rings::drawRings(GLfloat EarthDaysPassed, GLfloat CurrentEarthRotation) {			
	glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glPushMatrix();
				glRotatef(planet->getInclination(), 0.0, 0.0, 1.0);
				glRotatef( 360.0 * (EarthDaysPassed/planet->getOrbitDuration()), 0.0, 1.0, 0.0);
				glTranslatef(SUN_RADIUS_OFFSET + (AU_CONST * planet->getOrbitRadius()), 0.0, 0.0 );
				glRotatef( 360.0 * (CurrentEarthRotation/planet->getRotationDuration()), 0.0, 1.0, 0.0 );
				glRotatef( -90.0, 1.0, 0.0, 0.0 );
				glBindTexture(GL_TEXTURE_2D, textureName);
				glScalef(1,1,.02);
				gluSphere(this->quadro, RADIUS_CONST * (planet->getRadius()*2), 48, 48);
			glPopMatrix();
		glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(this->quadro);
}