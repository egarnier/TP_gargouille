
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
  picture gargouille;
  gargouille.ppm_read_from_file("gargouille.ppm");


  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Creation and copy image into image_bw
  picture gargouille_bw = picture(gargouille);

  // Desaturate image_bw
  gargouille_bw.ppm_desaturate();

  // Write the desaturated image into "gargouille_BW.ppm"
  gargouille_bw.ppm_write_to_file("gargouille_BW.ppm");


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Creation and copy image into image_small
  picture gargouille_small = picture(gargouille);

  // Shrink image_small size 2-fold
  gargouille_small.ppm_shrink(2);

  // Write the desaturated image into "gargouille_small.ppm"
  gargouille_small.ppm_write_to_file("gargouille_small.ppm");


  // Delete the picture
  delete(gargouille.GetData());
  delete(gargouille_bw.GetData());
  delete(gargouille_small.GetData());

  return 0;
}
