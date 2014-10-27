#include "antimain.h"

_cannon cannon;

extern BITMAP *turret;
extern SAMPLE *yell[3];

void _cannon::init()
{
  exists = true;
  life = 10;
  ammo = 5;
  firedelay = 0;
  ammodelay = 0;
  type = MATTER;
  angle = 64;
  x = 150;
  y = 175;
  w = 12;
  h = 5;
  maxammo = 5;
  reloadtime = 60;
}

void _cannon::do_stuff()
{
  int i;

  if (key[KEY_LEFT])
  {
    xv -= 0.05;
    if (xv < -1.5) xv = -1.5;
  }
  else if (key[KEY_RIGHT])
  {
    xv += 0.05;
    if (xv > 1.5) xv = 1.5;
  }
  else
  {
    if ((xv <= 0.07) && (xv >= -0.07))
    {
      xv = 0;
    }
    else
    {
      if (xv > 0)
      {
        xv -= 0.07;
      }
      else
      {
        xv += 0.07;
      }
    }
  }
  x += xv;
  if (x < 0) x = 0;
  if (x > 308) x = 308;
  
  if (key[KEY_Z])
  {
    angle += 2;
    if (angle > 108) angle = 108;
  }
  if (key[KEY_X])
  {
    angle -= 2;
    if (angle < 20) angle = 20;
  }
  
  if (firedelay > 0)
  {
    firedelay--;
  }
  else
  {
    firedelay = 0;
  }
  
  if (ammo < maxammo)
  {
    if (ammodelay > reloadtime)
    {
      ammo++;
      ammodelay = 0;
    }
    else
    {
      ammodelay++;
    }
  }
  
  if ((key[KEY_UP]) && (firedelay == 0) && (ammo > 0))
  {  //  fire!!!
    i = 0;
    while (i < MAX_PEOPLE)
    {
      if (!people[i].exists)
      {
        play_sample(yell[rand()%3], 128, 128, 1000, FALSE);
        people[i].init(x + w / 2 - 3, y, 3.0 * fixtof(fixcos(itofix(angle))), -3.0 * fixtof(fixsin(itofix(angle))));
        firedelay = 20;
        ammo--;
        i = MAX_PEOPLE;
      }
      i++;
    }
  }
}

void _cannon::draw()
{
  int fromx = int(x + w / 2) - 1;
  int fromy = int(y + 1);
  int destx = int(x) + int(w) / 2 + int(7 * fixtof(fixcos(itofix(angle)))) - 1;
  int desty = int(y) + 1 - int(7 * fixtof(fixsin(itofix(angle))));
  buffer_draw_sprite(turret, int(x), int(y));
  buffer_line(fromx, fromy, destx, desty, WHITE);
  buffer_line(fromx + 1, fromy, destx + 1, desty, WHITE);
  buffer_line(fromx, fromy + 1, destx, desty + 1, WHITE);
  buffer_line(fromx + 1, fromy + 1, destx + 1, desty + 1, WHITE);
}
