#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#include <txt.h>

#define FONT_CFG_FILE "font.cfg"
#define MAX_FONT_NAME_LENGTH 120
#define MAX_GLYPH_DIGIT_LENGTH 4
#define GLYPH_TABLE_SIZE 178
#define MAX_ERR_MSG_SIZE 80

typedef struct 
{
    int w;
    int h;
    int glyph_w;
    int glyph_h;

} atlas_data_t;

internal u32 *atlas[MAX_BITMAP_FONTS];
internal atlas_data_t data[MAX_BITMAP_FONTS];
internal u32 magic_pink;

internal enum BitmapFont default_font;
internal int fonts_loaded;

internal int keys[GLYPH_TABLE_SIZE];
internal int glyph_positions[GLYPH_TABLE_SIZE];
internal int glyphs_added;

internal BOOL TXT_initialized;

internal unsigned Hash(char key)
{
    double m = 0.5*(sqrt(5)-1);
}
