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

    uint32 new_width  = 0;  
    uint32 new_height = 0;

    bool needs_to_be_scaled = false;

    unsigned char * image_buffer;
    unsigned char * image_scaled_buffer;
    unsigned char * image_no_scaled_buffer;

    // Carga en buffer de la imagen
    image_no_scaled_buffer = stbi_load(filename.ToCString(), &image_x, &image_y, &image_comp, 4);

    width  = image_x;
    height = image_y;

    // Comprobar que ancho y alto no sea potencia de 2
    while (!(image_x & 1)) // X pot 2?
        image_x = image_x >> 1; 

    while (!(image_y & 1)) // Y pot 2?
        image_y = image_y >> 1; 

    bool is_y_pot = image_y == 1;
    bool is_x_pot = image_x == 1;

    if (!is_x_pot || !is_y_pot) {
        needs_to_be_scaled = true;

        new_width  = pow(2, ceil(Log2(width)));
        new_height = pow(2, ceil(Log2(height)));

        uint64 new_image_size = new_width * new_height * 4;
        uint64 old_image_size = width * height * 4;

        image_scaled_buffer = new unsigned char[new_image_size];
        memset(image_scaled_buffer, 0, new_image_size);

        for (uint32 y = 0; y < height; y++)
            for (uint32 x = 0; x < width; x++) 
                for (uint8 c = 0; c < 4; c++)
                    image_scaled_buffer[(y*new_width+x) * 4 + c] = image_no_scaled_buffer[(y*width+x) * 4 + c];

        image_buffer = image_scaled_buffer;

        // Cambiar las coordenadas de textura
        lastU = width*lastU/new_width;
	    lastV = height*lastV/new_height;
    } else {
        image_buffer = image_no_scaled_buffer;
    }

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
        if (needs_to_be_scaled)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, new_width, new_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_buffer);
        else
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