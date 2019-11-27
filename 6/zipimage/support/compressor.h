#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <Imagine/Graphics.h>
#include <iostream>
#include <string>
#include "../quadtree/quadtree.h"

using namespace std;
using namespace Imagine;

// Set up a class to eencode one image and decode an image
// with QuadTree structure
class Compressor
{
    // threshold for intensity difference of 4 pixels
    int height, width, threshold;

    // Check threshold is constant or variant, check a image is in color or in gray
    bool isConstantThreshold, isColor;

    // Matrix for a gray image and a new gray image by decoding
    byte *gray, *newGray;

    // Matrix for a color image and a new color image by decoing
    byte *r, *g, *b, *newR, *newG, *newB;

    // QuadTree for gray image and color image
    QuadTree<byte> *qtGray, *qtR, *qtG, *qtB;
public:
    // Initialize our compressor by inputing a image file path and a series of parameters
    Compressor(const char* image_file, bool _isColor, int _threshold=0, bool _isConstantThreshold=true);

    // Deconstructor
    ~Compressor();

    // Encode for one channel. Return a QuadTree. 4 int represente a sub-square (h0, b0) -> (h1, b1)
    QuadTree<byte>* encode_one_channel(byte*, int, int, int, int);

    // Encode a whole image. If a gray image, one channel; if a color image, 3 channels
    void encode(int, int, int, int);

    // Decode one channel from a QuadTree
    void decode_one_channel(QuadTree<byte>*, byte*, int, int, int, int);

    // Decode a whole image. One channel for a gray image, 3 channels for a color image
    void decode(int, int, int, int);

    // Fill a pixel or a sub-square with one value in order to generate a new image by decoding
    void fill_array(byte*, byte, int, int, int, int);

    // Reshape an image to a square
    int get_square_size();

    // Display a new image by decoding
    void display_decoded_iamge();
};

// Calculate an intensity difference for 4 neighbor-pixles
int intensity_difference(byte, byte, byte, byte);

#endif // COMPRESSOR_H
