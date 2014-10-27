#include "antimain.h"

//  This file (and antidraw.h) were taken from
//  my ongoing project Empire Allegro 2, and
//  modified to draw things using plain Allegro
//  instead of OpenLayer

vector<drawthing> drawqueue;

void draw_all()
{
  int i = 0;
  int s = drawqueue.size();
  drawthing t;
  while (i < s)
  {
    t = drawqueue[i];
    switch (t.type)
    {
      case DRAW_SPRITE:
        draw_sprite(back_buffer, t.bmp, t.x, t.y);
        break;
      case DRAW_SPRITE_H_FLIP:
        draw_sprite_h_flip(back_buffer, t.bmp, t.x, t.y);
        break;
      case ROTATE_SPRITE:
        rotate_sprite(back_buffer, t.bmp, t.x, t.y, t.angle);
        break;
      case STRETCH_SPRITE:
        stretch_sprite(back_buffer, t.bmp, t.x, t.y, t.w, t.h);
        break;
      case TEXTOUT_EX:
        textout_ex(back_buffer, t.fnt, t.str.c_str(), t.x, t.y, t.color, -1);
        break;
      case TEXTOUT_CENTRE_EX:
        textout_centre_ex(back_buffer, t.fnt, t.str.c_str(), t.x, t.y, t.color, -1);
        break;
      case TEXTOUT_RIGHT_EX:
        textout_right_ex(back_buffer, t.fnt, t.str.c_str(), t.x, t.y, t.color, -1);
        break;
      case CIRCLEFILL:
        circlefill(back_buffer, t.x, t.y, t.r, t.color);
        break;
      case RECT:
        rect(back_buffer, t.x, t.y, t.x + t.w, t.y + t.h, t.color);
        break;
      case RECTFILL:
        rectfill(back_buffer, t.x, t.y, t.x + t.w, t.y + t.h, t.color);
        break;
      case RECTROUNDED:
        rectfill(back_buffer, t.x + 1, t.y, t.x + t.w - 1, t.y + t.h, t.color);
        rect(back_buffer, t.x, t.y + 1, t.x + 1, t.y + t.h - 1, t.color);
        rect(back_buffer, t.x + t.w - 1, t.y + 1, t.x + t.w, t.y + t.h - 1, t.color);
        break;
      case ELLIPSEFILL:
        ellipsefill(back_buffer, t.x, t.y, t.rx, t.ry, t.color);
        break;
      case PUTPIXEL:
        putpixel(back_buffer, t.x, t.y, t.color);
        break;
      case LINE:
        line(back_buffer, t.x, t.y, t.x + t.w, t.y + t.h, t.color);
        break;
      case HLINE:
        hline(back_buffer, t.x, t.y, t.x + t.w, t.color);
        break;
      case VLINE:
        vline(back_buffer, t.x, t.y, t.y + t.h, t.color);
        break;
      case CLEAR_TO_COLOR:
        clear_to_color(back_buffer, t.color);
        break;
    }
    i++;
  }
  drawqueue.clear();
}

void buffer_draw_sprite(BITMAP *abitmap, int ax, int ay)
{
  drawthing t;
  t.type = DRAW_SPRITE;
  t.bmp = abitmap;
  t.x = ax;
  t.y = ay;
  drawqueue.push_back(t);
}

void buffer_draw_sprite_h_flip(BITMAP *abitmap, int ax, int ay)
{
  drawthing t;
  t.type = DRAW_SPRITE_H_FLIP;
  t.bmp = abitmap;
  t.x = ax;
  t.y = ay;
  drawqueue.push_back(t);
}

void buffer_rotate_sprite(BITMAP *abitmap, int ax, int ay, int32_t aangle)
{
  drawthing t;
  t.type = ROTATE_SPRITE;
  t.bmp = abitmap;
  t.x = ax;
  t.y = ay;
  t.angle = aangle;
  drawqueue.push_back(t);
}

void buffer_textout_ex(FONT *afont, string amessage, int ax, int ay, int acolor)
{
  drawthing t;
  t.type = TEXTOUT_EX;
  t.fnt = afont;
  t.str = amessage;
  t.x = ax;
  t.y = ay;
  t.color = acolor;
  drawqueue.push_back(t);
}

void buffer_textout_centre_ex(FONT *afont, string amessage, int ax, int ay, int acolor)
{
  drawthing t;
  t.type = TEXTOUT_CENTRE_EX;
  t.fnt = afont;
  t.str = amessage;
  t.x = ax;
  t.y = ay;
  t.color = acolor;
  drawqueue.push_back(t);
}

void buffer_textout_right_ex(FONT *afont, string amessage, int ax, int ay, int acolor)
{
  drawthing t;
  t.type = TEXTOUT_RIGHT_EX;
  t.fnt = afont;
  t.str = amessage;
  t.x = ax;
  t.y = ay;
  t.color = acolor;
  drawqueue.push_back(t);
}

void buffer_circlefill(int ax, int ay, int ar, int acolor)
{
  drawthing t;
  t.type = CIRCLEFILL;
  t.x = ax;
  t.y = ay;
  t.r = ar;
  t.color = acolor;
  drawqueue.push_back(t);
}

void buffer_rect(int ax, int ay, int bx, int by, int acolor)
{
  drawthing t;
  t.type = RECT;
  t.x = ax;
  t.y = ay;
  t.w = bx - ax;
  t.h = by - ay;
  if (t.w < 0) t.w = 0;
  if (t.h < 0) t.h = 0;
  t.color = acolor;
  drawqueue.push_back(t);
}

void buffer_ellipsefill(int ax, int ay, int arx, int ary, int acolor)
{
  drawthing t;
  t.type = ELLIPSEFILL;
  t.x = ax;
  t.y = ay;
  t.rx = arx;
  t.ry = ary;
  t.color = acolor;
  drawqueue.push_back(t);
}

void buffer_rectfill(int ax, int ay, int bx, int by, int acolor)
{
  drawthing t;
  t.type = RECTFILL;
  t.x = ax;
  t.y = ay;
  t.w = bx - ax;
  t.h = by - ay;
  if (t.w < 0) t.w = 0;
  if (t.h < 0) t.h = 0;
  t.color = acolor;
  drawqueue.push_back(t);
}

void buffer_rectrounded(int ax, int ay, int bx, int by, int acolor)
{
  drawthing t;
  t.type = RECTROUNDED;
  t.x = ax;
  t.y = ay;
  t.w = bx - ax;
  t.h = by - ay;
  if (t.w < 0) t.w = 0;
  if (t.h < 0) t.h = 0;
  t.color = acolor;
  drawqueue.push_back(t);
}

void buffer_putpixel(int ax, int ay, int acolor)
{
  drawthing t;
  t.type = PUTPIXEL;
  t.x = ax;
  t.y = ay;
  t.color = acolor;
  drawqueue.push_back(t);
}

void buffer_line(int ax, int ay, int bx, int by, int acolor)
{
  drawthing t;
  t.type = LINE;
  t.x = ax;
  t.y = ay;
  t.w = bx - ax;
  t.h = by - ay;
  t.color = acolor;
  drawqueue.push_back(t);
}

void buffer_hline(int ax, int ay, int bx, int acolor)
{
  drawthing t;
  t.type = HLINE;
  t.x = ax;
  t.y = ay;
  t.w = bx - ax;
  if (t.w < 0)
  {
    t.x = bx;
    t.w = ax - bx;
  }
  t.color = acolor;
  drawqueue.push_back(t);
}

void buffer_vline(int ax, int ay, int by, int acolor)
{
  drawthing t;
  t.type = VLINE;
  t.x = ax;
  t.y = ay;
  t.h = by - ay;
  if (t.h < 0)
  {
    t.y = by;
    t.h = ay - by;
  }
  t.color = acolor;
  drawqueue.push_back(t);
}

void buffer_clear_to_color(int acolor)
{
  drawthing t;
  t.type = CLEAR_TO_COLOR;
  t.color = acolor;
  drawqueue.push_back(t);
}
