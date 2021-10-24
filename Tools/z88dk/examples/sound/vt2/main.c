// zcc +zx main.c sound.asm -lndos -create-app
// zcc +msx main.c sound.asm -subtype=rom -create-app
#include <stdio.h>
#include <intrinsic.h>
#include <interrupt.h>
#ifdef __SPECTRUM__
#include <spectrum.h>
#endif
#ifdef __MSX__
#include <msx.h>
#endif
#include <psg/vt2.h>
#include <stdlib.h>


#if __PC6001__ | __MULTI8__
#define NO_INTERRUPT 1
#endif

extern vt2_song mysong;

void playmusic(void) {
   M_PRESERVE_MAIN;
   M_PRESERVE_INDEX;
   ay_vt2_play();
   M_RESTORE_INDEX;
   M_RESTORE_MAIN;
}


void setup_int() {
#ifndef NO_INTERRUPT
#if __SPECTRUM__
   zx_im2_init(0xd300, 0xd4);
   add_raster_int(0x38);
#else
   im1_init();
#endif
   add_raster_int(playmusic);
#endif
}


void main()
{
   printf("%cVT2 Tracker example\n",12);

   // Load the tracker file
   ay_vt2_init(&mysong);
   // Set things up to play
   ay_vt2_start();

   // Setup interrupt
   setup_int();

   // Just loop
   while  ( 1 ) {
      int k = getk();
      switch ( k ) {
      case ' ':
          ay_vt2_stop();
          break;
      case 's':
          ay_vt2_start();
          break;
      }
#ifdef NO_INTERRUPT
       ay_vt2_play();
       msleep(40);
#endif
   }
}

