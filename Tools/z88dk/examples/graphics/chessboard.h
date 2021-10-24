/* 
   Normal size chessboard by Stefano Bodrato - 27/02/2002
   Converted from ZX to BMP and then from BMP to sprites
   with the Daniel McKinnon's z88dk Sprite Editor
*/

#include <graphics.h>
#include <games.h>

#define P_BLACK 1
#define P_WHITE 0

#define P_PAWN 5
#define P_ROOK 0
#define P_KNIGHT 1
#define P_BISHOP 2
#define P_QUEEN 4
#define P_KING 3


char pieces[] = { 
	
21, 23, 0x00 , 0x00 , 0x00 , 0x3D , 0xF7 , 0x80 , 0x25 , 0x14 , 0x80 , 0x25 , 0x14 
, 0x80 , 0x27 , 0x1C , 0x80 , 0x20 , 0x00 , 0x80 , 0x18 , 0x03 , 0x00 , 0x04 
, 0x04 , 0x00 , 0x04 , 0x04 , 0x00 , 0x04 , 0x84 , 0x00 , 0x04 , 0x84 , 0x00 
, 0x04 , 0x04 , 0x00 , 0x04 , 0x84 , 0x00 , 0x04 , 0x84 , 0x00 , 0x04 , 0x84 
, 0x00 , 0x04 , 0x84 , 0x00 , 0x08 , 0x82 , 0x00 , 0x11 , 0x01 , 0x00 , 0x20 
, 0x00 , 0x80 , 0x40 , 0x00 , 0x40 , 0x40 , 0x00 , 0x40 , 0x7F , 0xFF , 0xC0 
, 0x00 , 0x00 , 0x00 ,

21, 23, 0x7F , 0xFF , 0xC0 , 0x7F , 0xFF , 0xC0 , 0x7F , 0xFF , 0xC0 , 0x7F , 0xFF 
, 0xC0 , 0x7F , 0xFF , 0xC0 , 0x7F , 0xFF , 0xC0 , 0x3F , 0xFF , 0x80 , 0x0F 
, 0xFE , 0x00 , 0x0F , 0xFE , 0x00 , 0x0F , 0xFE , 0x00 , 0x0F , 0xFE , 0x00 
, 0x0F , 0xFE , 0x00 , 0x0F , 0xFE , 0x00 , 0x0F , 0xFE , 0x00 , 0x0F , 0xFE 
, 0x00 , 0x0F , 0xFE , 0x00 , 0x1F , 0xFF , 0x00 , 0x3F , 0xFF , 0x80 , 0x7F 
, 0xFF , 0xC0 , 0xFF , 0xFF , 0xE0 , 0xFF , 0xFF , 0xE0 , 0xFF , 0xFF , 0xE0 
, 0xFF , 0xFF , 0xE0 ,

21, 23, 0x00 , 0x00 , 0x00 , 0x03 , 0xE0 , 0x00 , 0x0C , 0x18 , 0x00 , 0x11 , 0x84 
, 0x00 , 0x22 , 0x02 , 0x00 , 0x24 , 0x19 , 0x00 , 0x40 , 0x00 , 0x80 , 0x40 
, 0x00 , 0x40 , 0x40 , 0x00 , 0x20 , 0x40 , 0x00 , 0x20 , 0x40 , 0x3E , 0x20 
, 0x20 , 0x21 , 0xC0 , 0x20 , 0x10 , 0x00 , 0x10 , 0x10 , 0x00 , 0x11 , 0x08 
, 0x00 , 0x09 , 0x08 , 0x00 , 0x09 , 0x04 , 0x00 , 0x12 , 0x02 , 0x00 , 0x24 
, 0x01 , 0x00 , 0x40 , 0x00 , 0x80 , 0x40 , 0x00 , 0x80 , 0x7F , 0xFF , 0x80 
, 0x00 , 0x00 , 0x00 ,

21, 23, 0x03 , 0xE0 , 0x00 , 0x0F , 0xF0 , 0x00 , 0x1F , 0xFC , 0x00 , 0x3F , 0xFE 
, 0x00 , 0x7F , 0xFF , 0x00 , 0x7F , 0xFF , 0x80 , 0xFF , 0xFF , 0xC0 , 0xFF 
, 0xFF , 0xE0 , 0xFF , 0xFF , 0xF0 , 0xFF , 0xFF , 0xF0 , 0xFF , 0xFF , 0xF0 
, 0x7F , 0xFF , 0xE0 , 0x3F , 0xF9 , 0xC0 , 0x3F , 0xF8 , 0x00 , 0x3F , 0xFC 
, 0x00 , 0x1F , 0xFC , 0x00 , 0x1F , 0xFE , 0x00 , 0x3F , 0xFF , 0x00 , 0x7F 
, 0xFF , 0x80 , 0xFF , 0xFF , 0xC0 , 0xFF , 0xFF , 0xC0 , 0xFF , 0xFF , 0xC0 
, 0xFF , 0xFF , 0xC0 ,

21, 23, 0x00 , 0x00 , 0x00 , 0x00 , 0x40 , 0x00 , 0x00 , 0xA0 , 0x00 , 0x01 , 0x10 
, 0x00 , 0x02 , 0x08 , 0x00 , 0x02 , 0xE8 , 0x00 , 0x05 , 0xF4 , 0x00 , 0x05 
, 0x14 , 0x00 , 0x04 , 0x04 , 0x00 , 0x04 , 0x04 , 0x00 , 0x07 , 0x1C , 0x00 
, 0x01 , 0x10 , 0x00 , 0x02 , 0x88 , 0x00 , 0x05 , 0x04 , 0x00 , 0x09 , 0x02 
, 0x00 , 0x08 , 0x02 , 0x00 , 0x0A , 0x02 , 0x00 , 0x0A , 0x02 , 0x00 , 0x0A 
, 0x02 , 0x00 , 0x08 , 0x02 , 0x00 , 0x04 , 0x04 , 0x00 , 0x0F , 0xFE , 0x00 
, 0x00 , 0x00 , 0x00 ,

21, 23, 0x00 , 0x40 , 0x00 , 0x00 , 0xE0 , 0x00 , 0x01 , 0xF0 , 0x00 , 0x03 , 0xF8 
, 0x00 , 0x07 , 0xF8 , 0x00 , 0x07 , 0xFC , 0x00 , 0x0F , 0xFE , 0x00 , 0x0F 
, 0xFE , 0x00 , 0x0F , 0xFE , 0x00 , 0x0F , 0xFE , 0x00 , 0x0F , 0xFE , 0x00 
, 0x0F , 0xFE , 0x00 , 0x07 , 0xFC , 0x00 , 0x0F , 0xFF , 0x00 , 0x1F , 0xFF 
, 0x00 , 0x1F , 0xFF , 0x00 , 0x1F , 0xFF , 0x00 , 0x1F , 0xFF , 0x00 , 0x1F 
, 0xFF , 0x00 , 0x1F , 0xFF , 0x00 , 0x0F , 0xFE , 0x00 , 0x1F , 0xFF , 0x00 
, 0x1F , 0xFF , 0x00 ,

21, 23, 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x00 , 0x60 , 0x50 
, 0x30 , 0x50 , 0x50 , 0x50 , 0x28 , 0x88 , 0xA0 , 0x24 , 0x89 , 0x20 , 0x25 
, 0x05 , 0x20 , 0x13 , 0x06 , 0x40 , 0x11 , 0x04 , 0x40 , 0x11 , 0x8C , 0x40 
, 0x10 , 0x88 , 0x40 , 0x10 , 0x20 , 0x40 , 0x10 , 0x20 , 0x40 , 0x14 , 0xD8 
, 0x40 , 0x14 , 0x20 , 0x40 , 0x10 , 0x20 , 0x40 , 0x12 , 0x00 , 0x40 , 0x12 
, 0x00 , 0x40 , 0x12 , 0x00 , 0x40 , 0x10 , 0x00 , 0x40 , 0x0F , 0xFF , 0x80 
, 0x00 , 0x00 , 0x00 ,

21, 23, 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x00 , 0x60 , 0x70 , 0x30 , 0xF0 , 0xF8 
, 0x78 , 0xF8 , 0xF8 , 0xF8 , 0x7D , 0xFD , 0xF0 , 0x7F , 0xFF , 0xF0 , 0x7F 
, 0xFF , 0xF0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 
, 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF 
, 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F 
, 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x1F , 0xFF , 0xC0 
, 0x0F , 0xFF , 0x80 ,

21, 23, 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x00 , 0x60 , 0x50 
, 0x30 , 0x50 , 0x50 , 0x50 , 0x28 , 0x88 , 0xA0 , 0x24 , 0x89 , 0x20 , 0x25 
, 0x05 , 0x20 , 0x13 , 0x06 , 0x40 , 0x11 , 0x04 , 0x40 , 0x11 , 0x8C , 0x40 
, 0x10 , 0x88 , 0x40 , 0x10 , 0x88 , 0x40 , 0x10 , 0x88 , 0x40 , 0x12 , 0x00 
, 0x40 , 0x12 , 0x00 , 0x40 , 0x12 , 0x00 , 0x40 , 0x08 , 0x00 , 0x80 , 0x09 
, 0x00 , 0x80 , 0x09 , 0x00 , 0x80 , 0x08 , 0x00 , 0x80 , 0x0F , 0xFF , 0x80 
, 0x00 , 0x00 , 0x00 ,

21, 23, 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x00 , 0xE0 , 0x70 , 0x38 , 0xF0 , 0x70 
, 0x78 , 0xF8 , 0xF8 , 0xF8 , 0x7C , 0xF9 , 0xF0 , 0x7F , 0xFF , 0xF0 , 0x7F 
, 0xFF , 0xF0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 
, 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF 
, 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x1F , 0xFF , 0xC0 , 0x1F 
, 0xFF , 0xC0 , 0x1F , 0xFF , 0xC0 , 0x1F , 0xFF , 0xC0 , 0x1F , 0xFF , 0xC0 
, 0x1F , 0xFF , 0xC0 ,

21, 23, 0x00 , 0x00 , 0x00 , 0x00 , 0xF0 , 0x00 , 0x01 , 0x08 , 0x00 , 0x02 , 0x44 
, 0x00 , 0x02 , 0x84 , 0x00 , 0x02 , 0x84 , 0x00 , 0x02 , 0x04 , 0x00 , 0x01 
, 0x08 , 0x00 , 0x00 , 0x90 , 0x00 , 0x00 , 0x90 , 0x00 , 0x01 , 0x08 , 0x00 
, 0x01 , 0x48 , 0x00 , 0x02 , 0x44 , 0x00 , 0x04 , 0x82 , 0x00 , 0x09 , 0x01 
, 0x00 , 0x12 , 0x00 , 0x80 , 0x24 , 0x00 , 0x40 , 0x48 , 0x00 , 0x20 , 0x48 
, 0x00 , 0x20 , 0x40 , 0x00 , 0x20 , 0x20 , 0x00 , 0x40 , 0x7F , 0xFF , 0xE0 
, 0x00 , 0x00 , 0x00 ,

21, 23, 0x00 , 0xF0 , 0x00 , 0x01 , 0xF8 , 0x00 , 0x03 , 0xFC , 0x00 , 0x07 , 0xFE 
, 0x00 , 0x07 , 0xFE , 0x00 , 0x07 , 0xFE , 0x00 , 0x07 , 0xFE , 0x00 , 0x03 
, 0xFC , 0x00 , 0x01 , 0xF8 , 0x00 , 0x01 , 0xF8 , 0x00 , 0x03 , 0xFC , 0x00 
, 0x03 , 0xFC , 0x00 , 0x07 , 0xFE , 0x00 , 0x0F , 0xFF , 0x00 , 0x1F , 0xFF 
, 0x80 , 0x3F , 0xFF , 0xC0 , 0x7F , 0xFF , 0xE0 , 0xFF , 0xFF , 0xF0 , 0xFF 
, 0xFF , 0xF0 , 0xFF , 0xFF , 0xF0 , 0x7F , 0xFF , 0xE0 , 0xFF , 0xFF , 0xF0 
, 0xFF , 0xFF , 0xF0 ,




21, 23, 0x00 , 0x00 , 0x00 , 0x38 , 0xE3 , 0x80 , 0x38 , 0xE3 , 0x80 , 0x38 , 0xE3 
, 0x80 , 0x3F , 0xFF , 0x80 , 0x3F , 0xFF , 0x80 , 0x0F , 0xFE , 0x00 , 0x07 
, 0xFC , 0x00 , 0x07 , 0xFC , 0x00 , 0x06 , 0xFC , 0x00 , 0x06 , 0xFC , 0x00 
, 0x07 , 0xFC , 0x00 , 0x06 , 0xFC , 0x00 , 0x06 , 0xFC , 0x00 , 0x06 , 0xFC 
, 0x00 , 0x06 , 0xFC , 0x00 , 0x0E , 0xFE , 0x00 , 0x1D , 0xFF , 0x00 , 0x3F 
, 0xFF , 0x80 , 0x7F , 0xFF , 0xC0 , 0x7F , 0xFF , 0xC0 , 0x7F , 0xFF , 0xC0 
, 0x00 , 0x00 , 0x00 ,

21, 23, 0x7D , 0xF7 , 0xC0 , 0x7D , 0xF7 , 0xC0 , 0x7F , 0xFF , 0xC0 , 0x7F , 0xFF 
, 0xC0 , 0x7F , 0xFF , 0xC0 , 0x7F , 0xFF , 0xC0 , 0x3F , 0xFF , 0x80 , 0x0F 
, 0xFE , 0x00 , 0x0F , 0xFE , 0x00 , 0x0F , 0xFE , 0x00 , 0x0F , 0xFE , 0x00 
, 0x0F , 0xFE , 0x00 , 0x0F , 0xFE , 0x00 , 0x0F , 0xFE , 0x00 , 0x0F , 0xFE 
, 0x00 , 0x0F , 0xFE , 0x00 , 0x1F , 0xFF , 0x00 , 0x3F , 0xFF , 0x80 , 0x7F 
, 0xFF , 0xC0 , 0xFF , 0xFF , 0xE0 , 0xFF , 0xFF , 0xE0 , 0xFF , 0xFF , 0xE0 
, 0xFF , 0xFF , 0xE0 ,

21, 23, 0x00 , 0x00 , 0x00 , 0x03 , 0xF0 , 0x00 , 0x0F , 0xFC , 0x00 , 0x1C , 0xFE 
, 0x00 , 0x3B , 0xFF , 0x00 , 0x37 , 0xE7 , 0x80 , 0x7F , 0xFF , 0xC0 , 0x7F 
, 0xFF , 0xE0 , 0x7F , 0xFF , 0xE0 , 0x7F , 0xFF , 0xE0 , 0x7F , 0xE1 , 0xC0 
, 0x3F , 0xE0 , 0x00 , 0x3F , 0xF0 , 0x00 , 0x1F , 0xF0 , 0x00 , 0x1D , 0xF8 
, 0x00 , 0x0D , 0xF8 , 0x00 , 0x0D , 0xFC , 0x00 , 0x1B , 0xFE , 0x00 , 0x37 
, 0xFF , 0x00 , 0x7F , 0xFF , 0x80 , 0x7F , 0xFF , 0x80 , 0x7F , 0xFF , 0x80 
, 0x00 , 0x00 , 0x00 ,

21, 23, 0x03 , 0xF0 , 0x00 , 0x0F , 0xFC , 0x00 , 0x1F , 0xFE , 0x00 , 0x3F , 0xFF 
, 0x00 , 0x7F , 0xFF , 0x80 , 0x7F , 0xFF , 0xC0 , 0xFF , 0xFF , 0xE0 , 0xFF 
, 0xFF , 0xF0 , 0xFF , 0xFF , 0xF0 , 0xFF , 0xFF , 0xF0 , 0xFF , 0xFF , 0xF0 
, 0x7F , 0xFF , 0xE0 , 0x3F , 0xF9 , 0xC0 , 0x3F , 0xF8 , 0x00 , 0x3F , 0xFC 
, 0x00 , 0x1F , 0xFC , 0x00 , 0x1F , 0xFE , 0x00 , 0x3F , 0xFF , 0x00 , 0x7F 
, 0xFF , 0x80 , 0xFF , 0xFF , 0xC0 , 0xFF , 0xFF , 0xC0 , 0xFF , 0xFF , 0xC0 
, 0xFF , 0xFF , 0xC0 ,

21, 23, 0x00 , 0x00 , 0x00 , 0x00 , 0x40 , 0x00 , 0x00 , 0xE0 , 0x00 , 0x01 , 0xF0 
, 0x00 , 0x03 , 0xF8 , 0x00 , 0x03 , 0x18 , 0x00 , 0x06 , 0x0C , 0x00 , 0x06 
, 0xEC , 0x00 , 0x07 , 0xFC , 0x00 , 0x07 , 0xFC , 0x00 , 0x07 , 0xFC , 0x00 
, 0x01 , 0xF0 , 0x00 , 0x03 , 0x78 , 0x00 , 0x06 , 0xFC , 0x00 , 0x0E , 0xFE 
, 0x00 , 0x0F , 0xFE , 0x00 , 0x0D , 0xFE , 0x00 , 0x0D , 0xFE , 0x00 , 0x0D 
, 0xFE , 0x00 , 0x0F , 0xFE , 0x00 , 0x07 , 0xFC , 0x00 , 0x0F , 0xFE , 0x00 
, 0x00 , 0x00 , 0x00 ,

21, 23, 0x00 , 0x40 , 0x00 , 0x00 , 0xE0 , 0x00 , 0x01 , 0xF0 , 0x00 , 0x03 , 0xF8 
, 0x00 , 0x07 , 0xF8 , 0x00 , 0x07 , 0xFC , 0x00 , 0x0F , 0xFE , 0x00 , 0x0F 
, 0xFE , 0x00 , 0x0F , 0xFE , 0x00 , 0x0F , 0xFE , 0x00 , 0x0F , 0xFE , 0x00 
, 0x0F , 0xFE , 0x00 , 0x07 , 0xFC , 0x00 , 0x0F , 0xFF , 0x00 , 0x1F , 0xFF 
, 0x00 , 0x1F , 0xFF , 0x00 , 0x1F , 0xFF , 0x00 , 0x1F , 0xFF , 0x00 , 0x1F 
, 0xFF , 0x00 , 0x1F , 0xFF , 0x00 , 0x0F , 0xFE , 0x00 , 0x1F , 0xFF , 0x00 
, 0x1F , 0xFF , 0x00 ,

21, 23, 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x00 , 0x40 , 0x20 
, 0x10 , 0x60 , 0x70 , 0x30 , 0x30 , 0x70 , 0x60 , 0x38 , 0xF8 , 0xE0 , 0x38 
, 0xF8 , 0xC0 , 0x1D , 0xFD , 0xC0 , 0x1D , 0xFD , 0xC0 , 0x1E , 0xFB , 0xC0 
, 0x1E , 0xFB , 0xC0 , 0x1F , 0xDF , 0xC0 , 0x1F , 0xDF , 0xC0 , 0x1F , 0x27 
, 0xC0 , 0x1B , 0xDF , 0xC0 , 0x1B , 0xDF , 0xC0 , 0x1F , 0xFF , 0xC0 , 0x1D 
, 0xFF , 0xC0 , 0x1D , 0xFF , 0xC0 , 0x1D , 0xFF , 0xC0 , 0x0F , 0xFF , 0x80 
, 0x00 , 0x00 , 0x00 ,

21, 23, 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x00 , 0xC0 , 0x70 , 0x18 , 0xE0 , 0xF8 
, 0x38 , 0xF0 , 0xF8 , 0x78 , 0x79 , 0xFC , 0xF0 , 0x7D , 0xFD , 0xF0 , 0x7F 
, 0xFF , 0xF0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 
, 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF 
, 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F 
, 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x1F , 0xFF , 0xC0 
, 0x0F , 0xFF , 0x80 ,

21, 23, 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x00 , 0x40 , 0x20 
, 0x10 , 0x60 , 0x70 , 0x30 , 0x30 , 0x70 , 0x60 , 0x38 , 0xF8 , 0xE0 , 0x38 
, 0xF8 , 0xC0 , 0x1D , 0xFD , 0xC0 , 0x1D , 0xFD , 0xC0 , 0x1E , 0xFB , 0xC0 
, 0x1E , 0xFB , 0xC0 , 0x1E , 0xFB , 0xC0 , 0x1E , 0xFB , 0xC0 , 0x1F , 0xFF 
, 0xC0 , 0x1B , 0xFF , 0xC0 , 0x1B , 0xFF , 0xC0 , 0x0F , 0xFF , 0x80 , 0x0D 
, 0xFF , 0x80 , 0x0D , 0xFF , 0x80 , 0x0D , 0xFF , 0x80 , 0x0F , 0xFF , 0x80 
, 0x00 , 0x00 , 0x00 ,

21, 23, 0x00 , 0x00 , 0x00 , 0x00 , 0x20 , 0x00 , 0xC0 , 0x70 , 0x18 , 0xE0 , 0x70 
, 0x38 , 0xF0 , 0xF8 , 0x78 , 0x78 , 0xF8 , 0xF0 , 0x7D , 0xFD , 0xF0 , 0x7F 
, 0xFF , 0xF0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 
, 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF 
, 0xE0 , 0x3F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xE0 , 0x1F , 0xFF , 0xC0 , 0x1F 
, 0xFF , 0xC0 , 0x1F , 0xFF , 0xC0 , 0x1F , 0xFF , 0xC0 , 0x1F , 0xFF , 0xC0 
, 0x1F , 0xFF , 0xC0 ,

21, 23, 0x00 , 0x00 , 0x00 , 0x00 , 0xF0 , 0x00 , 0x01 , 0xB8 , 0x00 , 0x03 , 0x7C 
, 0x00 , 0x03 , 0x7C , 0x00 , 0x03 , 0xFC , 0x00 , 0x03 , 0xFC , 0x00 , 0x01 
, 0xF8 , 0x00 , 0x00 , 0xF0 , 0x00 , 0x00 , 0xF0 , 0x00 , 0x01 , 0xF8 , 0x00 
, 0x01 , 0x78 , 0x00 , 0x03 , 0x7C , 0x00 , 0x06 , 0xFE , 0x00 , 0x0D , 0xFF 
, 0x00 , 0x1B , 0xFF , 0x80 , 0x37 , 0xFF , 0xC0 , 0x6F , 0xFF , 0xE0 , 0x6F 
, 0xFF , 0xE0 , 0x7F , 0xFF , 0xE0 , 0x3F , 0xFF , 0xC0 , 0x7F , 0xFF , 0xE0 
, 0x00 , 0x00 , 0x00 ,

21, 23, 0x00 , 0xF0 , 0x00 , 0x01 , 0xF8 , 0x00 , 0x03 , 0xFC , 0x00 , 0x07 , 0xFE 
, 0x00 , 0x07 , 0xFE , 0x00 , 0x07 , 0xFE , 0x00 , 0x07 , 0xFE , 0x00 , 0x03 
, 0xFC , 0x00 , 0x01 , 0xF8 , 0x00 , 0x01 , 0xF8 , 0x00 , 0x03 , 0xFC , 0x00 
, 0x03 , 0xFC , 0x00 , 0x07 , 0xFE , 0x00 , 0x0F , 0xFF , 0x00 , 0x1F , 0xFF 
, 0x80 , 0x3F , 0xFF , 0xC0 , 0x7F , 0xFF , 0xE0 , 0xFF , 0xFF , 0xF0 , 0xFF 
, 0xFF , 0xF0 , 0xFF , 0xFF , 0xF0 , 0x7F , 0xFF , 0xE0 , 0xFF , 0xFF , 0xF0 
, 0xFF , 0xFF , 0xF0

};


void PutPiece (int x, int y, int piece,int b_w)
{
  putsprite(spr_and,9+21*x+10*y,15+10*y,pieces+852*b_w+piece*142 + 71);
  putsprite(spr_or,9+21*x+10*y,15+10*y,pieces+852*b_w+piece*142);
}


void DrawBoard()
{

  int     x,y,z,a,b;

  clg();

  for (x=1 ; x!=82; x++)
  {
    draw(x,x+30,x+170,x+30);
  }

  for (x=0 ; x!=8; x++)
  {
    for (y=0 ; y!=8; y++)
    {
      if (!((x+y) & 1))
      {
	  for (z=0 ; z!=9; z++)
	  {
	    a=3+21*x+10*y+z;
	    b=32+10*y+z;

	    undraw(a,b,a+20,b);
	  }
      }
    }
  }
}

