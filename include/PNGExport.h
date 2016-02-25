#ifndef __PNGEXPORT_DECLARATION__
#define __PNGEXPORT_DECLARATION__

#include <iostream>

class PNGExport
{
    public:
        PNGExport(void*, std::string);
        ~PNGExport() = default;

        PNGExport(PNGExport const&) = delete;
        PNGExport(PNGExport &&) = delete;
        auto operator=(PNGExport const&) -> PNGExport = delete;
        auto operator=(PNGExport &&) -> PNGExport = delete;

    private:
        void* pointer;
        std::string pathFile;
};

typedef unsigned char BIT8;
typedef unsigned long BIT32;

struct PNGSignature
{
    BIT8 Signature[8];
};

struct PNGChunk
{
    BIT32 length;
    BIT32 type;
    BIT32 crc;
    BIT8  data[];
};

struct PNGHeaderChunk
{
    BIT32 width;
    BIT32 height;
    BIT8  depth;
    BIT8  colorType;
    BIT8  compression;
    BIT8  filter;
    BIT8  interlace;
};

struct PNGPaletteChunk
{
    BIT8 red;
    BIT8 green;
    BIT8 blue;
};

#endif //__PNGEXPORT_DECLARATION__
