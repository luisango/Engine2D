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

    // Carga en buffer de la imagen
    image_buffer = stbi_load(filename.ToCString(), &image_x, &image_y, &image_comp, 4);

    // Comprobar que ancho y alto no sea potencia de 2
    while (!(image_x & 1)) // X pot 2?
        image_x = image_x >> 1; 

    while (!(image_y & 1)) // Y pot 2?
        image_y = image_y >> 1; 

    bool is_y_pot = image_y == 1;
    bool is_x_pot = image_x == 1;

    if (is_x_pot || is_y_pot) {
        // hacer el nuevo buffer, el buffer viene con RGBA
        // El tamaño del buffer es W*H*4
        // image_buffer[i]   = R
        // image_buffer[i+1] = G
        // image_buffer[i+2] = B
        // image_buffer[i+3] = A

        // Se recalcula cual es las nuevas coordenadas
        // Unos señores for que rellenen el nuevo buffer y completen los pixeles que faltan

        // memset (nuevoBuffer, 255, nuevoAncho*nuevoAlto*4);
        // Luego copiar la imagen vieja al nuevo buffer
        // ¡Ya lo tienes campeon!
    }

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