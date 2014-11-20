
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "picture.h"


//============================================================================
//                           Function definitions
//============================================================================
void ppm_write_to_file(picture* im, char* name)
{
  // Create file 
  FILE* ppm_tmp=fopen(name,"wb");

  // Write header
  fprintf(ppm_tmp, "P6\n%d %d\n255\n", im->width, im->height);

  // Write pixels
  fwrite(im->data, 3, im->width * im->height, ppm_tmp);

  // Close file
  fclose(ppm_tmp);
}

void ppm_read_from_file(picture* im, char* name)
{
  // Create file
  FILE* ppm_tmp=fopen(name,"rb");

  // Read file header
  fscanf(ppm_tmp, "P6\n%d %d\n255\n", &(im->width), &(im->height));

  // Allocate memory according to width and height
  im->data = (u_char*) malloc(3 * im->width * im->height * sizeof(*(im->data)));

  // Read the actual image data
  fread(im->data, 3, im->width * im->height, ppm_tmp);

  // Close file
  fclose(ppm_tmp);
}

void ppm_desaturate(picture* im)
{
  int x, y;

  // For each pixel ...
  for (x = 0 ; x < im->width ; x++)
  {
    for (y = 0 ; y < im->height ; y++)
    {
      u_int grey_lvl = 0;
      int rgb_canal;

      // Compute the grey level
      for (rgb_canal = 0 ; rgb_canal < 3 ; rgb_canal++)
      {
        grey_lvl += im->data[ 3 * (y * im->width + x) + rgb_canal ];
      }
      grey_lvl /= 3;
      assert(grey_lvl >= 0 && grey_lvl <=255);

      // Set the corresponding pixel's value in new_image
      memset(&(im->data[3 * (y * im->width + x)]), grey_lvl, 3);
    }
  }
}

void ppm_shrink(picture* im, int factor)
{
  // Compute new image size and allocate memory for the new image
  int new_width   = im->width / factor;
  int new_height  = im->height / factor;
  u_char* new_image = (u_char*) malloc(3 * new_width * new_height * sizeof(*new_image));

  // Precompute factor^2 (for performance reasons)
  int factor_squared = factor * factor;

  // For each pixel of the new image...
  int x, y;
  for (x = 0 ; x < new_width ; x++)
  {
    for (y = 0 ; y < new_height ; y++)
    {
      // ... compute the average RGB values of the set of pixels (a square of side factor)
      // that correspond to the pixel we are creating.

      // Initialize RGB values for the new image's pixel
      u_int red   = 0;
      u_int green = 0;
      u_int blue  = 0;

      // Compute coordinates and index of the first (top-left) pixel from the
      // model image corresponding to the pixel we are creating
      int x0 = x * factor;
      int y0 = y * factor;
      int i0 = 3 * (y0 * im->width + x0);

      // Compute RGB values for the new pixel
      int dx, dy;
      for (dx = 0 ; dx < factor ; dx++)
      {
        for (dy = 0 ; dy < factor ; dy++)
        {
          // Compute the offset of the current pixel (in the model image)
          // with regard to the top-left pixel of the current "set of pixels"
          int delta_i = 3 * (dy * im->width + dx);

          // Accumulate RGB values
          red   += im->data[i0+delta_i];
          green += im->data[i0+delta_i+1];
          blue  += im->data[i0+delta_i+2];
        }
      }

      // Divide RGB values to get the mean values
      red   /= factor_squared;
      green /= factor_squared;
      blue  /= factor_squared;

      // Set new pixel's RGB values
      new_image[ 3 * (y * new_width + x) ]     = red;
      new_image[ 3 * (y * new_width + x) + 1 ] = green;
      new_image[ 3 * (y * new_width + x) + 2 ] = blue;
    }
  }

  // Update image size
  im->width  = new_width;
  im->height = new_height;

  // Update image
  free(im->data);
  im->data = new_image;
}
