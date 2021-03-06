#ifndef _draw_h
#define _draw_h

//  This file (and antidraw.cpp) were taken from
//  my ongoing project Empire Allegro 2, and
//  modified to draw things using plain Allegro
//  instead of OpenLayer

using namespace std;

#define DRAW_SPRITE        0
#define DRAW_SPRITE_H_FLIP 1
#define ROTATE_SPRITE      2
#define STRETCH_SPRITE     3
#define TEXTOUT_EX         4
#define TEXTOUT_CENTRE_EX  5
#define TEXTOUT_RIGHT_EX   15
#define CIRCLEFILL         6
#define RECT               7
#define RECTFILL           8
#define RECTROUNDED        9
#define PUTPIXEL           10
#define LINE               11
#define HLINE              12
#define VLINE              13
#define CLEAR_TO_COLOR     14
#define ELLIPSEFILL        16

typedef struct drawthing
{
  short type;
  short x, y, w, h, color;
  int32_t angle;  // 0 to 255
  int r;
  short rx, ry;
  string str;
  BITMAP *bmp;
  FONT *fnt;
} drawthing;

extern vector<drawthing> drawqueue;

void buffer_draw_sprite(BITMAP *abitmap, int ax, int ay);
void buffer_draw_sprite_h_flip(BITMAP *abitmap, int ax, int ay);
void buffer_rotate_sprite(BITMAP *abitmap, int ax, int ay, int32_t aangle);
void buffer_stretch_sprite(BITMAP *abitmap, int ax, int ay, int aw, int ah);

void buffer_textout_ex(FONT *afont, string amessage, int ax, int ay, int acolor);
void buffer_textout_centre_ex(FONT *afont, string amessage, int ax, int ay, int acolor);
void buffer_textout_right_ex(FONT *afont, string amessage, int ax, int ay, int acolor);
void buffer_circlefill(int ax, int ay, int ar, int acolor);
void buffer_rect(int ax, int ay, int bx, int by, int acolor);
void buffer_rectfill(int ax, int ay, int bx, int by, int acolor);
void buffer_rectrounded(int ax, int ay, int bx, int by, int acolor);
void buffer_putpixel(int ax, int ay, int acolor);
void buffer_ellipsefill(int ax, int ay, int rx, int ry, int acolor);
void buffer_line(int ax, int ay, int bx, int by, int acolor);
void buffer_hline(int ax, int ay, int bx, int acolor);
void buffer_vline(int ax, int ay, int by, int acolor);
void buffer_clear_to_color(int acolor);

void draw_all();

#endif
