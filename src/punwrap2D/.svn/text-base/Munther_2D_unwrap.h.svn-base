#ifndef __MUNTHER_2D_UNWRAP
#define __MUNTHER_2D_UNWRAP

typedef unsigned char         BYTE;

//PIXELM information
struct PIXELM
{
  //int x;                        //x coordinate of the pixel
  //int y;                        //y coordinate
  int increment;                  //No. of 2*pi to add to the pixel to unwrap it
  int number_of_pixels_in_group;  //No. of pixel in the pixel group
  float value;                    //value of the pixel
  float reliability;
  BYTE input_mask;                //0 pixel is masked. 255 pixel is not masked
  BYTE extended_mask;             //0 pixel is masked. 255 pixel is not masked
  int group;                      //group No.
  int new_group;
  struct PIXELM *head;            //pointer to the first pixel in the group in the linked list
  struct PIXELM *last;            //pointer to the last pixel in the group
  struct PIXELM *next;            //pointer to the next pixel in the group
};

typedef struct PIXELM    PIXELM; 

//the EDGE is the line that connects two pixels.
//if we have S pixels, then we have S horizental edges and S vertical edges
struct EDGE
{    
  float reliab;	      //reliabilty of the edge and it depends on the two pixels
  PIXELM *pointer_1;  //pointer to the first pixel
  PIXELM *pointer_2;  //pointer to the second pixel
  int increment;      //No. of 2*pi to add to one of the pixels to unwrap it with respect to the second 
}; 

typedef struct EDGE       EDGE;  


int phase_unwrap_2D(float* WrappedImage, float* UnwrappedImage, 
                    BYTE* input_mask, int n_pe, int n_fe);  

typedef enum {yes, no} yes_no;
yes_no find_pivot(EDGE *left, EDGE *right, float *pivot_ptr);

EDGE *partition(EDGE *left, EDGE *right, float pivot);
void quicker_sort(EDGE *left, EDGE *right);
void  initialisePIXELs(float *WrappedImage, BYTE *input_mask, 
                       BYTE *extended_mask, PIXELM *pixel, int image_width, 
                       int image_height);
float wrap(float pixel_value);
int find_wrap(float pixelL_value, float pixelR_value);
void extend_mask(BYTE *input_mask, BYTE *extended_mask, int image_width, 
                 int image_height);
void calculate_reliability(float *wrappedImage, PIXELM *pixel, int image_width,
                           int image_height);
void  horizentalEDGEs(PIXELM *pixel, EDGE *edge, int image_width, 
                      int image_height);
void  verticalEDGEs(PIXELM *pixel, EDGE *edge, int image_width, 
                    int image_height);
void  gatherPIXELs(EDGE *edge, int image_width, int image_height);
void  unwrapImage(PIXELM *pixel, int image_width, int image_height);
void  maskImage(PIXELM *pixel, BYTE *input_mask, int image_width, 
                int image_height);
void returnImage(PIXELM *pixel, float *unwrappedImage, int image_width, 
                  int image_height);

#endif
