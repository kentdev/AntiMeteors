#include "antimain.h"

volatile int counter;

void update_counter()
{
  counter++;
}
END_OF_FUNCTION(update_counter)

int level, score;
BITMAP *back_buffer;

DATAFILE *data;
BITMAP *world, *land, *overperson, *person[4], *power, *turret, *meteor;
SAMPLE *smallboom, *yell[3], *thud;

extern int menu();
extern int beforelogic();
extern int logic();
extern int blowup();
extern int hiscores();

short init_everything();

int main()
{
  short gamestatus;
  bool draw;
  
  if (init_everything() == 1)
  {
    return 1;
  }
  gamestatus = MENU;
  draw = false;
  
  while (gamestatus != QUIT)
  {
    while (counter > 0)
    {
      buffer_clear_to_color(BLACK);
      switch (gamestatus)
      {
        case MENU:
          gamestatus = menu();
          break;
        case BEFORE:
          gamestatus = beforelogic();
          break;
        case LOGIC:
          gamestatus = logic();
          break;
        case DEAD:
          gamestatus = blowup();
          break;
        case HISCORE:
          gamestatus = hiscores();
          break;
      }
      draw = true;
      counter--;
    }
    
    if (draw)
    {
      draw_all();
      stretch_blit(back_buffer, screen, 0, 0, 320, 200, 0, 0, 640, 400);
      draw = false;
    }
    
    if (counter < 1)
    {
      usleep(1);
    }
  }
  
  destroy_bitmap(back_buffer);
  unload_datafile(data);
  
  allegro_exit();
  return 0;
}
END_OF_MAIN()

short init_everything()
{
  allegro_init();
  install_keyboard();
  install_timer();
  
  BITMAP *temp;
  
  LOCK_VARIABLE(counter);
  LOCK_FUNCTION(update_counter);
  
  set_color_depth(16);
  if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 400, 0, 0) != 0)
  {
    allegro_message("Couldn't set up a graphics mode!");
    return 1;
  }
  
  install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
  
  data = load_datafile("anti.dat");
  if (!data)
  {
    allegro_message("Couldn't load anti.dat!");
    return 1;
  }
  
  world = (BITMAP *)data[0].dat;
  land = (BITMAP *)data[1].dat;
  overperson = (BITMAP *)data[2].dat;
  person[0] = create_sub_bitmap(overperson, 0, 0, 7, 7);
  person[1] = create_sub_bitmap(overperson, 7, 0, 7, 7);
  person[2] = create_sub_bitmap(overperson, 14, 0, 7, 7);
  person[3] = create_sub_bitmap(overperson, 21, 0, 7, 7);
  power = (BITMAP *)data[3].dat;
  turret = (BITMAP *)data[4].dat;
  meteor = (BITMAP *)data[5].dat;
  
  smallboom = (SAMPLE *)data[6].dat;
  yell[0] = (SAMPLE *)data[7].dat;
  yell[1] = (SAMPLE *)data[8].dat;
  yell[2] = (SAMPLE *)data[9].dat;
  thud = (SAMPLE *)data[10].dat;
  
  install_int_ex(update_counter, BPS_TO_TIMER(50));
  
  back_buffer = create_bitmap(320, 200);
  
  srand(time(NULL));
  
  return 0;
} 
