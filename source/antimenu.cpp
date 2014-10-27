#include "antimain.h"

extern BITMAP *world;

int menu()
{
  static bool first = true;
  static short selected, keydelay, stardelay;
  int i;
  string t;
  
  if (first)
  {
    clear_particles();
    selected = 0;
    keydelay = 10;
    stardelay = 20;
    score = 0;
    i = 0;
    while (i < 32)
    {
      new_particle(P_STAR, i * 10, rand()%200, -0.5 + float(rand()%10) / 30, 0.0);
      i++;
    }
    first = false;
  }
  
  if (stardelay <= 0)
  {
    new_particle(P_STAR, 320, rand()%200, -0.5 + float(rand()%10) / 30, 0.0);
    stardelay = 20;
  }
  else
  {
    stardelay--;
  }
  
  do_particles();
  buffer_draw_sprite(world, 107, 75);
  buffer_textout_centre_ex(font, "AntiMeteors", 160, 20, WHITE);
  
  i = 0;
  while (i < 3)
  {
    switch (i)
    {
      case 0:
        t = "Start Game";
        break;
      case 1:
        t = "High Scores";
        break;
      case 2:
        t = "Exit";
        break;
    }
    if (i == selected)
    {
      buffer_textout_centre_ex(font, t, 160, 60 + (20 * i), WHITE);
    }
    else
    {
      buffer_textout_centre_ex(font, t, 160, 60 + (20 * i), GREY);
    }
    i++;
  }
  
  if (keydelay <= 0)
  {
    if (key[KEY_UP])
    {
      selected--;
      if (selected < 0) selected = 2;
      keydelay = 10;
    }
    else if ((key[KEY_DOWN]) || (key[KEY_RSHIFT]))
    {
      selected++;
      if (selected > 2) selected = 0;
      keydelay = 10;
    }
    else if (key[KEY_ENTER])
    {
      first = true;
      switch(selected)
      {
        case 0:
          return BEFORE;
          break;
        case 1:
          return HISCORE;
          break;
        case 2:
          return QUIT;
          break;
      }
    }
  }
  else
  {
    keydelay--;
  }

  if (key[KEY_ESC])
  {
    return QUIT;
  }
      
  return MENU;
}
