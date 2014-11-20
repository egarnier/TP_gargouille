
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "picture.h"


//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  picture* gargouille;
  gargouille=(picture*)malloc(sizeof(gargouille));
  ppm_read_from_file(gargouille, "gargouille.ppm");


  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Creation and copy image into image_bw
  picture* gargouille_bw;
  gargouille_bw=(picture*)malloc(sizeof(gargouille_bw));
  gargouille_bw->width  = gargouille->width;
  gargouille_bw->height = gargouille->height;
  gargouille_bw->data = (u_char*) malloc(3 * gargouille->width * gargouille->height * sizeof(*(gargouille_bw->data)));
  memcpy(gargouille_bw->data, gargouille->data, 3 * gargouille_bw->width * gargouille_bw->height * sizeof(*(gargouille_bw->data)));

  // Desaturate image_bw
  ppm_desaturate(gargouille_bw);

  // Write the desaturated image into "gargouille_BW.ppm"
  ppm_write_to_file(gargouille_bw,"gargouille_BW.ppm");

  // Free the desaturated image
  free(gargouille_bw->data);
  free(gargouille_bw);

  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Creation and copy image into image_small
  picture* gargouille_small;
  gargouille_small=(picture*)malloc(sizeof(gargouille_small));
  gargouille_small->width  = gargouille->width;
  gargouille_small->height = gargouille->height;
  gargouille_small->data = (u_char*) malloc(3 * gargouille->width * gargouille->height * sizeof(*(gargouille_small->data)));
  memcpy(gargouille_small->data, gargouille->data, 3 * gargouille_small->width * gargouille_small->height * sizeof(*(gargouille_small->data)));

  // Shrink image_small size 2-fold
  ppm_shrink(gargouille_small, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  ppm_write_to_file(gargouille_small, "gargouille_small.ppm");

  // Free the not yet freed images
  free(gargouille_small->data);
  free(gargouille_small);
  free(gargouille->data);
  free(gargouille);

  return 0;
}
