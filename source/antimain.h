#ifndef _anti_h
#define _anti_h

#include <allegro.h>
#ifdef MINGDIR
#include <winalleg.h>
#endif
#include <time.h>
#include <vector>
#include <string>
#include <fstream.h>
#include "antidraw.h"

#define MAX_PARTICLES 300
#define MAX_METEORS   20
#define MAX_PEOPLE    20

#define BLACK makecol(0, 0, 0)
#define GREY makecol(128, 128, 128)
#define LGREY makecol(192, 192, 192)
#define DGREY makecol(64, 64, 64)
#define VDGREY makecol(32, 32, 32)
#define RED makecol(255, 0, 0)
#define GREEN makecol(0, 255, 0)
#define DGREEN makecol(0, 150, 0)
#define BLUE makecol(0, 0, 255)
#define YELLOW makecol(255, 255, 0)
#define DYELLOW makecol(150, 150, 0)
#define WHITE makecol(255, 255, 255)
#define ORANGE makecol(255, 128, 0)
#define BROWN makecol(150, 100, 50)
#define DBROWN makecol(100, 70, 40)
#define TRANS makecol(255, 0, 255)

#define QUIT    0
#define MENU    1
#define BEFORE  2
#define LOGIC   3
#define DEAD    4
#define HISCORE 5

#define MATTER     0
#define ANTIMATTER 1

#define P_BLIP   1
#define P_BOOM   2
#define P_STAR   4
#define P_TEXT   8
#define P_SPLAT 16
#define P_ALL   31

extern int level;
extern int score;
extern BITMAP *back_buffer;

typedef struct object
{
  float x, y, xv, yv;
  float w, h;
  short type;  //matter or antimatter
  short life;  //very short, usually [/lame attempt at joke]
  bool exists;
  
  virtual void do_stuff() = 0;
  virtual void draw() = 0;
} object;

typedef struct _cannon : object
{
  short firedelay;
  short ammodelay;
  short reloadtime;
  short maxammo;
  short ammo;
  int angle;

  void init();
  void do_stuff();
  void draw();
} _cannon;

typedef struct _energy : object
{
  void init(int x, int y);
  void do_stuff();
  void draw();
} _energy;

typedef struct _meteor : object
{
  short particledelay;
  
  void init(int x, int y, float xv, float yv);
  void do_stuff();
  void draw();
} _meteor;

typedef struct _people : object
{
  float frame;
  
  void init(float x, float y, float xv, float yv);
  void do_stuff();
  void draw();
} _people;

typedef struct _particle : object
{
  short color;
  string text;
  
  void init(short type, float x, float y, float xv, float yv, string txt);
  void do_stuff();
  void draw();
} _particle;

extern void new_particle(int type, int x, int y, float xv, float yv, string txt = "");
extern void do_particles(int types = P_ALL);
extern void clear_particles();

extern _cannon cannon;
extern _meteor meteors[MAX_METEORS];
extern _people people[MAX_PEOPLE];
extern _energy energy[6];

#endif
