#ifndef VIDEO_H
#define VIDEO_H

#include "common.h"
#include "vid_def.h"
#include "vid_typ.h"

extern Video_t g_Video;

// functions
void setVideo   (byte mode);
int  initVideo  (byte mode);
void quitVideo  ();
void render();

#endif/* VIDEO_H */
