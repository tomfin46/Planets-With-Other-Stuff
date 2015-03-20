#include "Planets.h"
#include "SolarSystemConstants.h"

Moon::Moon(GenericPlanet *planet, GLfloat radius, GLfloat orbitRadius, GLfloat lunarCycle, GLfloat inclination, GLuint textureName) {
	this->planet = planet;
	this->radius = radius;
	this->orbitRadius = orbitRadius;	
	this->lunarCycle = lunarCycle;
	this->inclination = inclination;
	this->textureName = textureName;

	this->quadro = gluNewQuadric();							
	gluQuadricNormals(this->quadro, GLU_SMOOTH);		
	gluQuadricTexture(this->quadro, GL_TRUE);
}

void Moon::drawMoon(GLfloat EarthDaysPassed, GLfloat CurrentEarthRotation) {
	GLfloat MoonRevolution = EarthDaysPassed / lunarCycle;
				
	glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glRotatef( planet->getInclination(), 0.0, 0.0, 1.0);
			glRotatef( 360.0 * (EarthDaysPassed/planet->getOrbitDuration()), 0.0, 1.0, 0.0);
			glTranslatef(SUN_RADIUS_OFFSET + (AU_CONST * planet->getOrbitRadius()), 0.0, 0.0 );
			glRotatef(inclination, 0.0, 0.0, 1.0);
			glRotatef( 360.0 * MoonRevolution, 0.0, 1.0, 0.0 );
			glTranslatef( planet->getRadius() + (AU_CONST * orbitRadius), 0.0, 0.0 );
			glBindTexture(GL_TEXTURE_2D, textureName);
			gluSphere(this->quadro, RADIUS_CONST * radius, 48, 48);
		glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(this->quadro);
}