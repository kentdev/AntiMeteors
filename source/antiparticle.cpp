#include "antimain.h"

_particle particles[MAX_PARTICLES];

extern SAMPLE *smallboom;

void new_particle(int type, int x, int y, float xv, float yv, string txt)
{
  int i = 0;
  while (i < MAX_PARTICLES)
  {
    if (!particles[i].exists)
    {
      particles[i].init(type, float(x), float(y), xv, yv, txt);
      i = MAX_PARTICLES;
    }
    i++;
  }
}

void do_particles(int types)
{
  int i = 0;
  while (i < MAX_PARTICLES)
  {
    if (particles[i].exists)
    {
      if (types & particles[i].type)
      {
        particles[i].do_stuff();
        particles[i].draw();
      }
    }
    i++;
  }
}

void clear_particles()
{
  int i = 0;
  while (i < MAX_PARTICLES)
  {
    particles[i].exists = false;
    i++;
  }
}

void _particle::init(short atype, float ax, float ay, float axv, float ayv, string txt)
{
  type = atype;
  x = ax;
  y = ay;
  xv = axv;
  yv = ayv;
  text = txt;
  exists = true;
  switch (type)
  {
    case P_BLIP:
      life = 20;
      break;
    case P_BOOM:
      play_sample(smallboom, 128, 128, 1000, FALSE);
      life = 20;
      break;
    case P_STAR:
      life = 50;
      break;
    case P_TEXT:
      life = 200;
      break;
    case P_SPLAT:
      life = 2500;
      break;
    default:
      life = 0;
      break;
  }
}

void _particle::do_stuff()
{
  x += xv;
  y += yv;
  switch (type)
  {
    case P_BLIP:
      break;
    case P_BOOM:
      break;
    case P_STAR:
      if ((x < 0) || (x > 320) || (y < 0) || (y > 200))
      {
        exists = 0;
      }
      life++;
      break;
    case P_TEXT:
      break;
  }
  life--;
  if (life <= 0)
  {
    exists = false;
  }
}

void _particle::draw()
{
  int a, c;
  switch (type)
  {
    case P_BLIP:
      buffer_putpixel(int(x), int(y), WHITE);
      break;
    case P_BOOM:
      a = rand()%3;
      if (a == 0) c = RED;
      if (a == 1) c = ORANGE;
      if (a == 2) c = YELLOW;
      buffer_circlefill(int(x), int(y), (20 - life) / 2, c);
      break;
    case P_STAR:
      buffer_putpixel(int(x), int(y), WHITE);
      break;
    case P_TEXT:
      buffer_textout_ex(font, text, int(x), int(y), GREEN);
      break;
    case P_SPLAT:
      buffer_ellipsefill(int(x), int(y), 5, 2, RED);
      break;
  }
}
