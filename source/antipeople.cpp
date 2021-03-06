#include "antimain.h"

_people people[MAX_PEOPLE];

extern BITMAP *person[4];
extern SAMPLE *thud;

void _people::init(float ax, float ay, float axv, float ayv)
{
  exists = true;
  life = 5;
  x = ax;
  y = ay;
  xv = axv;
  yv = ayv;
  w = 7;
  h = 7;
  frame = 0;
}

void _people::do_stuff()
{
  x += xv;
  y += yv;
  yv += 0.02;
  if ((x < 0) || (x + w > 320))
  {
    exists = false;
  }
  if ((y > cannon.y + cannon.h) || (y < -75.0))
  {
    exists = false;
    play_sample(thud, 128, 128, 1000, FALSE);
    new_particle(P_SPLAT, int(x) + 2, int(y) + rand()%3, 0, 0);
  }
}

void _people::draw()
{
  frame += 0.2;
  if (frame >= 4) frame = 0;
  int32_t angle = fixatan2(ftofix(yv), ftofix(xv)) + itofix(64);
  buffer_rotate_sprite(person[int(frame)], int(x), int(y), angle);
}
