/*******************************************************************************
 * Size: 16 px
 * Bpp: 4
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef FIRACODE_REGULAR_16
#define FIRACODE_REGULAR_16 1
#endif

#if FIRACODE_REGULAR_16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0xe, 0xa0, 0xd, 0xa0, 0xd, 0x90, 0xd, 0x90,
    0xc, 0x90, 0xc, 0x80, 0xb, 0x80, 0x8, 0x50,
    0x0, 0x0, 0x1, 0x10, 0x1f, 0xe0, 0xd, 0xb0,

    /* U+0022 "\"" */
    0x4f, 0x68, 0xf2, 0x3f, 0x57, 0xf1, 0x2f, 0x46,
    0xf0, 0x1f, 0x35, 0xf0, 0x5, 0x1, 0x50,

    /* U+0023 "#" */
    0x0, 0xc, 0x60, 0x3f, 0x0, 0x0, 0xd4, 0x5,
    0xd0, 0x0, 0xf, 0x20, 0x7b, 0x0, 0x8f, 0xff,
    0xff, 0xff, 0x0, 0x5e, 0x11, 0xb8, 0x10, 0x5,
    0xc0, 0xc, 0x50, 0x0, 0x7a, 0x0, 0xf3, 0x0,
    0x9, 0x80, 0x1f, 0x10, 0x1f, 0xff, 0xff, 0xff,
    0x50, 0x2e, 0x62, 0x6d, 0x20, 0x0, 0xf2, 0x7,
    0xb0, 0x0, 0x2f, 0x0, 0x99, 0x0,

    /* U+0024 "$" */
    0x0, 0x3, 0x50, 0x0, 0x0, 0x7, 0xa0, 0x0,
    0x0, 0x7, 0xa0, 0x0, 0x2, 0xbf, 0xfc, 0x60,
    0x1e, 0xca, 0xc7, 0xf6, 0x6f, 0x17, 0xa0, 0x10,
    0x5f, 0x27, 0xa0, 0x0, 0xd, 0xda, 0xa0, 0x0,
    0x1, 0xaf, 0xf8, 0x10, 0x0, 0x7, 0xee, 0xe1,
    0x0, 0x7, 0xa1, 0xf9, 0x0, 0x7, 0xa0, 0xbc,
    0x22, 0x7, 0xa0, 0xda, 0x9e, 0x78, 0xca, 0xf3,
    0x7, 0xdf, 0xfc, 0x40, 0x0, 0x7, 0xa0, 0x0,
    0x0, 0x7, 0xa0, 0x0, 0x0, 0x3, 0x50, 0x0,

    /* U+0025 "%" */
    0x9, 0xfd, 0x30, 0x1, 0xb0, 0x6e, 0x18, 0xc0,
    0xa, 0x90, 0xa9, 0x2, 0xf1, 0x5e, 0x0, 0xa9,
    0x3, 0xf2, 0xe4, 0x0, 0x5e, 0x18, 0xca, 0x90,
    0x0, 0x9, 0xfd, 0x8d, 0x0, 0x0, 0x0, 0x1,
    0xe4, 0x0, 0x0, 0x0, 0xb, 0x94, 0xef, 0x90,
    0x0, 0x5d, 0x2f, 0x51, 0xe5, 0x1, 0xe3, 0x3f,
    0x0, 0xb8, 0xb, 0x80, 0x1f, 0x51, 0xe5, 0x3d,
    0x0, 0x4, 0xef, 0x90, 0x0, 0x0, 0x0, 0x0,
    0x0,

    /* U+0026 "&" */
    0x0, 0x4c, 0xfd, 0x60, 0x0, 0x2, 0xf7, 0x14,
    0xd1, 0x0, 0x7, 0xe0, 0x0, 0x0, 0x0, 0x6,
    0xe0, 0x0, 0x0, 0x0, 0x1, 0xe9, 0x0, 0x0,
    0x0, 0x0, 0x3e, 0xff, 0xff, 0xf6, 0x4, 0xe7,
    0x22, 0x6f, 0x20, 0xe, 0x80, 0x0, 0x5f, 0x0,
    0x1f, 0x40, 0x0, 0x5f, 0x0, 0xf, 0x70, 0x0,
    0x5f, 0x0, 0x9, 0xf5, 0x24, 0xcc, 0x0, 0x0,
    0x8d, 0xfe, 0x91, 0x0,

    /* U+0027 "'" */
    0xec, 0xdb, 0xca, 0xb9, 0x43,

    /* U+0028 "(" */
    0x0, 0x0, 0x0, 0x0, 0x5b, 0x0, 0x5f, 0x40,
    0x3f, 0x50, 0xd, 0xa0, 0x4, 0xf2, 0x0, 0x9d,
    0x0, 0xd, 0x90, 0x0, 0xe8, 0x0, 0xe, 0x80,
    0x0, 0xd9, 0x0, 0xb, 0xb0, 0x0, 0x6f, 0x0,
    0x0, 0xf7, 0x0, 0x6, 0xf2, 0x0, 0x9, 0xd1,
    0x0, 0xa, 0xb0, 0x0, 0x1,

    /* U+0029 ")" */
    0x0, 0x0, 0x0, 0xc, 0x30, 0x0, 0x6, 0xf3,
    0x0, 0x0, 0x7e, 0x10, 0x0, 0xc, 0xa0, 0x0,
    0x5, 0xf2, 0x0, 0x0, 0xf7, 0x0, 0x0, 0xca,
    0x0, 0x0, 0xac, 0x0, 0x0, 0xac, 0x0, 0x0,
    0xbb, 0x0, 0x0, 0xe8, 0x0, 0x2, 0xf4, 0x0,
    0x9, 0xd0, 0x0, 0x4f, 0x30, 0x2, 0xe7, 0x0,
    0xe, 0x70, 0x0, 0x1, 0x0, 0x0,

    /* U+002A "*" */
    0x0, 0x0, 0xc9, 0x0, 0x0, 0x0, 0x0, 0xb9,
    0x0, 0x0, 0x9, 0x40, 0xb8, 0x5, 0x70, 0x1c,
    0xfe, 0xed, 0xff, 0xb0, 0x0, 0x17, 0xff, 0x61,
    0x0, 0x0, 0xc, 0xbd, 0x90, 0x0, 0x0, 0x8f,
    0x13, 0xf5, 0x0, 0x0, 0x96, 0x0, 0x87, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0,

    /* U+002B "+" */
    0x0, 0xb, 0x80, 0x0, 0x0, 0xb, 0x80, 0x0,
    0x0, 0xb, 0x80, 0x0, 0xef, 0xff, 0xff, 0xfc,
    0x22, 0x2c, 0x92, 0x22, 0x0, 0xb, 0x80, 0x0,
    0x0, 0xb, 0x80, 0x0, 0x0, 0x9, 0x70, 0x0,

    /* U+002C "," */
    0xa, 0x80, 0x5f, 0xf3, 0x1f, 0xf1, 0xf, 0xa0,
    0x4f, 0x40, 0x8d, 0x0,

    /* U+002D "-" */
    0x0, 0x0, 0x0, 0x0, 0x5f, 0xff, 0xff, 0xf3,
    0x13, 0x33, 0x33, 0x30,

    /* U+002E "." */
    0x2d, 0xc0, 0x7f, 0xf4, 0x2e, 0xd1,

    /* U+002F "/" */
    0x0, 0x0, 0x0, 0x2, 0x30, 0x0, 0x0, 0x0,
    0x9c, 0x0, 0x0, 0x0, 0x1f, 0x40, 0x0, 0x0,
    0x9, 0xc0, 0x0, 0x0, 0x1, 0xf5, 0x0, 0x0,
    0x0, 0x8d, 0x0, 0x0, 0x0, 0xe, 0x50, 0x0,
    0x0, 0x7, 0xe0, 0x0, 0x0, 0x0, 0xe6, 0x0,
    0x0, 0x0, 0x6e, 0x0, 0x0, 0x0, 0xe, 0x70,
    0x0, 0x0, 0x5, 0xe0, 0x0, 0x0, 0x0, 0xd8,
    0x0, 0x0, 0x0, 0x5f, 0x10, 0x0, 0x0, 0xc,
    0x90, 0x0, 0x0, 0x0, 0x81, 0x0, 0x0, 0x0,

    /* U+0030 "0" */
    0x1, 0xaf, 0xe9, 0x0, 0xc, 0xd3, 0x4e, 0x90,
    0x4f, 0x30, 0xd, 0xf1, 0x8e, 0x0, 0x5a, 0xf6,
    0xbc, 0x0, 0xd2, 0xe8, 0xcb, 0x5, 0xa0, 0xd9,
    0xcb, 0xc, 0x20, 0xd9, 0xbc, 0x4a, 0x0, 0xe8,
    0x8e, 0xc3, 0x0, 0xf6, 0x4f, 0xb0, 0x5, 0xf1,
    0xc, 0xc3, 0x4e, 0x90, 0x1, 0xaf, 0xe9, 0x0,

    /* U+0031 "1" */
    0x0, 0x1b, 0xf2, 0x0, 0x6, 0xfd, 0xf2, 0x0,
    0x3f, 0x64, 0xf2, 0x0, 0x1, 0x4, 0xf2, 0x0,
    0x0, 0x4, 0xf2, 0x0, 0x0, 0x4, 0xf2, 0x0,
    0x0, 0x4, 0xf2, 0x0, 0x0, 0x4, 0xf2, 0x0,
    0x0, 0x4, 0xf2, 0x0, 0x0, 0x4, 0xf2, 0x0,
    0x2, 0x25, 0xf3, 0x21, 0xf, 0xff, 0xff, 0xf8,

    /* U+0032 "2" */
    0x1, 0x9e, 0xfd, 0x50, 0x0, 0xcc, 0x43, 0x8f,
    0x40, 0x2, 0x0, 0x0, 0xcb, 0x0, 0x0, 0x0,
    0xa, 0xc0, 0x0, 0x0, 0x0, 0xda, 0x0, 0x0,
    0x0, 0x3f, 0x40, 0x0, 0x0, 0xd, 0xb0, 0x0,
    0x0, 0xa, 0xd1, 0x0, 0x0, 0x8, 0xe2, 0x0,
    0x0, 0x7, 0xe2, 0x0, 0x0, 0x7, 0xf5, 0x33,
    0x33, 0x0, 0xcf, 0xff, 0xff, 0xf0,

    /* U+0033 "3" */
    0x1, 0x8e, 0xfd, 0x60, 0x0, 0x8c, 0x42, 0x7f,
    0x70, 0x0, 0x0, 0x0, 0xad, 0x0, 0x0, 0x0,
    0x9, 0xc0, 0x0, 0x0, 0x5, 0xe3, 0x0, 0x0,
    0x6f, 0xf7, 0x0, 0x0, 0x1, 0x25, 0xe8, 0x0,
    0x0, 0x0, 0x5, 0xf1, 0x0, 0x0, 0x0, 0x3f,
    0x30, 0x10, 0x0, 0x7, 0xf1, 0xd, 0xb4, 0x37,
    0xf8, 0x0, 0x2a, 0xef, 0xd6, 0x0,

    /* U+0034 "4" */
    0x0, 0x6, 0x30, 0x0, 0x0, 0xf, 0x50, 0x0,
    0x0, 0x6e, 0x0, 0x0, 0x0, 0xd8, 0x0, 0x0,
    0x4, 0xf1, 0x2, 0x0, 0xb, 0xb0, 0xf, 0x30,
    0x2f, 0x40, 0xf, 0x30, 0x8d, 0x0, 0x1f, 0x30,
    0xcf, 0xff, 0xff, 0xfa, 0x22, 0x22, 0x4f, 0x51,
    0x0, 0x0, 0x1f, 0x30, 0x0, 0x0, 0x1f, 0x30,

    /* U+0035 "5" */
    0xf, 0xff, 0xff, 0xe0, 0xf, 0x62, 0x22, 0x10,
    0xf, 0x50, 0x0, 0x0, 0xf, 0x50, 0x0, 0x0,
    0xf, 0x50, 0x0, 0x0, 0xf, 0xbd, 0xeb, 0x20,
    0x7, 0x63, 0x4c, 0xd0, 0x0, 0x0, 0x3, 0xf3,
    0x0, 0x0, 0x1, 0xf5, 0x0, 0x0, 0x5, 0xf2,
    0x6d, 0x53, 0x5e, 0xb0, 0x8, 0xdf, 0xe8, 0x0,

    /* U+0036 "6" */
    0x0, 0x5d, 0xfd, 0x50, 0x6, 0xf6, 0x25, 0x30,
    0xe, 0x60, 0x0, 0x0, 0x5f, 0x0, 0x0, 0x0,
    0x8d, 0x4d, 0xfc, 0x30, 0xae, 0xc4, 0x3a, 0xe1,
    0xbe, 0x10, 0x0, 0xf7, 0xab, 0x0, 0x0, 0xd9,
    0x8d, 0x0, 0x0, 0xd8, 0x4f, 0x10, 0x1, 0xf5,
    0xc, 0xc3, 0x3c, 0xc0, 0x1, 0xae, 0xfa, 0x10,

    /* U+0037 "7" */
    0x6f, 0xff, 0xff, 0xf4, 0x12, 0x22, 0x26, 0xf1,
    0x0, 0x0, 0xa, 0xa0, 0x0, 0x0, 0x1f, 0x40,
    0x0, 0x0, 0x8d, 0x0, 0x0, 0x0, 0xe6, 0x0,
    0x0, 0x6, 0xe0, 0x0, 0x0, 0xd, 0x80, 0x0,
    0x0, 0x4f, 0x20, 0x0, 0x0, 0xbb, 0x0, 0x0,
    0x2, 0xf4, 0x0, 0x0, 0x2, 0x80, 0x0, 0x0,

    /* U+0038 "8" */
    0x2, 0xae, 0xea, 0x20, 0x1e, 0xa2, 0x3b, 0xd0,
    0x6f, 0x0, 0x2, 0xf3, 0x6f, 0x0, 0x2, 0xf3,
    0x1f, 0xa1, 0xa, 0xa0, 0x3, 0xef, 0xeb, 0x0,
    0x1c, 0xa3, 0x9f, 0xb0, 0x9d, 0x0, 0x2, 0xf7,
    0xe9, 0x0, 0x0, 0xbb, 0xcb, 0x0, 0x0, 0xda,
    0x5f, 0x72, 0x3a, 0xf3, 0x5, 0xcf, 0xfb, 0x30,

    /* U+0039 "9" */
    0x4, 0xcf, 0xe9, 0x0, 0x4f, 0x83, 0x5e, 0x90,
    0xbb, 0x0, 0x5, 0xf1, 0xe8, 0x0, 0x1, 0xf4,
    0xca, 0x0, 0x1, 0xf6, 0x7f, 0x40, 0x2c, 0xf6,
    0x9, 0xff, 0xe5, 0xf4, 0x0, 0x1, 0x6, 0xf1,
    0x0, 0x0, 0x1e, 0x90, 0x0, 0x4, 0xed, 0x10,
    0x6, 0xdf, 0x80, 0x0, 0x7, 0x61, 0x0, 0x0,

    /* U+003A ":" */
    0x2e, 0xc0, 0x5f, 0xf3, 0x9, 0x80, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x9, 0x70, 0x5f, 0xf3,
    0x2e, 0xc0,

    /* U+003B ";" */
    0x2e, 0xc0, 0x5f, 0xf3, 0x9, 0x80, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x2e, 0xc0, 0x5f, 0xf3,
    0xf, 0xf0, 0x1f, 0x90, 0x5f, 0x20, 0x79, 0x0,

    /* U+003C "<" */
    0x0, 0x0, 0x2, 0xb1, 0x0, 0x0, 0x8f, 0xb1,
    0x0, 0x4d, 0xe5, 0x0, 0x1a, 0xf9, 0x10, 0x0,
    0x8e, 0x30, 0x0, 0x0, 0x5f, 0xa1, 0x0, 0x0,
    0x2, 0xcf, 0x60, 0x0, 0x0, 0x6, 0xfc, 0x20,
    0x0, 0x0, 0x1b, 0xf2, 0x0, 0x0, 0x0, 0x30,

    /* U+003D "=" */
    0x4f, 0xff, 0xff, 0xf1, 0x3, 0x33, 0x33, 0x30,
    0x0, 0x0, 0x0, 0x0, 0x4f, 0xff, 0xff, 0xf1,
    0x3, 0x33, 0x33, 0x30,

    /* U+003E ">" */
    0x2a, 0x10, 0x0, 0x0, 0x2c, 0xf6, 0x0, 0x0,
    0x0, 0x6f, 0xc3, 0x0, 0x0, 0x1, 0xaf, 0x80,
    0x0, 0x0, 0x5, 0xf6, 0x0, 0x0, 0x2c, 0xf4,
    0x0, 0x8, 0xfb, 0x10, 0x4, 0xde, 0x50, 0x0,
    0x4f, 0x91, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0,

    /* U+003F "?" */
    0x4, 0xbf, 0xea, 0x10, 0x3f, 0x83, 0x4d, 0xc0,
    0x2, 0x0, 0x5, 0xf1, 0x0, 0x0, 0x8, 0xf0,
    0x0, 0x0, 0x8f, 0x50, 0x0, 0x8, 0xf4, 0x0,
    0x0, 0x1f, 0x60, 0x0, 0x0, 0x2f, 0x30, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0,
    0x0, 0x6f, 0x80, 0x0, 0x0, 0x4f, 0x60, 0x0,

    /* U+0040 "@" */
    0x2, 0x9d, 0xfe, 0xb3, 0x0, 0x6f, 0xb5, 0x35,
    0xbf, 0x30, 0x34, 0x0, 0x0, 0xb, 0xd0, 0x0,
    0x0, 0x0, 0x4, 0xf2, 0x2, 0xae, 0xd8, 0x0,
    0xf6, 0xd, 0xa2, 0x6f, 0x0, 0xe8, 0x4f, 0x10,
    0x3f, 0x0, 0xd9, 0x7e, 0x0, 0x3f, 0x0, 0xc9,
    0x7d, 0x0, 0x3f, 0x0, 0xd9, 0x6e, 0x0, 0x3f,
    0x0, 0xd7, 0x2f, 0x40, 0xbe, 0x0, 0xf5, 0x8,
    0xff, 0x78, 0x63, 0xf2, 0x0, 0x0, 0x1, 0xef,
    0x90, 0x0, 0x0, 0x0, 0x1, 0x0,

    /* U+0041 "A" */
    0x0, 0x2, 0xff, 0x0, 0x0, 0x0, 0x7, 0xef,
    0x40, 0x0, 0x0, 0xc, 0x8c, 0x90, 0x0, 0x0,
    0x1f, 0x48, 0xe0, 0x0, 0x0, 0x5f, 0x3, 0xf3,
    0x0, 0x0, 0xab, 0x0, 0xe8, 0x0, 0x0, 0xf6,
    0x0, 0xad, 0x0, 0x4, 0xf2, 0x0, 0x6f, 0x20,
    0x9, 0xff, 0xff, 0xff, 0x70, 0xe, 0x93, 0x33,
    0x3c, 0xb0, 0x3f, 0x30, 0x0, 0x7, 0xf1, 0x8e,
    0x0, 0x0, 0x2, 0xf5,

    /* U+0042 "B" */
    0x6f, 0xff, 0xe9, 0x10, 0x6f, 0x22, 0x4c, 0xd0,
    0x6f, 0x0, 0x3, 0xf4, 0x6f, 0x0, 0x2, 0xf4,
    0x6f, 0x0, 0x1a, 0xc0, 0x6f, 0xff, 0xfc, 0x10,
    0x6f, 0x33, 0x4a, 0xe3, 0x6f, 0x0, 0x0, 0xdb,
    0x6f, 0x0, 0x0, 0xad, 0x6f, 0x0, 0x0, 0xdb,
    0x6f, 0x33, 0x4a, 0xf4, 0x6f, 0xff, 0xea, 0x30,

    /* U+0043 "C" */
    0x0, 0x4c, 0xff, 0xc4, 0x0, 0x7f, 0x94, 0x48,
    0xc0, 0x2f, 0x70, 0x0, 0x0, 0x9, 0xe0, 0x0,
    0x0, 0x0, 0xda, 0x0, 0x0, 0x0, 0xe, 0x80,
    0x0, 0x0, 0x0, 0xe8, 0x0, 0x0, 0x0, 0xd,
    0xa0, 0x0, 0x0, 0x0, 0x9e, 0x0, 0x0, 0x0,
    0x2, 0xf6, 0x0, 0x0, 0x0, 0x7, 0xf9, 0x44,
    0x9e, 0x10, 0x4, 0xcf, 0xfc, 0x50,

    /* U+0044 "D" */
    0xaf, 0xfe, 0xc7, 0x0, 0xa, 0xd3, 0x37, 0xeb,
    0x0, 0xac, 0x0, 0x3, 0xf6, 0xa, 0xc0, 0x0,
    0xc, 0xc0, 0xac, 0x0, 0x0, 0x8f, 0xa, 0xc0,
    0x0, 0x7, 0xf0, 0xac, 0x0, 0x0, 0x7f, 0xa,
    0xc0, 0x0, 0x9, 0xf0, 0xac, 0x0, 0x0, 0xcb,
    0xa, 0xc0, 0x0, 0x4f, 0x50, 0xad, 0x23, 0x7f,
    0xa0, 0xa, 0xff, 0xec, 0x60, 0x0,

    /* U+0045 "E" */
    0xff, 0xff, 0xff, 0x6f, 0x93, 0x33, 0x30, 0xf7,
    0x0, 0x0, 0xf, 0x70, 0x0, 0x0, 0xf7, 0x0,
    0x0, 0xf, 0x70, 0x0, 0x0, 0xff, 0xff, 0xfa,
    0xf, 0x93, 0x33, 0x20, 0xf7, 0x0, 0x0, 0xf,
    0x70, 0x0, 0x0, 0xf9, 0x22, 0x22, 0x1f, 0xff,
    0xff, 0xfa,

    /* U+0046 "F" */
    0xbf, 0xff, 0xff, 0xdb, 0xb3, 0x33, 0x32, 0xbb,
    0x0, 0x0, 0xb, 0xb0, 0x0, 0x0, 0xbb, 0x0,
    0x0, 0xb, 0xb0, 0x0, 0x0, 0xbf, 0xff, 0xff,
    0x1b, 0xb2, 0x22, 0x20, 0xbb, 0x0, 0x0, 0xb,
    0xb0, 0x0, 0x0, 0xbb, 0x0, 0x0, 0xb, 0xb0,
    0x0, 0x0,

    /* U+0047 "G" */
    0x0, 0x7, 0xdf, 0xe8, 0x0, 0xb, 0xe6, 0x46,
    0xe7, 0x7, 0xf2, 0x0, 0x1, 0x0, 0xea, 0x0,
    0x0, 0x0, 0x1f, 0x60, 0x0, 0x0, 0x3, 0xf4,
    0x0, 0x0, 0x0, 0x3f, 0x40, 0xe, 0xff, 0xd2,
    0xf5, 0x0, 0x23, 0xad, 0xf, 0x80, 0x0, 0x9,
    0xd0, 0x9e, 0x10, 0x0, 0x9d, 0x1, 0xec, 0x54,
    0x6d, 0xd0, 0x2, 0xae, 0xfd, 0x92,

    /* U+0048 "H" */
    0xac, 0x0, 0x0, 0xf7, 0xac, 0x0, 0x0, 0xf7,
    0xac, 0x0, 0x0, 0xf7, 0xac, 0x0, 0x0, 0xf7,
    0xac, 0x0, 0x0, 0xf7, 0xaf, 0xff, 0xff, 0xf7,
    0xad, 0x33, 0x33, 0xf7, 0xac, 0x0, 0x0, 0xf7,
    0xac, 0x0, 0x0, 0xf7, 0xac, 0x0, 0x0, 0xf7,
    0xac, 0x0, 0x0, 0xf7, 0xac, 0x0, 0x0, 0xf7,

    /* U+0049 "I" */
    0x5f, 0xff, 0xff, 0xf2, 0x2, 0x2d, 0xb2, 0x20,
    0x0, 0xc, 0xa0, 0x0, 0x0, 0xc, 0xa0, 0x0,
    0x0, 0xc, 0xa0, 0x0, 0x0, 0xc, 0xa0, 0x0,
    0x0, 0xc, 0xa0, 0x0, 0x0, 0xc, 0xa0, 0x0,
    0x0, 0xc, 0xa0, 0x0, 0x0, 0xc, 0xa0, 0x0,
    0x2, 0x2d, 0xb2, 0x20, 0x5f, 0xff, 0xff, 0xf2,

    /* U+004A "J" */
    0x0, 0xaf, 0xff, 0xf2, 0x0, 0x13, 0x36, 0xf2,
    0x0, 0x0, 0x4, 0xf2, 0x0, 0x0, 0x4, 0xf2,
    0x0, 0x0, 0x4, 0xf2, 0x0, 0x0, 0x4, 0xf2,
    0x0, 0x0, 0x4, 0xf2, 0x0, 0x0, 0x4, 0xf2,
    0x0, 0x0, 0x5, 0xf0, 0x0, 0x0, 0xa, 0xd0,
    0x8a, 0x54, 0x9f, 0x60, 0x2a, 0xef, 0xd6, 0x0,

    /* U+004B "K" */
    0x4f, 0x20, 0x0, 0xbd, 0x4, 0xf2, 0x0, 0x8f,
    0x20, 0x4f, 0x20, 0x5f, 0x50, 0x4, 0xf2, 0x2f,
    0x80, 0x0, 0x4f, 0x3d, 0xb0, 0x0, 0x4, 0xfb,
    0xf1, 0x0, 0x0, 0x4f, 0x4f, 0xa0, 0x0, 0x4,
    0xf2, 0x6f, 0x50, 0x0, 0x4f, 0x20, 0xaf, 0x20,
    0x4, 0xf2, 0x1, 0xec, 0x0, 0x4f, 0x20, 0x3,
    0xf8, 0x4, 0xf2, 0x0, 0x8, 0xf4,

    /* U+004C "L" */
    0xca, 0x0, 0x0, 0xc, 0xa0, 0x0, 0x0, 0xca,
    0x0, 0x0, 0xc, 0xa0, 0x0, 0x0, 0xca, 0x0,
    0x0, 0xc, 0xa0, 0x0, 0x0, 0xca, 0x0, 0x0,
    0xc, 0xa0, 0x0, 0x0, 0xca, 0x0, 0x0, 0xc,
    0xa0, 0x0, 0x0, 0xcc, 0x44, 0x44, 0x3c, 0xff,
    0xff, 0xfb,

    /* U+004D "M" */
    0xe, 0xf3, 0x0, 0x6f, 0xb0, 0xf, 0xf7, 0x0,
    0x9f, 0xc0, 0xf, 0xba, 0x0, 0xdb, 0xd0, 0xf,
    0x8e, 0x0, 0xf8, 0xe0, 0x1f, 0x4f, 0x14, 0xd6,
    0xf0, 0x2f, 0x2d, 0x57, 0x96, 0xf0, 0x3f, 0x19,
    0x9a, 0x65, 0xf0, 0x4f, 0x5, 0xce, 0x24, 0xf1,
    0x5f, 0x2, 0xfe, 0x3, 0xf2, 0x5f, 0x0, 0xc9,
    0x2, 0xf3, 0x6e, 0x0, 0x0, 0x1, 0xf4, 0x7d,
    0x0, 0x0, 0x0, 0xf5,

    /* U+004E "N" */
    0xaf, 0x70, 0x0, 0xd7, 0xaf, 0xd0, 0x0, 0xd7,
    0xaa, 0xf4, 0x0, 0xd7, 0xa9, 0xba, 0x0, 0xd7,
    0xaa, 0x5f, 0x0, 0xd7, 0xaa, 0xf, 0x60, 0xd7,
    0xab, 0x9, 0xc0, 0xd7, 0xab, 0x3, 0xf2, 0xd7,
    0xab, 0x0, 0xd8, 0xc7, 0xab, 0x0, 0x7e, 0xb7,
    0xab, 0x0, 0x1f, 0xf7, 0xab, 0x0, 0xb, 0xf7,

    /* U+004F "O" */
    0x0, 0x2b, 0xee, 0xa1, 0x0, 0x1, 0xeb, 0x45,
    0xcd, 0x0, 0x9, 0xd0, 0x0, 0x1f, 0x60, 0xe,
    0x80, 0x0, 0xa, 0xc0, 0x1f, 0x50, 0x0, 0x7,
    0xf0, 0x3f, 0x40, 0x0, 0x6, 0xf0, 0x3f, 0x40,
    0x0, 0x6, 0xf0, 0x2f, 0x50, 0x0, 0x7, 0xf0,
    0xe, 0x80, 0x0, 0xa, 0xc0, 0x9, 0xd0, 0x0,
    0x1f, 0x60, 0x1, 0xeb, 0x44, 0xcd, 0x0, 0x0,
    0x2b, 0xfe, 0xa1, 0x0,

    /* U+0050 "P" */
    0x1f, 0xff, 0xeb, 0x40, 0x1, 0xf6, 0x23, 0x9f,
    0x60, 0x1f, 0x50, 0x0, 0xbe, 0x1, 0xf5, 0x0,
    0x7, 0xf1, 0x1f, 0x50, 0x0, 0x6f, 0x11, 0xf5,
    0x0, 0x9, 0xe0, 0x1f, 0x50, 0x16, 0xf7, 0x1,
    0xff, 0xff, 0xe7, 0x0, 0x1f, 0x72, 0x10, 0x0,
    0x1, 0xf5, 0x0, 0x0, 0x0, 0x1f, 0x50, 0x0,
    0x0, 0x1, 0xf5, 0x0, 0x0, 0x0,

    /* U+0051 "Q" */
    0x0, 0x2b, 0xee, 0xa1, 0x0, 0x1, 0xeb, 0x45,
    0xcd, 0x0, 0x9, 0xd0, 0x0, 0x1f, 0x60, 0xe,
    0x70, 0x0, 0xa, 0xc0, 0x2f, 0x40, 0x0, 0x7,
    0xf0, 0x3f, 0x30, 0x0, 0x6, 0xf0, 0x3f, 0x30,
    0x0, 0x6, 0xf0, 0x2f, 0x40, 0x0, 0x7, 0xf0,
    0xf, 0x70, 0x0, 0xa, 0xc0, 0xa, 0xd0, 0x0,
    0x1f, 0x60, 0x2, 0xfa, 0x34, 0xcb, 0x0, 0x0,
    0x3b, 0xff, 0xf6, 0x0, 0x0, 0x0, 0x1, 0x6f,
    0xc0, 0x0, 0x0, 0x0, 0x6, 0xf7, 0x0, 0x0,
    0x0, 0x0, 0x83,

    /* U+0052 "R" */
    0x5f, 0xff, 0xeb, 0x40, 0x5, 0xf3, 0x24, 0xaf,
    0x40, 0x5f, 0x10, 0x0, 0xeb, 0x5, 0xf1, 0x0,
    0xb, 0xc0, 0x5f, 0x10, 0x0, 0xda, 0x5, 0xf1,
    0x1, 0x8f, 0x30, 0x5f, 0xff, 0xfc, 0x30, 0x5,
    0xf3, 0x4f, 0x60, 0x0, 0x5f, 0x10, 0x8f, 0x10,
    0x5, 0xf1, 0x0, 0xdb, 0x0, 0x5f, 0x10, 0x4,
    0xf6, 0x5, 0xf1, 0x0, 0x9, 0xf1,

    /* U+0053 "S" */
    0x0, 0x5c, 0xff, 0xc5, 0x0, 0x5f, 0x94, 0x59,
    0xf3, 0xb, 0xc0, 0x0, 0x1, 0x0, 0xbc, 0x0,
    0x0, 0x0, 0x5, 0xfb, 0x40, 0x0, 0x0, 0x5,
    0xdf, 0xe8, 0x10, 0x0, 0x0, 0x39, 0xfe, 0x20,
    0x0, 0x0, 0x2, 0xf9, 0x0, 0x0, 0x0, 0xb,
    0xc0, 0x30, 0x0, 0x0, 0xda, 0x1f, 0xc6, 0x35,
    0xcf, 0x30, 0x29, 0xef, 0xeb, 0x30,

    /* U+0054 "T" */
    0x5f, 0xff, 0xff, 0xff, 0xf1, 0x14, 0x44, 0xdb,
    0x44, 0x40, 0x0, 0x0, 0xd9, 0x0, 0x0, 0x0,
    0x0, 0xd9, 0x0, 0x0, 0x0, 0x0, 0xd9, 0x0,
    0x0, 0x0, 0x0, 0xd9, 0x0, 0x0, 0x0, 0x0,
    0xd9, 0x0, 0x0, 0x0, 0x0, 0xd9, 0x0, 0x0,
    0x0, 0x0, 0xd9, 0x0, 0x0, 0x0, 0x0, 0xd9,
    0x0, 0x0, 0x0, 0x0, 0xd9, 0x0, 0x0, 0x0,
    0x0, 0xd9, 0x0, 0x0,

    /* U+0055 "U" */
    0xd9, 0x0, 0x0, 0xca, 0xd9, 0x0, 0x0, 0xca,
    0xd9, 0x0, 0x0, 0xca, 0xd9, 0x0, 0x0, 0xca,
    0xd9, 0x0, 0x0, 0xca, 0xd9, 0x0, 0x0, 0xca,
    0xd9, 0x0, 0x0, 0xca, 0xd9, 0x0, 0x0, 0xca,
    0xca, 0x0, 0x0, 0xd9, 0x9e, 0x0, 0x1, 0xf6,
    0x2f, 0xb5, 0x5d, 0xd0, 0x3, 0xbf, 0xea, 0x10,

    /* U+0056 "V" */
    0x7f, 0x10, 0x0, 0x2, 0xf4, 0x1f, 0x60, 0x0,
    0x7, 0xf0, 0xc, 0xb0, 0x0, 0xc, 0xa0, 0x7,
    0xf0, 0x0, 0x1f, 0x50, 0x2, 0xf4, 0x0, 0x6f,
    0x0, 0x0, 0xd9, 0x0, 0xbb, 0x0, 0x0, 0x8e,
    0x0, 0xf6, 0x0, 0x0, 0x3f, 0x35, 0xf1, 0x0,
    0x0, 0xe, 0x89, 0xc0, 0x0, 0x0, 0x9, 0xde,
    0x70, 0x0, 0x0, 0x4, 0xff, 0x20, 0x0, 0x0,
    0x0, 0xfd, 0x0, 0x0,

    /* U+0057 "W" */
    0xd8, 0x0, 0x0, 0x0, 0x9b, 0xba, 0x0, 0x98,
    0x0, 0xb8, 0x9c, 0x1, 0xff, 0x0, 0xe6, 0x7e,
    0x4, 0xdf, 0x10, 0xf4, 0x5f, 0x6, 0xae, 0x42,
    0xf1, 0x3f, 0x29, 0x8c, 0x64, 0xf0, 0xf, 0x4b,
    0x59, 0x86, 0xd0, 0xe, 0x5d, 0x37, 0xa8, 0xb0,
    0xc, 0x8f, 0x15, 0xda, 0x80, 0xa, 0xce, 0x3,
    0xfc, 0x60, 0x8, 0xfc, 0x0, 0xff, 0x40, 0x6,
    0xfa, 0x0, 0xef, 0x10,

    /* U+0058 "X" */
    0xd, 0xb0, 0x0, 0xd, 0xa0, 0x5, 0xf3, 0x0,
    0x6f, 0x10, 0x0, 0xbc, 0x0, 0xe8, 0x0, 0x0,
    0x2f, 0x57, 0xe0, 0x0, 0x0, 0x9, 0xdf, 0x50,
    0x0, 0x0, 0x1, 0xfe, 0x0, 0x0, 0x0, 0x7,
    0xef, 0x40, 0x0, 0x0, 0x1e, 0x6a, 0xd0, 0x0,
    0x0, 0x8d, 0x2, 0xf6, 0x0, 0x2, 0xf5, 0x0,
    0x9e, 0x0, 0xa, 0xd0, 0x0, 0x1f, 0x80, 0x3f,
    0x40, 0x0, 0x8, 0xf1,

    /* U+0059 "Y" */
    0x5f, 0x30, 0x0, 0x4, 0xf3, 0xd, 0xb0, 0x0,
    0xc, 0xa0, 0x5, 0xf3, 0x0, 0x4f, 0x20, 0x0,
    0xcb, 0x0, 0xca, 0x0, 0x0, 0x4f, 0x34, 0xf2,
    0x0, 0x0, 0xc, 0xbc, 0x90, 0x0, 0x0, 0x4,
    0xff, 0x10, 0x0, 0x0, 0x0, 0xda, 0x0, 0x0,
    0x0, 0x0, 0xca, 0x0, 0x0, 0x0, 0x0, 0xca,
    0x0, 0x0, 0x0, 0x0, 0xca, 0x0, 0x0, 0x0,
    0x0, 0xca, 0x0, 0x0,

    /* U+005A "Z" */
    0x3f, 0xff, 0xff, 0xfa, 0x3, 0x33, 0x35, 0xf7,
    0x0, 0x0, 0xa, 0xd0, 0x0, 0x0, 0x4f, 0x30,
    0x0, 0x0, 0xd9, 0x0, 0x0, 0x8, 0xe1, 0x0,
    0x0, 0x2f, 0x50, 0x0, 0x0, 0xcb, 0x0, 0x0,
    0x6, 0xf2, 0x0, 0x0, 0x1e, 0x80, 0x0, 0x0,
    0x9f, 0x44, 0x44, 0x42, 0xdf, 0xff, 0xff, 0xf8,

    /* U+005B "[" */
    0xff, 0xff, 0x2f, 0x73, 0x30, 0xf5, 0x0, 0xf,
    0x50, 0x0, 0xf5, 0x0, 0xf, 0x50, 0x0, 0xf5,
    0x0, 0xf, 0x50, 0x0, 0xf5, 0x0, 0xf, 0x50,
    0x0, 0xf5, 0x0, 0xf, 0x50, 0x0, 0xf5, 0x0,
    0xf, 0x50, 0x0, 0xff, 0xff, 0x22, 0x33, 0x30,

    /* U+005C "\\" */
    0x4, 0x0, 0x0, 0x0, 0x0, 0xe7, 0x0, 0x0,
    0x0, 0x6, 0xe0, 0x0, 0x0, 0x0, 0xe, 0x60,
    0x0, 0x0, 0x0, 0x7d, 0x0, 0x0, 0x0, 0x0,
    0xf5, 0x0, 0x0, 0x0, 0x8, 0xd0, 0x0, 0x0,
    0x0, 0x1f, 0x50, 0x0, 0x0, 0x0, 0x9c, 0x0,
    0x0, 0x0, 0x1, 0xf4, 0x0, 0x0, 0x0, 0x9,
    0xb0, 0x0, 0x0, 0x0, 0x2f, 0x30, 0x0, 0x0,
    0x0, 0xab, 0x0, 0x0, 0x0, 0x3, 0xf2, 0x0,
    0x0, 0x0, 0xb, 0xa0, 0x0, 0x0, 0x0, 0x36,

    /* U+005D "]" */
    0x4f, 0xff, 0xd0, 0x33, 0x9d, 0x0, 0x7, 0xd0,
    0x0, 0x7d, 0x0, 0x7, 0xd0, 0x0, 0x7d, 0x0,
    0x7, 0xd0, 0x0, 0x7d, 0x0, 0x7, 0xd0, 0x0,
    0x7d, 0x0, 0x7, 0xd0, 0x0, 0x7d, 0x0, 0x7,
    0xd0, 0x0, 0x7d, 0x4f, 0xff, 0xd0, 0x33, 0x32,

    /* U+005E "^" */
    0x0, 0x1e, 0xd0, 0x0, 0x0, 0x9b, 0xe7, 0x0,
    0x3, 0xf2, 0x5f, 0x20, 0xd, 0x90, 0xb, 0xb0,
    0x7e, 0x10, 0x2, 0xf5,

    /* U+005F "_" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x2f, 0xff, 0xff,
    0xff, 0xf0, 0x3, 0x33, 0x33, 0x33, 0x30,

    /* U+0060 "`" */
    0x0, 0x0, 0xaa, 0x10, 0x4b, 0xe5, 0x0, 0x34,

    /* U+0061 "a" */
    0x1a, 0xef, 0xe8, 0x0, 0x6, 0x43, 0x5e, 0x80,
    0x0, 0x0, 0x9, 0xc0, 0x5, 0xbe, 0xff, 0xd0,
    0x6f, 0x60, 0x8, 0xd0, 0xcb, 0x0, 0x8, 0xd0,
    0xca, 0x0, 0xa, 0xd0, 0x8f, 0x41, 0x7f, 0xe1,
    0x9, 0xee, 0xa2, 0xb5,

    /* U+0062 "b" */
    0x27, 0x0, 0x0, 0x0, 0x5f, 0x0, 0x0, 0x0,
    0x5f, 0x0, 0x0, 0x0, 0x5f, 0x0, 0x0, 0x0,
    0x5f, 0x3c, 0xfd, 0x40, 0x5f, 0xd4, 0x3b, 0xf1,
    0x5f, 0x20, 0x1, 0xf7, 0x5f, 0x0, 0x0, 0xda,
    0x5f, 0x0, 0x0, 0xcb, 0x5f, 0x0, 0x0, 0xda,
    0x5f, 0x0, 0x2, 0xf6, 0x5f, 0xb3, 0x3c, 0xe0,
    0x5e, 0x6e, 0xfc, 0x20,

    /* U+0063 "c" */
    0x0, 0x7d, 0xfe, 0x91, 0x8, 0xf7, 0x35, 0xb2,
    0x1f, 0x70, 0x0, 0x0, 0x6f, 0x20, 0x0, 0x0,
    0x7f, 0x0, 0x0, 0x0, 0x6f, 0x10, 0x0, 0x0,
    0x2f, 0x60, 0x0, 0x0, 0x9, 0xf7, 0x35, 0xc2,
    0x0, 0x7d, 0xfe, 0x80,

    /* U+0064 "d" */
    0x0, 0x0, 0x1, 0x71, 0x0, 0x0, 0x3, 0xf3,
    0x0, 0x0, 0x3, 0xf3, 0x0, 0x0, 0x3, 0xf3,
    0x3, 0xcf, 0xd7, 0xf3, 0x2f, 0xb3, 0x4d, 0xf3,
    0x9f, 0x0, 0x3, 0xf3, 0xcb, 0x0, 0x3, 0xf3,
    0xda, 0x0, 0x3, 0xf3, 0xdb, 0x0, 0x3, 0xf3,
    0x9e, 0x0, 0x3, 0xf3, 0x3f, 0x70, 0x2d, 0xf3,
    0x5, 0xdf, 0xc4, 0xf3,

    /* U+0065 "e" */
    0x1, 0x9e, 0xfa, 0x10, 0xc, 0xd4, 0x3c, 0xc0,
    0x5f, 0x20, 0x1, 0xf4, 0x9d, 0x0, 0x0, 0xd7,
    0xbf, 0xee, 0xee, 0xf8, 0x9d, 0x11, 0x11, 0x10,
    0x5f, 0x10, 0x0, 0x0, 0xc, 0xd5, 0x36, 0xa0,
    0x1, 0x9e, 0xfd, 0x50,

    /* U+0066 "f" */
    0x0, 0x3, 0xcf, 0xeb, 0x0, 0x0, 0xea, 0x34,
    0x60, 0x0, 0x5f, 0x0, 0x0, 0x0, 0x6, 0xf0,
    0x0, 0x0, 0x0, 0x6f, 0x0, 0x0, 0x6, 0xff,
    0xff, 0xfc, 0x0, 0x12, 0x7f, 0x22, 0x10, 0x0,
    0x6, 0xf0, 0x0, 0x0, 0x0, 0x6f, 0x0, 0x0,
    0x0, 0x6, 0xf0, 0x0, 0x0, 0x0, 0x6f, 0x0,
    0x0, 0x0, 0x6, 0xf0, 0x0, 0x0, 0x0, 0x6f,
    0x0, 0x0, 0x0,

    /* U+0067 "g" */
    0x0, 0x0, 0x1, 0x57, 0x0, 0x3c, 0xff, 0xfc,
    0xa0, 0x2f, 0x81, 0x3e, 0x60, 0x8, 0xd0, 0x0,
    0x8e, 0x0, 0xbb, 0x0, 0x6, 0xf0, 0x9, 0xd0,
    0x0, 0x8e, 0x0, 0x3f, 0x70, 0x2e, 0x70, 0x0,
    0x9e, 0xfd, 0x70, 0x0, 0x2f, 0x63, 0x32, 0x0,
    0x0, 0xaf, 0xff, 0xfc, 0x10, 0x0, 0x0, 0x3,
    0xda, 0xa, 0x40, 0x0, 0x9, 0xd0, 0xbc, 0x42,
    0x36, 0xf7, 0x1, 0xae, 0xfe, 0xc6, 0x0,

    /* U+0068 "h" */
    0x16, 0x0, 0x0, 0x0, 0x5f, 0x0, 0x0, 0x0,
    0x5f, 0x0, 0x0, 0x0, 0x5f, 0x0, 0x0, 0x0,
    0x5f, 0x3b, 0xfe, 0x50, 0x5f, 0xd5, 0x29, 0xf0,
    0x5f, 0x20, 0x3, 0xf3, 0x5f, 0x0, 0x2, 0xf3,
    0x5f, 0x0, 0x2, 0xf3, 0x5f, 0x0, 0x2, 0xf3,
    0x5f, 0x0, 0x2, 0xf3, 0x5f, 0x0, 0x2, 0xf3,
    0x5f, 0x0, 0x2, 0xf3,

    /* U+0069 "i" */
    0x0, 0xd, 0xb0, 0x0, 0x0, 0xd, 0xb0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xf, 0xff, 0xf0, 0x0, 0x1, 0x16, 0xf0, 0x0,
    0x0, 0x5, 0xf0, 0x0, 0x0, 0x5, 0xf0, 0x0,
    0x0, 0x5, 0xf0, 0x0, 0x0, 0x5, 0xf0, 0x0,
    0x0, 0x5, 0xf0, 0x0, 0x1, 0x16, 0xf1, 0x10,
    0xf, 0xff, 0xff, 0xf7,

    /* U+006A "j" */
    0x0, 0x0, 0xcc, 0x0, 0x0, 0xb, 0xc0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa, 0xff,
    0xff, 0x40, 0x11, 0x12, 0xf4, 0x0, 0x0, 0x1f,
    0x40, 0x0, 0x1, 0xf4, 0x0, 0x0, 0x1f, 0x40,
    0x0, 0x1, 0xf4, 0x0, 0x0, 0x1f, 0x40, 0x0,
    0x1, 0xf4, 0x0, 0x0, 0x3f, 0x20, 0x0, 0xb,
    0xc0, 0x0, 0x4c, 0xe2, 0x4, 0xee, 0x91, 0x0,
    0x13, 0x0, 0x0, 0x0,

    /* U+006B "k" */
    0x2a, 0x10, 0x0, 0x0, 0x4, 0xf2, 0x0, 0x0,
    0x0, 0x4f, 0x20, 0x0, 0x0, 0x4, 0xf2, 0x0,
    0x0, 0x0, 0x4f, 0x20, 0x6, 0xf6, 0x4, 0xf2,
    0x5, 0xf7, 0x0, 0x4f, 0x24, 0xf7, 0x0, 0x4,
    0xf5, 0xf8, 0x0, 0x0, 0x4f, 0x7f, 0x60, 0x0,
    0x4, 0xf2, 0x7f, 0x40, 0x0, 0x4f, 0x20, 0xaf,
    0x30, 0x4, 0xf2, 0x0, 0xbe, 0x10, 0x4f, 0x20,
    0x1, 0xdd, 0x10,

    /* U+006C "l" */
    0xf, 0xff, 0xf0, 0x0, 0x0, 0x11, 0x6f, 0x0,
    0x0, 0x0, 0x5, 0xf0, 0x0, 0x0, 0x0, 0x5f,
    0x0, 0x0, 0x0, 0x5, 0xf0, 0x0, 0x0, 0x0,
    0x5f, 0x0, 0x0, 0x0, 0x5, 0xf0, 0x0, 0x0,
    0x0, 0x5f, 0x0, 0x0, 0x0, 0x5, 0xf0, 0x0,
    0x0, 0x0, 0x5f, 0x0, 0x0, 0x0, 0x5, 0xf0,
    0x0, 0x0, 0x0, 0x2f, 0x73, 0x50, 0x0, 0x0,
    0x6e, 0xfd, 0x10,

    /* U+006D "m" */
    0x2f, 0x5e, 0xd3, 0xcf, 0x70, 0x2f, 0xa3, 0xde,
    0x57, 0xe0, 0x2f, 0x10, 0xb9, 0x4, 0xf0, 0x2f,
    0x10, 0xb9, 0x4, 0xf0, 0x2f, 0x10, 0xb9, 0x4,
    0xf0, 0x2f, 0x10, 0xb9, 0x4, 0xf0, 0x2f, 0x10,
    0xb9, 0x4, 0xf0, 0x2f, 0x10, 0xb9, 0x4, 0xf0,
    0x2f, 0x10, 0xb9, 0x4, 0xf0,

    /* U+006E "n" */
    0x5d, 0x3b, 0xee, 0x50, 0x5f, 0xc2, 0x8, 0xf0,
    0x5f, 0x10, 0x3, 0xf3, 0x5f, 0x0, 0x2, 0xf3,
    0x5f, 0x0, 0x2, 0xf3, 0x5f, 0x0, 0x2, 0xf3,
    0x5f, 0x0, 0x2, 0xf3, 0x5f, 0x0, 0x2, 0xf3,
    0x5f, 0x0, 0x2, 0xf3,

    /* U+006F "o" */
    0x2, 0xbf, 0xfa, 0x10, 0x1e, 0xb4, 0x4d, 0xd0,
    0x7f, 0x10, 0x3, 0xf4, 0xbc, 0x0, 0x0, 0xf8,
    0xcb, 0x0, 0x0, 0xd9, 0xac, 0x0, 0x0, 0xf8,
    0x7f, 0x10, 0x3, 0xf4, 0xe, 0xb3, 0x4d, 0xc0,
    0x2, 0xbf, 0xea, 0x10,

    /* U+0070 "p" */
    0x5d, 0x3c, 0xfd, 0x40, 0x5f, 0xd4, 0x3c, 0xf1,
    0x5f, 0x20, 0x2, 0xf6, 0x5f, 0x0, 0x0, 0xe9,
    0x5f, 0x0, 0x0, 0xd9, 0x5f, 0x0, 0x0, 0xf8,
    0x5f, 0x10, 0x3, 0xf5, 0x5f, 0xc4, 0x4d, 0xe0,
    0x5f, 0x6e, 0xfc, 0x20, 0x5f, 0x0, 0x0, 0x0,
    0x5f, 0x0, 0x0, 0x0, 0x5f, 0x0, 0x0, 0x0,
    0x14, 0x0, 0x0, 0x0,

    /* U+0071 "q" */
    0x3, 0xcf, 0xd4, 0xf3, 0x1f, 0xb3, 0x4d, 0xf3,
    0x7f, 0x10, 0x3, 0xf3, 0xbc, 0x0, 0x3, 0xf3,
    0xcb, 0x0, 0x3, 0xf3, 0xbc, 0x0, 0x3, 0xf3,
    0x9f, 0x0, 0x4, 0xf3, 0x3f, 0xa3, 0x5e, 0xf3,
    0x5, 0xdf, 0xc5, 0xf3, 0x0, 0x0, 0x3, 0xf3,
    0x0, 0x0, 0x3, 0xf3, 0x0, 0x0, 0x3, 0xf3,
    0x0, 0x0, 0x0, 0x41,

    /* U+0072 "r" */
    0x4f, 0xf2, 0x5d, 0xfa, 0x1, 0xe8, 0xd4, 0xa9,
    0x0, 0xef, 0x20, 0xa8, 0x0, 0xea, 0x0, 0x0,
    0x0, 0xe7, 0x0, 0x0, 0x0, 0xe7, 0x0, 0x0,
    0x0, 0xe7, 0x0, 0x0, 0x1, 0xe7, 0x10, 0x0,
    0x4f, 0xff, 0xf3, 0x0,

    /* U+0073 "s" */
    0x3, 0xbf, 0xfc, 0x50, 0x1f, 0x93, 0x36, 0xa0,
    0x4f, 0x30, 0x0, 0x0, 0xd, 0xe7, 0x20, 0x0,
    0x1, 0x7c, 0xfd, 0x40, 0x0, 0x0, 0x1b, 0xf1,
    0x0, 0x0, 0x5, 0xf3, 0x7c, 0x53, 0x4c, 0xe0,
    0x19, 0xef, 0xda, 0x20,

    /* U+0074 "t" */
    0x0, 0x1, 0x0, 0x0, 0x0, 0xba, 0x0, 0x0,
    0x0, 0xba, 0x0, 0x0, 0xbf, 0xff, 0xff, 0x90,
    0x11, 0xbb, 0x11, 0x0, 0x0, 0xba, 0x0, 0x0,
    0x0, 0xba, 0x0, 0x0, 0x0, 0xba, 0x0, 0x0,
    0x0, 0xba, 0x0, 0x0, 0x0, 0xab, 0x0, 0x0,
    0x0, 0x6f, 0x53, 0x61, 0x0, 0x8, 0xef, 0xc3,

    /* U+0075 "u" */
    0x5f, 0x0, 0x3, 0xf3, 0x5f, 0x0, 0x3, 0xf3,
    0x5f, 0x0, 0x3, 0xf3, 0x5f, 0x0, 0x3, 0xf3,
    0x5f, 0x0, 0x3, 0xf3, 0x5f, 0x0, 0x3, 0xf3,
    0x5f, 0x0, 0x3, 0xf3, 0x2f, 0x50, 0x3d, 0xf3,
    0x7, 0xee, 0xb3, 0xf3,

    /* U+0076 "v" */
    0xd9, 0x0, 0x0, 0xba, 0x7e, 0x0, 0x1, 0xf5,
    0x2f, 0x40, 0x6, 0xf0, 0xc, 0x90, 0xb, 0xa0,
    0x7, 0xe0, 0xf, 0x40, 0x1, 0xf3, 0x5e, 0x0,
    0x0, 0xc9, 0xa9, 0x0, 0x0, 0x6e, 0xf3, 0x0,
    0x0, 0x1f, 0xd0, 0x0,

    /* U+0077 "w" */
    0xac, 0x0, 0x0, 0x0, 0xd7, 0x7e, 0x0, 0xcc,
    0x0, 0xf4, 0x4f, 0x1, 0xff, 0x12, 0xf2, 0x1f,
    0x24, 0xcd, 0x34, 0xf0, 0xe, 0x47, 0x9a, 0x66,
    0xc0, 0xc, 0x7b, 0x67, 0x98, 0xa0, 0x9, 0x9e,
    0x35, 0xca, 0x70, 0x6, 0xcf, 0x2, 0xfd, 0x40,
    0x3, 0xfd, 0x0, 0xff, 0x20,

    /* U+0078 "x" */
    0x6, 0xf3, 0x0, 0x5f, 0x30, 0xb, 0xd0, 0xe,
    0x80, 0x0, 0x1f, 0x68, 0xd0, 0x0, 0x0, 0x6f,
    0xf3, 0x0, 0x0, 0x1, 0xfe, 0x0, 0x0, 0x0,
    0xba, 0xd9, 0x0, 0x0, 0x6f, 0x14, 0xf4, 0x0,
    0x2f, 0x60, 0xa, 0xe0, 0xc, 0xc0, 0x0, 0x1f,
    0x90,

    /* U+0079 "y" */
    0xda, 0x0, 0x0, 0xca, 0x7e, 0x0, 0x1, 0xf5,
    0x2f, 0x40, 0x5, 0xf0, 0xd, 0x90, 0xa, 0xa0,
    0x7, 0xe0, 0xf, 0x50, 0x2, 0xf3, 0x4f, 0x0,
    0x0, 0xc8, 0x9a, 0x0, 0x0, 0x7d, 0xe4, 0x0,
    0x0, 0x2f, 0xf0, 0x0, 0x0, 0xb, 0x90, 0x0,
    0x0, 0x6f, 0x20, 0x0, 0x2c, 0xf5, 0x0, 0x0,
    0x6, 0x10, 0x0, 0x0,

    /* U+007A "z" */
    0xf, 0xff, 0xff, 0xf2, 0x3, 0x33, 0x3d, 0xc0,
    0x0, 0x0, 0x7f, 0x20, 0x0, 0x2, 0xf6, 0x0,
    0x0, 0xd, 0xb0, 0x0, 0x0, 0x9e, 0x10, 0x0,
    0x4, 0xf4, 0x0, 0x0, 0x1e, 0xb3, 0x33, 0x30,
    0x5f, 0xff, 0xff, 0xf1,

    /* U+007B "{" */
    0x0, 0x2, 0xad, 0x60, 0x0, 0xcc, 0x41, 0x0,
    0xe, 0x50, 0x0, 0x0, 0xc7, 0x0, 0x0, 0xb,
    0x90, 0x0, 0x0, 0xaa, 0x0, 0x0, 0x2d, 0x90,
    0x1, 0xff, 0xc0, 0x0, 0x3, 0x6f, 0x70, 0x0,
    0x0, 0xaa, 0x0, 0x0, 0xa, 0xa0, 0x0, 0x0,
    0xb8, 0x0, 0x0, 0xd, 0x70, 0x0, 0x0, 0xe5,
    0x0, 0x0, 0xc, 0xa1, 0x0, 0x0, 0x3c, 0xf6,
    0x0, 0x0, 0x0, 0x0,

    /* U+007C "|" */
    0xb8, 0xb8, 0xb8, 0xb8, 0xb8, 0xb8, 0xb8, 0xb8,
    0xb8, 0xb8, 0xb8, 0xb8, 0xb8, 0xb8, 0xb8,

    /* U+007D "}" */
    0x8d, 0x91, 0x0, 0x14, 0xda, 0x0, 0x0, 0x8b,
    0x0, 0x0, 0xaa, 0x0, 0x0, 0xb8, 0x0, 0x0,
    0xd7, 0x0, 0x0, 0xbc, 0x20, 0x0, 0x1c, 0xfe,
    0x0, 0x9e, 0x52, 0x0, 0xd7, 0x0, 0x0, 0xc7,
    0x0, 0x0, 0xb9, 0x0, 0x0, 0x9a, 0x0, 0x0,
    0x8c, 0x0, 0x2, 0xca, 0x0, 0x8f, 0xb1, 0x0,
    0x0, 0x0, 0x0,

    /* U+007E "~" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xcf, 0x90,
    0x1, 0x80, 0xc, 0xa4, 0xda, 0x1a, 0xb0, 0x1b,
    0x0, 0x1d, 0xfd, 0x10, 0x0, 0x0, 0x0, 0x20,
    0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 158, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 158, .box_w = 4, .box_h = 12, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 158, .box_w = 6, .box_h = 5, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 39, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 158, .box_w = 8, .box_h = 18, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 165, .adv_w = 158, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 230, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 158, .box_w = 2, .box_h = 5, .ofs_x = 4, .ofs_y = 8},
    {.bitmap_index = 295, .adv_w = 158, .box_w = 5, .box_h = 18, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 340, .adv_w = 158, .box_w = 6, .box_h = 18, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 394, .adv_w = 158, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 439, .adv_w = 158, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 471, .adv_w = 158, .box_w = 4, .box_h = 6, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 483, .adv_w = 158, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 495, .adv_w = 158, .box_w = 4, .box_h = 3, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 501, .adv_w = 158, .box_w = 9, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 573, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 621, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 669, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 723, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 777, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 825, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 873, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 921, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 969, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1017, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1065, .adv_w = 158, .box_w = 4, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 1083, .adv_w = 158, .box_w = 4, .box_h = 12, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 1107, .adv_w = 158, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1147, .adv_w = 158, .box_w = 8, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1167, .adv_w = 158, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1207, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1255, .adv_w = 158, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1325, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1385, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1433, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1487, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1541, .adv_w = 158, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1583, .adv_w = 158, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1625, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1679, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1727, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1775, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1823, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1877, .adv_w = 158, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1919, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1979, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2027, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2087, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2141, .adv_w = 158, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2216, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2270, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2324, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2384, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2432, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2492, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2552, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2612, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2672, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2720, .adv_w = 158, .box_w = 5, .box_h = 16, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 2760, .adv_w = 158, .box_w = 9, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2832, .adv_w = 158, .box_w = 5, .box_h = 16, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 2872, .adv_w = 158, .box_w = 8, .box_h = 5, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 2892, .adv_w = 158, .box_w = 10, .box_h = 3, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 2907, .adv_w = 158, .box_w = 4, .box_h = 4, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 2915, .adv_w = 158, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2951, .adv_w = 158, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3003, .adv_w = 158, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3039, .adv_w = 158, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3091, .adv_w = 158, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3127, .adv_w = 158, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3186, .adv_w = 158, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 3249, .adv_w = 158, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3301, .adv_w = 158, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3353, .adv_w = 158, .box_w = 7, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 3413, .adv_w = 158, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3472, .adv_w = 158, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3531, .adv_w = 158, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3576, .adv_w = 158, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3612, .adv_w = 158, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3648, .adv_w = 158, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 3700, .adv_w = 158, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 3752, .adv_w = 158, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3788, .adv_w = 158, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3824, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3872, .adv_w = 158, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3908, .adv_w = 158, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3944, .adv_w = 158, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3989, .adv_w = 158, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 4030, .adv_w = 158, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 4082, .adv_w = 158, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4118, .adv_w = 158, .box_w = 7, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 4178, .adv_w = 158, .box_w = 2, .box_h = 15, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 4193, .adv_w = 158, .box_w = 6, .box_h = 17, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 4244, .adv_w = 158, .box_w = 10, .box_h = 5, .ofs_x = 0, .ofs_y = 3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR >= 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR >= 8
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t FiraCode_Regular_16 = {
#else
lv_font_t FiraCode_Regular_16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
    .fallback = NULL,
    .user_data = NULL
};



#endif /*#if FIRACODE_REGULAR_16*/

