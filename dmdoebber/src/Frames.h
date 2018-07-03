#ifndef FPS_H_INCLUDED
#define FPS_H_INCLUDED

#include <stdio.h>
#include <time.h>

#define UPDATE_RATE 300

/// PEGUEI DA DEMO FPS
class Frames{
   clock_t t1, t2;
   long    cont_frames;
   float   fps, fps_old;
public:
   Frames()
   {
      t1 = clock();
	  cont_frames = 0;
      fps_old = 20;
   }

   float getFrames()
   {
      double tempo;

      t2 = clock();
      tempo  = (double)(t2 - t1);
      cont_frames++;

      if( tempo > UPDATE_RATE )
      {
         t1 = t2;
         fps = cont_frames / (tempo/CLOCKS_PER_SEC);
         cont_frames = 0;
         fps_old = fps;

         return fps;
      }

      return fps_old;
   }
};

#endif // FPS_H_INCLUDED
