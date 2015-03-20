#include <math.h>

#include "Planets.h"
#include "SolarSystemConstants.h"

Sun::Sun(GLfloat radius, GLuint textureName) {
	this->radius = radius;
	this->textureName = textureName;

	this->quadro = gluNewQuadric();							
	gluQuadricNormals(this->quadro, GLU_SMOOTH);		
	gluQuadricTexture(this->quadro, GL_TRUE);
}

void Sun::drawSun() {
	glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glPushMatrix();
				glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, LIGHT_EMISSION);

				glRotatef( -90.0, 1.0, 0.0, 0.0 );
				glBindTexture(GL_TEXTURE_2D, textureName);
				gluSphere(this->quadro, radius, 48, 48);

				glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, DEFAULT_EMISSION);
			glPopMatrix();
		glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(this->quadro);
}