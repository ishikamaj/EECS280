// Project UID af1f95f547e44c8ea88730dfb185559d
 
#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
 
using namespace std;
 
 
// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory
 
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};
 
  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);
 
  // Capture our output
  ostringstream s;
  Image_print(img, s);
 
  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
 
  delete img; // delete the Image
}
 
TEST(test_image_width) {
  Image *img = new Image; // create an Image in dynamic memory
 
  Image_init(img, 2, 2);
  ASSERT_EQUAL(2, Image_width(img));
  
  Image *img2 = new Image;
  Image_init(img2, 6, 2);
  ASSERT_EQUAL(6, Image_width(img2));
 
  Image *img3 = new Image;
  Image_init(img3, 12, 2);
  ASSERT_EQUAL(12, Image_width(img3));
 
  delete img;
  delete img2;
  delete img3;
}
 
TEST(test_image_height) {
  Image *img = new Image;
 
  Image_init(img, 2, 2);
  ASSERT_EQUAL(2, Image_height(img));
  
  Image *img2 = new Image;
  Image_init(img2, 2, 6);
  ASSERT_EQUAL(6, Image_height(img2));
 
  Image *img3 = new Image;
  Image_init(img3, 2, 12);
  ASSERT_EQUAL(12, Image_height(img3));
 
  delete img;
  delete img2;
  delete img3;
}
 
TEST(test_Image_get_set_pixel) {
  Image *img = new Image;
 
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};
  const Pixel purple = {230, 230, 250};
  const Pixel yellow = {255, 240, 0};
 
  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);
 
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 1), green));
 
  Image *img2 = new Image;
  Image_init(img2, 4, 5);
  Image_set_pixel(img2, 0, 0, red);
  Image_set_pixel(img2, 0, 1, blue);
  Image_set_pixel(img2, 0, 2, red);
  Image_set_pixel(img2, 0, 3, green);
  Image_set_pixel(img2, 1, 0, white);
  Image_set_pixel(img2, 1, 1, purple);
  Image_set_pixel(img2, 1, 2, green);
  Image_set_pixel(img2, 1, 3, blue);
  Image_set_pixel(img2, 2, 0, red);
  Image_set_pixel(img2, 2, 1, yellow);
  Image_set_pixel(img2, 2, 2, red);
  Image_set_pixel(img2, 2, 3, red);
  Image_set_pixel(img2, 3, 0, purple);
  Image_set_pixel(img2, 3, 1, purple);
  Image_set_pixel(img2, 3, 2, green);
  Image_set_pixel(img2, 3, 3, blue);
  Image_set_pixel(img2, 4, 0, blue);
  Image_set_pixel(img2, 4, 1, yellow);
  Image_set_pixel(img2, 4, 2, purple);
  Image_set_pixel(img2, 4, 3, red);
 
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img2, 4, 2), purple));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img2, 0, 3), green));
 
  delete img;
  delete img2;
}
 
TEST(test_Image_fill) {
  Image *img = new Image;
 
  const Pixel red = {255, 0, 0};
  const Pixel purple = {230, 230, 250};
 
  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, red);
  Image_set_pixel(img, 1, 0, red);
  Image_set_pixel(img, 1, 1, red);
 
  Image *img2 = new Image;
  Image_init(img2, 2, 2);
  Image_fill(img2, red);
  ASSERT_TRUE(Image_equal(img, img2));

  Image *img3 = new Image;
  Image *img4 = new Image;
  Image_init(img3, 4, 5);
  Image_init(img4, 4, 5);
  Image_set_pixel(img3, 0, 0, purple);
  Image_set_pixel(img3, 0, 1, purple);
  Image_set_pixel(img3, 0, 2, purple);
  Image_set_pixel(img3, 0, 3, purple);
  Image_set_pixel(img3, 1, 0, purple);
  Image_set_pixel(img3, 1, 1, purple);
  Image_set_pixel(img3, 1, 2, purple);
  Image_set_pixel(img3, 1, 3, purple);
  Image_set_pixel(img3, 2, 0, purple);
  Image_set_pixel(img3, 2, 1, purple);
  Image_set_pixel(img3, 2, 2, purple);
  Image_set_pixel(img3, 2, 3, purple);
  Image_set_pixel(img3, 3, 0, purple);
  Image_set_pixel(img3, 3, 1, purple);
  Image_set_pixel(img3, 3, 2, purple);
  Image_set_pixel(img3, 3, 3, purple);
  Image_set_pixel(img3, 4, 0, purple);
  Image_set_pixel(img3, 4, 1, purple);
  Image_set_pixel(img3, 4, 2, purple);
  Image_set_pixel(img3, 4, 3, purple);
 
  Image_fill(img4, purple);
  ASSERT_TRUE(Image_equal(img3, img4));
  
  delete img;
  delete img2;
  delete img3;
  delete img4;
}
 
 
// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
