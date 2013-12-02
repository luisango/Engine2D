#include "../include/font.h"
#include "../include/math.h"
#include "../include/renderer.h"
#include <math.h>
#include <stdlib.h>

Font::Font(const String& filename)
	: Image(filename, 16, 16), glyphs(new Array<Glyph>()) 
{
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
		    this,                // Image
            x + char_offset, y,  // Position
		    text[char_position], // Character
		    16, 16,              // Width
		    0                    // Angle
	    );

        char_offset += GetWidth();
    }
}