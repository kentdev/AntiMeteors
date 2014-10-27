#include "antimain.h"

extern bool collided(object *a, object *b);

extern BITMAP *meteor;

_meteor meteors[MAX_METEORS];

void _meteor::init(int ax, int ay, float axv, float ayv)
{
  w = 10;
  h = 10;
  x = float(ax);
  y = float(ay);
  xv = axv;
  yv = ayv;
  life = 5;
  exists = true;
  particledelay = 0;
}

void _meteor::do_stuff()
{
  int i = 0;
  x += xv;
  y += yv;
  if (collided(this, &cannon))
  {
    exists = false;
    i = 0;
    while (i < 6)
    {  //if the cannon is hit, you lose instantly
      energy[i].exists = false;
      i++;
    }
  }
  i = 0;
  while (i < 6)
  {
    if (energy[i].exists)
    {
      if (collided(this, &energy[i]))
      {
        exists = false;
        energy[i].exists = false;
        new_particle(P_BOOM, int(energy[i].x + energy[i].w / 2), int(energy[i].y + energy[i].h / 2), 0, 0);
      }
    }
    i++;
  }
  
  particledelay++;
  if (particledelay > 2)
  {
    new_particle(P_BLIP, int(x) + rand()%int(w), int(y) + rand()%int(h), 0, 0);
    particledelay = 0;
  }
  
  i = 0;
  while (i < MAX_PEOPLE)
  {
    if (people[i].exists)
    {
      if (collided(this, &people[i]))
      {
        exists = false;
        people[i].exists = false;
        score += level * 10;
        new_particle(P_BOOM, int(x) + 5, int(y) + 6, 0, 0);
      }
    }
    i++;
  }
  if (y > 200)
  {
    exists = false;
  }
}

void _meteor::draw()
{
  buffer_draw_sprite(meteor, int(x), int(y));
}
