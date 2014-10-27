#include "antimain.h"

void new_meteor();
void target_energy(int x, int y, float &xv, float &yv);
bool collided(object *a, object *b);
short meteors_in_play();

extern BITMAP *land, *person[3];

int beforelogic()
{
  static bool first = true;
  static short wait;
  static short timer[3];
  static short selected[3];
  static short stardelay;
  int i;
  char txt[20];
  
  if (first)
  {
    clear_particles();
    cannon.init();
    i = 0;
    while (i < 6)
    {
      energy[i].init(30 + (50 * i), 185);
      i++;
    }
    i = 0;
    while (i < MAX_METEORS)
    {
      meteors[i].exists = false;
      i++;
    }
    wait = 50;
    timer[0] = 100 + rand()%30;
    selected[0] = 1;
    timer[1] = 150 + rand()%30;
    selected[1] = 5;
    timer[2] = 200 + rand()%30;
    selected[2] = 60;
    first = false;
  }

  buffer_draw_sprite(land, 0, 174);
  cannon.draw();
  i = 0;
  while (i < 6)
  {
    energy[i].draw();
    i++;
  }
  buffer_textout_centre_ex(font, "Starting Conditions:", 160, 20, WHITE);
  buffer_textout_right_ex(font, "Difficulty: ", 170, 50, WHITE);
  buffer_textout_right_ex(font, "Ammo Capacity: ", 170, 80, WHITE);
  buffer_textout_right_ex(font, "Reload Time: ", 170, 110, WHITE);
  buffer_textout_centre_ex(font, "Protect the Energy Generators!", 160, 150, RED);
  
  if (wait > 0)
  {
    wait--;
  }
  else
  {
    sprintf(txt, "%-1d", selected[0]);
    buffer_textout_ex(font, txt, 190, 50, WHITE);
    sprintf(txt, "%-1d", selected[1]);
    buffer_textout_ex(font, txt, 190, 80, WHITE);
    sprintf(txt, "%-1d", selected[2]);
    buffer_textout_ex(font, txt, 190, 110, WHITE);
    
    if (wait == 0)
    {
      if (timer[0] > 0)
      {
        timer[0]--;
        selected[0]++;
        if (selected[0] > 20) selected[0] = 1;
      }
      if (timer[1] > 0)
      {
        timer[1]--;
        selected[1]++;
        if (selected[1] > 10) selected[1] = 3;
      }
      if (timer[2] > 0)
      {
        timer[2]--;
        selected[2]--;
        if (selected[2] < 30) selected[2] = 85;
      }
      if ((timer[0] == 0) && (timer[1] == 0) && (timer[2] == 0))
      {
        wait--;
      }
    }
    else
    {
      if (wait > -90)
      {
        wait--;
      }
      else
      {
        first = true;
        level = selected[0];
        cannon.maxammo = cannon.ammo = selected[1];
        cannon.reloadtime = selected[2];
        return LOGIC;
      }
    }
  }
  return BEFORE;
}

  

int logic()
{
  static bool first = true;
  static short stardelay, levelup;
  
  short maxmeteors = level + 3;
  short randmod = 200 - (level * 4);
  bool hasenergy;
  int i = 0;
  char txt[20];
  
  if (first)
  {
    clear_particles();
    score = 0;
    stardelay = 20;
    levelup = 0;
    i = 0;
    while (i < 32)
    {
      new_particle(P_STAR, i * 10, rand()%200, -0.4 + float(rand()%10) / 80, 0.0);
      i++;
    }
    i = 0;
    while (i < MAX_METEORS)
    {
      meteors[i].exists = false;
      i++;
    }
    i = 0;
    while (i < MAX_PEOPLE)
    {
      people[i].exists = false;
      i++;
    }
    first = false;
  }
  
  levelup++;
  if (levelup > 2000)
  {
    level++;
    if (cannon.reloadtime > 5)
    {
      cannon.reloadtime -= 3;
      new_particle(P_TEXT, 196, 25, 0, 0, "Reload Time -3!");
    }
    if (cannon.maxammo < 15)
    {
      cannon.maxammo++;
      new_particle(P_TEXT, 220, 15, 0, 0, "Max Ammo +1!");
    }
    new_particle(P_TEXT, 320, 100, -3, 0, "Difficulty Increased");
    
    levelup = 0;
  }
  
  if (randmod < 20) randmod = 20;
  if (rand()%randmod == 0)
  {
    if (meteors_in_play() < maxmeteors)
    {
      new_meteor();
    }
  }
  
  hasenergy = false;
  i = 0;
  while (i < 6)
  {
    if (energy[i].exists)
    {
      hasenergy = true;
    }
    i++;
  }
  if (!hasenergy)
  {
    first = true;
    return DEAD;
  }
  
  if (stardelay <= 0)
  {
    new_particle(P_STAR, 320, rand()%200, -0.4 + float(rand()%10) / 80, 0.0);
    stardelay = 20;
  }
  else
  {
    stardelay--;
  }
  
  do_particles(P_STAR | P_BLIP);
  
  i = 0;
  while (i < cannon.ammo)
  {
    buffer_draw_sprite(person[1], 310 - (10 * i), 3);
    i++;
  }
  
  sprintf(txt, "%-1d", score);
  buffer_textout_ex(font, txt, 0, 0, LGREY);
  
  i = 0;
  while (i < MAX_METEORS)
  {
    if (meteors[i].exists)
    {
      meteors[i].do_stuff();
      meteors[i].draw();
    }
    i++;
  }
  buffer_draw_sprite(land, 0, 174);
  cannon.do_stuff();
  cannon.draw();
  i = 0;
  while (i < MAX_PEOPLE)
  {
    if (people[i].exists)
    {
      people[i].do_stuff();
      people[i].draw();
    }
    i++;
  }
  i = 0;
  while (i < 6)
  {
    if (energy[i].exists)
    {
      energy[i].draw();
    }
    i++;
  }
  i = 0;
  while (i < MAX_METEORS)
  {
    if (meteors[i].exists)
    {
      meteors[i].do_stuff();
      meteors[i].draw();
    }
    i++;
  }

  do_particles((P_ALL ^ P_STAR) ^ P_BLIP);

  if (key[KEY_ESC])
  {
    first = true;
    return QUIT;
  }
  
  return LOGIC;
}

int blowup()
{
  static bool first = true;
  static short t, z;
  
  if (first)
  {
    clear_particles();
    t = 0;
    z = 0;
    first = false;
  }
  
  buffer_textout_centre_ex(font, "Game Over", 160, 50, WHITE);
  
  t++;
  z++;
  if (z < 160)
  {
    if (z < 150)
    {
      cannon.draw();
    }
    if (t > 3)
    {
      new_particle(P_BOOM, int(cannon.x) - 10 + rand()%(20 + int(cannon.w)), int(cannon.y) - 10 + rand()%(20 + int(cannon.h)), 0, 0);
      t = 0;
    }
  }
  else if (z > 250)
  {
    first = true;
    return HISCORE;
  }
  
  do_particles();
  
  return DEAD;
}

bool collided(object *a, object *b)
{
  if ((a->x + a->w > b->x) && (a->x < b->x + b->w))
  {
    if ((a->y + a->h > b->y) && (a->y < b->y + b->h))
    {
      return true;
    }
  }
  return false;
}

short meteors_in_play()
{
  short i = 0;
  short z = 0;
  while (i < MAX_METEORS)
  {
    if (meteors[i].exists)
    {
      z++;
    }
    i++;
  }
  return z;
}

void new_meteor()
{
  short i = 0;
  int x;
  float xv = 0, yv = 0;
  while (i < MAX_METEORS)
  {
    if (!meteors[i].exists)
    {
      x = rand()%320;
      target_energy(x, -20, xv, yv);
      meteors[i].init(x, -20, xv, yv);
      i = MAX_METEORS;
    }
    i++;
  }
}
      
void target_energy(int x, int y, float &xv, float &yv)
{
  bool out = false;
  short q = 0;
  int i = rand()%6;
  float t = float(250 + rand()%150);
  
  xv = (energy[i].x + energy[i].w / 2 - 3 - float(x)) / t;
  yv = (energy[i].y - float(y)) / t;
}
