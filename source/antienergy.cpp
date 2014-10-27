#include "antimain.h"

_energy energy[6];

extern BITMAP *power;

void _energy::init(int ax, int ay)
{
  exists = true;
  life = 15;
  x = float(ax);
  y = float(ay);
  xv = 0;
  yv = 0;
  w = 15;
  h = 15;
}

void _energy::do_stuff()
{
}

void _energy::draw()
{
  buffer_draw_sprite(power, int(x), int(y));
}
