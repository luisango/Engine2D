#include "../include/glinclude.h"
#include "../include/font.h"
#include "../include/math.h"
#include "../include/renderer.h"
#include <math.h>
#include <stdlib.h>

extern "C" unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
extern "C" void stbi_image_free(void *retval_from_stbi_load);

Font::Font(const String& filename)
	: Image(filename, 16, 16), glyphs(new Array<Glyph>()) 
{
    int image_x    = 0;
    int image_y    = 0;
    int image_comp = 0;

    unsigned char * image_buffer;

    // Carga en buffer de la imagen
    image_buffer = stbi_load(filename.ToCString(), &image_x, &image_y, &image_comp, 4);

    for (int actual_glyph = 0; actual_glyph < 256; actual_glyph++)
    {
        int column = actual_glyph % 16;
        int row    = actual_glyph / 16;

        Glyph g(image_x / 16, image_y / 16, row, column, image_buffer);
        glyphs->Add(g);
    }

    if (image_buffer) {
		// TAREA: Generar la textura de OpenGL
        // Paso 1
        glGenTextures(1, &gltex);

        // Paso 2
        Bind();

        // Paso 3
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Paso 4
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_x, image_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_buffer);

        // Paso 5
        stbi_image_free(image_buffer);
	}
}

uint32 Font::GetTextWidth(const String& text) const
{
	int string_length = text.Length();
	uint32 width = 0;

	for (int i = 0; i < string_length; i++)
	{
		width += (*glyphs)[text[i]].GetWidth();
	}

	return width;
}

uint32 Font::GetTextHeight(const String& text) const 
{ 
    int string_length = text.Length();
	uint32 height = 0;

	for (int i = 0; i < string_length; i++)
	{
		uint32 actual_height = (*glyphs)[text[i]].GetHeight();

		if (actual_height > height)
			height = actual_height;
	}

	return height;
}

void Font::Render(const String& text, double x, double y) const
{
    int text_length = text.Length();
    int char_offset = 0;

    for (int char_position = 0; char_position < text_length; char_position++) 
    {
        Renderer::Instance().DrawImage(
		    this,                                // Image
            x + char_offset, y,                  // Position
		    (unsigned char) text[char_position], // Character
			GetWidth(),                          // Width 
			GetHeight(),                         // Height
		    0                                    // Angle
	    );

        char_offset += (*glyphs)[text[char_position]].GetWidth();
    }
}