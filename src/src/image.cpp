#include "../include/image.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#include <math.h>
#include <stdlib.h>

// TAREA: Declarar funciones de stb_image.c
extern "C" unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
extern "C" void stbi_image_free(void *retval_from_stbi_load);

Image::Image(const String &filename, uint16 hframes, uint16 vframes) {
	this->filename = filename;
	this->hframes = hframes;
	this->vframes = vframes;
	width = 0;
	height = 0;
	handlex = 0;
	handley = 0;
	gltex = 0;
	lastU = 1.0;
	lastV = 1.0;

	// TAREA: Cargar el buffer de la imagen
    int image_x    = 0;
    int image_y    = 0;
    int image_comp = 0;
    unsigned char * image_buffer;

    image_buffer = stbi_load(filename.ToCString(), &image_x, &image_y, &image_comp, 4);

    width  = image_x;
    height = image_y;

	// Generamos la textura
	if ( image_buffer ) {
		// TAREA: Generar la textura de OpenGL
        // Paso 1
        glGenTextures(1, &gltex);

        // Paso 2
        Bind();

        // Paso 3
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Paso 4
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_buffer);

        // Paso 5
        stbi_image_free(image_buffer);
	}
}

Image::~Image() {
	glDeleteTextures(1, &gltex);
}

void Image::Bind() const {
	// TAREA: Establecer la textura actual
    glBindTexture(GL_TEXTURE_2D, gltex);
}