#ifndef SimpleEffect_h
#define SimpleEffect_h

#include "Effect.h"
#include <SOIL.h>

class SimpleEffect: public Effect{
public:
		GLint LoadGLTexture(const char *filename) 
	{
		GLuint _texture;
		_texture = SOIL_load_OGL_texture
		(
		 filename,
		 SOIL_LOAD_AUTO,
		 SOIL_CREATE_NEW_ID,
		 SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT 
		 );
    
		if(_texture == 0) {
			printf( "[ERROR] SOIL loading error: '%s'\n", SOIL_last_result() );
		}

		glBindTexture(GL_TEXTURE_2D, _texture); 
  
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		return _texture;
	}

    SimpleEffect(int* screenWidth, int* screenHeight)
		:Effect("effect_simple.frag",screenWidth, screenHeight)
	{
		UniformOffset = glGetUniformLocation(programID, "offset");
        if (UniformOffset == -1) {
            fprintf(stderr, "Could not bind attribute %s\n", "offset");
        } 

		UniformStex = glGetUniformLocation(programID, "in_texture");
        if (UniformStex == -1) {
            fprintf(stderr, "Could not bind attribute %s\n", "in_texture");
        }

        UniformRamptex = glGetUniformLocation(programID, "ramp_texture");
        if (UniformRamptex == -1) {
            fprintf(stderr, "Could not bind attribute %s\n", "ramp_texture");
        }
    }
    virtual void draw()
	{
        glUseProgram(programID);
		
		//GLfloat move = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 2*3.14159 * .75;  // 3/4 of a wave cycle per second
		//glUniform1f(UniformOffset, move);
		
		glActiveTexture(GL_TEXTURE1); // scene texture active
		LoadGLTexture("red.jpg");	   // bind the texture
        glUniform1i(UniformStex, 1);  // send to shader

		glActiveTexture(GL_TEXTURE2);  // ramp texture for color correction
		LoadGLTexture("ramp_texture.jpg");  // bind the texture
        glUniform1i(UniformRamptex, 2);		// send to shader

		glActiveTexture(GL_TEXTURE0);	// frame buffer object texture, fbo_texture in Effect.h

        Effect::draw();
	}
	private:
	GLuint UniformOffset;
    GLuint UniformStex, UniformRamptex;
};

#endif
