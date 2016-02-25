#ifndef __PNGEXPORT_DECLARATION__
#define __PNGEXPORT_DECLARATION__

#include <iostream>
#include <fstream>

class PNGExport
{
    public:
        PNGExport(void*, int, std::string);
        ~PNGExport();

        PNGExport(PNGExport const&) = delete;
        PNGExport(PNGExport &&) = delete;
        auto operator=(PNGExport const&) -> PNGExport = delete;
        auto operator=(PNGExport &&) -> PNGExport = delete;


    private:
        void* inData;
        std::string pathFile;
        int sizePerData;
        std::ofstream file;
};

typedef unsigned char BIT8;
typedef unsigned long BIT32;

struct PNGSignature
{
    BIT8 Signature[8] = {137, 80, 78, 71, 13, 10, 26, 10};
};

struct PNGChunk
{
    BIT32 length;
    BIT32 type;
    BIT8  data[];
    BIT32 crc;
};

struct PNGHeaderChunk
{
    BIT32 width;
    BIT32 height;
    BIT8  depth = 8;
    BIT8  colorType = 2;
    BIT8  compression = 0;
    BIT8  filter = 0;
    BIT8  interlace = 0;
};

struct PNGPaletteChunk
{
    BIT8 red;
    BIT8 green;
    BIT8 blue;
};

#endif //__PNGEXPORT_DECLARATION__
