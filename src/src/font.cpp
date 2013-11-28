#include "../include/font.h"
#include "../include/math.h"
#include "../include/renderer.h"
#include <math.h>
#include <stdlib.h>

uint32 Font::GetTextWidth(const String& text) const
{
    return GetSize() * text.Length();
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
        char c = text[char_position];
        Renderer::Instance().DrawImage(
		    this,                // Image
            x + char_offset, y,  // Position
		    c,                   // Character
		    16, 16,                // Width
		    0                    // Angle
	    );

        char_offset += GetWidth();
    }
}