#include <iostream>
#include "support/compressor.h"

using namespace std;

int main(int argc, char **argv)
{
    // Get image file (default is running horse)
    // running-horse-square.png
    // lena_color.jpg
    const char *image_file =
        (argc > 1) ? argv[1] : srcPath("lena_color.jpg");

    // Creat a compressor
    // If we input a gray image, change the second parameter to false
    // If we want a constant compression threshold, we change last paramter to true
    Compressor *image = new Compressor(image_file, true, 100, false);

    // Reshape an image to a square image
    int square_size = image->get_square_size();

    // Encoding an image with Quadtree(s)
    image->encode(0, square_size, 0, square_size);

    // Decoding the QuadTree(s)
    image->decode(0, square_size, 0, square_size);

    // Display the decoded image
    image->display_decoded_iamge();

    // Release memeory
    delete image;

    // Exit
    return 0;
}
