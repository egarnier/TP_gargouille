//============================================================================
//                       Class and Functions declarations
//============================================================================
// Create a class of image that contains <width>, <height> and <data>

class picture{
 public:
  // Constructors
  picture(void);
  picture(const picture& im);

  // Getters
  int GetWidth(void) const;
  int GetHeight(void) const;
  u_char* GetData(void) const;

  // Functions
  // Write the image contained in <data> (of size <width> * <height>)
  // into plain RGB ppm file <file>
  void ppm_write_to_file(const char* name);
  // Read the image contained in plain RGB ppm file <file>
  // into <data> and set <width> and <height> accordingly
  // Warning: data is malloc_ed, don't forget to free it
  void ppm_read_from_file(const char* name);
  // Desaturate (transform to B&W) <image> (of size <width> * <height>)
  void ppm_desaturate();
  // Shrink image (of original size <width> * <height>) by factor <factor>
  // <width> and <height> are updated accordingly
  void ppm_shrink(int factor);
  
 private:
  int width;
  int height;
  u_char* data;
};


