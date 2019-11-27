#include "compressor.h"

Compressor::Compressor(const char* image_file, bool _isColor, int _threshold, bool _isConstantThreshold)
{
    isColor = _isColor;
    threshold = _threshold;
    isConstantThreshold = _isConstantThreshold;
    cout << "Loading image: " << image_file << endl;

    if (isColor)
    {
        loadColorImage(image_file, r, g, b, width, height);
        // Initialise 3 color channel with 0
        // Set gray, newGray and qyGray to 0
        newR = new byte[height*width]();
        newG = new byte[height*width]();
        newB = new byte[height*width]();
        gray = newGray = nullptr;
        qtGray = nullptr;
    }
    else
    {
        loadGreyImage(image_file, gray, width, height);
        // Initialize a gray image with 0
        newGray = new byte[height*width]();
        r = g = b = newR = newG = newB = nullptr;
        qtR = qtG = qtB = nullptr;
    }
    // Print statistics
    cout << "Image size: " << width << "x" << height << endl;
    cout << "Number of pixels: " << width*height << endl;
}

Compressor::~Compressor()
{
    // For one gray image or color image, release their memory in the end
    if (isColor)
    {
        delete []r;
        delete []g;
        delete []b;
        delete []newR;
        delete []newG;
        delete []newB;
    }
    else
    {
        delete []gray;
        delete []newGray;
    }
}

QuadTree<byte>* Compressor::encode_one_channel(byte *image, int hb, int he, int wb, int we)
{
    /*
    image representes an array for one channel;
    he: height begin
    hb: height end
    wb: width begin
    we: width end
    They are 4 coordinates of sub-sqaure like (hb, wb)->(he, we). For example, (0, 4) -> (4, 8)
    means a North-East sub-sqaure of an image 8*8.
    In order to construct a QuadTree, we descend recursively until we come across a pixel or
    a square with 4 identic values.
    */
    // Come across a pixel
    if ((he-hb) == 1 && (we-wb) == 1)
    {
        byte value;
        // In a squared image, some coordiantes may exceed the size of original image
        if (hb >= height || wb >= width)
        {
            //Set white
            value = byte(255);
        }
        // The current pixel is located in the image
        else
        {
            int pos = hb*width + wb;
            value = image[pos];
        }
        // Creat a leave
        QuadTree<byte> *ql = new QuadLeaf<byte>(value);
        ql->protect_leaves_from_destruction = true;
        return ql;
    }
    // hm means height middlle, wm mean width middle
    int hm = (hb+he)/2;
    int wm = (wb+we)/2;
    // Creat a QuadNode
    QuadTree<byte> *qn = new QuadNode<byte>();
    // 4 sons
    QuadTree<byte> *qNW, *qNE, *qSE, *qSW;
    // Cut the current image into 4 sub-image by manipulating its coordinates
    // (hb, wb)->(hm, wm) north-west
    qNW = encode_one_channel(image, hb, hm, wb, wm);
    // (hb, wm)->(hm, we) north-east
    qNE = encode_one_channel(image, hb, hm, wm, we);
    // (hm, wm)->(he, we) south-east
    qSE = encode_one_channel(image, hm, he, wm, we);
    // (hm, wb)->(he, wm) south-west
    qSW = encode_one_channel(image, hm, he, wb, wm);
    // Check if all sons are leaves for one node
    if (qNW->isLeaf() && qNE->isLeaf() && qSE->isLeaf() && qSW->isLeaf())
    {
        // Check if the treshold is variable
        if (!isConstantThreshold)
        {
            // Vary the treshold according to the size of region
            // Region increases, threshold decreases
            threshold = 255/(he-hb);
        }
        // Calculate intensity difference for 4 sons
        int diff = intensity_difference(qNW->value(), qNE->value(), qSE->value(), qSW->value());
        // Check if itensity difference is samller than the current threshold
        if (diff <= threshold)
        {
            // Return the current node as a leave with a mean value of its 4 sons
            byte value = byte((qNW->value()+qNE->value()+qSE->value()+qSW->value())/4);
            QuadTree<byte> *ql = new QuadLeaf<byte>(value);
            ql->protect_leaves_from_destruction = true;
            return ql;
        }
    }
    // At least one son is not a leave
    qn->son(NW) = qNW;
    qn->son(NE) = qNE;
    qn->son(SE) = qSE;
    qn->son(SW) = qSW;
    return qn;
}

void Compressor::encode(int hb, int he, int wb, int we)
{
    /*
    4 parameters of int are identic to function encode_one_channel
    For a gray image, call encode_one_channel once because of one channel
    for a color image, call encode_one_channel three times, because of 3 timnes
    */
    if(isColor)
    {
        qtR = encode_one_channel(r, hb, he, wb, we);
        qtG = encode_one_channel(g, hb, he, wb, we);
        qtB = encode_one_channel(b, hb, he, wb, we);
        cout << "Number of nodes: " << qtR->nTrees() + qtG->nTrees() + qtB->nTrees() << endl;
    }
    else
    {
        qtGray = encode_one_channel(gray, hb, he, wb, we);
        cout << "Number of nodes: " << qtGray->nTrees() << endl;
    }
}

void Compressor::decode_one_channel(QuadTree<byte>* qt, byte *image, int hb, int he, int wb, int we)
{
    /*
    qt means a QuadTree which is created in the stage of encoding
    image represent an array which is going to receive data from QuadTree
    Next 4 int parameters are identic to function encode_one_channel
    Descend resurvisely in the QuadTree
    */
    // If tree is not null
    if (qt != nullptr)
    {
        // If tree is leaf
        if (qt->isLeaf())
        {
            byte value = qt->value();
            fill_array(image, value, hb, he, wb, we);
        }
        // Otherwise if tree is a branch node
        else
        {
            int hm = (hb+he)/2;
            int wm = (wb+we)/2;
            decode_one_channel(qt->son(NW), image, hb, hm, wb, wm);
            decode_one_channel(qt->son(NE), image, hb, hm, wm, we);
            decode_one_channel(qt->son(SE), image, hm, he, wm, we);
            decode_one_channel(qt->son(SW), image, hm, he, wb, wm);
        }
    }
}

void Compressor::decode(int hb, int he, int wb, int we)
{
    /*
    4 parameters of int are identic to function encode_one_channel
    For a gray image, call decode_one_channel once because of one channel
    for a color image, call decode_one_channel three times, because of 3 timnes
    */
    if (isColor)
    {
        decode_one_channel(qtR, newR, hb, he, wb, we);
        decode_one_channel(qtG, newG, hb, he, wb, we);
        decode_one_channel(qtB, newB, hb, he, wb, we);
    }
    else
    {
        decode_one_channel(qtGray, newGray, hb, he, wb, we);
    }
}

void Compressor::fill_array(byte *image, byte value, int hb, int he, int wb, int we)
{
    /*
    image represents an array to stock all data of one image.
    Fill out the array with one value in a sub-square (hb, wb)->(he, we)
    */
   // Position in array
    int pos;
    // If one coordinate (h, w) is out of original image, ignore it.
    // Focus at only the original image.
    for (int h=hb; h<min(he, height); h++)
    {
        for (int w=wb; w<min(we, width); w++)
        {
            // Get position in the array
            pos = h*width+w;
            image[pos] = value;
        }
    }
}

int Compressor::get_square_size()
{
    /*
    One image is either square or rectangle. For any image, return a max size
    */
    return int(pow(2, ceil(log2(max(height, width)))));
}

void Compressor::display_decoded_iamge()
{
    // Display image
    Window window = openWindow(width, height);
    if (isColor)
    {
       putColorImage(IntPoint2(0,0), newR, newG, newB, width, height);
    }
    else
    {
        // Display image
        putGreyImage(IntPoint2(0,0), newGray, width, height);
    }
    // Pause
    click();
}

int intensity_difference(byte a, byte b, byte c, byte d)
{
    /*
    Calculate an intensity difference for 4 neighbor-leaves
    */
    int min_value = min(min(min(a, b), c), d);
    int max_value = max(max(max(a, b), c), d);
    return (max_value-min_value);
}
