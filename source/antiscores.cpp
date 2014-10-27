#include "antimain.h"

typedef struct scorename
{
  int score;
  char name[5];
} scorename;

typedef struct scoreset
{
  scorename set[10];
} scoreset;

void enter_hiscore(scoreset &s);

int hiscores()
{
  static bool first = true;
  static short keydelay;
  static scoreset scores;

  short i;
  char temp[20];
  
  if (first)
  {
    ifstream dat("hiscores.dat");
    if (!dat.bad())
    {
      i = 0;
      while (i < 10)
      {
        dat >> scores.set[i].score >> scores.set[i].name;
        i++;
      }
    }
    else
    {
      i = 0;
      while (i < 10)
      {
        scores.set[i].score = 5000 - (i * 400);
        sprintf(scores.set[i].name, "KDV");
        i++;
      }
    }
    if (score < scores.set[9].score)
    {
      score = 0;
    }
    clear_particles();
    keydelay = 20;
    first = false;
  }
  
  do_particles();

  if (score > 0)
  {
    enter_hiscore(scores);
  }
  else
  {
    buffer_textout_centre_ex(font, "High Scores", 160, 30, WHITE);
    i = 0;
    while (i < 10)
    {
      sprintf(temp, "%-1d", scores.set[i].score);
      buffer_textout_right_ex(font, temp, 150, 50 + (10 * i), WHITE);
      buffer_textout_ex(font, scores.set[i].name, 170, 50 + (10 * i), WHITE);
      i++;
    }
    buffer_textout_centre_ex(font, "Press Enter", 160, 185, GREEN);
  
    if ((keydelay <= 0) && (key[KEY_ENTER]))
    {
      ofstream o("hiscores.dat");
      i = 0;
      while (i < 10)
      {
        o << scores.set[i].score << " " << scores.set[i].name << "\n";
        i++;
      }
      first = true;
      return MENU;
    }
    if (keydelay > 0) keydelay--;
  }
  
  return HISCORE;
}

void enter_hiscore(scoreset &s)
{
  static bool first = true, done;
  static char n[5];
  static char selected;
  static short initials;
  static short keydelay, donedelay;
  
  char t[2];
  short i;
  
  if (first)
  {
    sprintf(n, "");
    done = false;
    selected = 'A';
    initials = 0;
    first = false;
    keydelay = 20;
  }
  
  buffer_textout_centre_ex(font, "High Score!", 160, 20, WHITE);
  buffer_textout_centre_ex(font, "Enter your initials:", 160, 70, WHITE);
  buffer_textout_centre_ex(font, n, 160, 90, GREEN);
  
  if (!done)
  {
    sprintf(t, "%-1c", selected);
    buffer_textout_centre_ex(font, t, 160, 100, GREY);
  }
  
  if ((keydelay == 0) && (!done))
  {
    if ((key[KEY_Z]) || (key[KEY_X]))
    {
      n[initials] = selected;
      initials++;
      keydelay = 15;
    }
    if ((key[KEY_LEFT]) && (selected > 'A'))
    {
      selected--;
      keydelay = 15;
    }
    if ((key[KEY_RIGHT]) && (selected < 'Z'))
    {
      selected++;
      keydelay = 15;
    }
    if (initials >= 3)
    {
      done = true;
      donedelay = 50;
    }
  }
  
  if (keydelay > 0) keydelay--;
  
  if (done)
  {
    if (donedelay > 0)
    {
      donedelay--;
    }
    else
    {
      i = 9;
      while (score >= s.set[i].score)
      {
        s.set[i] = s.set[i - 1];
        if (score >= s.set[i].score)
        {
          i--;
        }
      }
      if (i < 0) i = 0;
      s.set[i].score = score;
      i = 0;
      while (i < 5)
      {
      	s.set[i].name[i] = n[i];
      	i++;
      }
      score = 0;
      first = true;
    }
  }
}
