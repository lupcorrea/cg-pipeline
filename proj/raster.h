#ifndef _RASTER_
#define _RASTER_

#include "pixel.h"

#include <stdio.h>

void drawPixel (Pixel p1);
void drawLine (Pixel p1, Pixel p2);
void drawTriangle (Pixel p1, Pixel p2, Pixel p3);

int biggerThanScreen (Pixel p1);

#endif

