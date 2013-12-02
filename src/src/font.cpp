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

    stbi_image_free(image_buffer);
}

uint32 Font::GetTextWidth(const String& text) const
{
	int glyphs_size   = glyphs->Size();
	int string_length = text.Length();

	if (glyphs_size != 0) {
		uint32 size = 0;

		for (int i = 0; i < string_length; i++)
		{
			size += (*glyphs)[text[i]].GetEndX() - (*glyphs)[text[i]].GetBeginX();
		}

		return size;
	}

	return GetWidth() * text.Length();
}

uint32 Font::GetTextHeight(const String& text) const 
{ 
    return GetHeight(); 
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
		    16, 16,                              // Width
		    0                                    // Angle
	    );

        char_offset += GetWidth();
    }
}