#ifndef __PNGEXPORT_DECLARATION__
#define __PNGEXPORT_DECLARATION__

#include <iostream>
#include <fstream>

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
    BIT32 crc;
    BIT8* data;
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

struct PNGDataChunk
{
    BIT8 colorData;
};

enum EchunkType : int
{
    HeaderChunk = 1,
    PaletteChunk,
    DataChunk,
    TrailerChunk
};

class PNGExport
{
    public:
        PNGExport(void*, int, int, int, std::string);
        ~PNGExport() = default;

        PNGExport(PNGExport const&) = delete;
        PNGExport(PNGExport &&) = delete;
        auto operator=(PNGExport const&) -> PNGExport = delete;
        auto operator=(PNGExport &&) -> PNGExport = delete;

        auto prepareChunk(int type, BIT8* data) -> PNGChunk;
        auto writeChunk(PNGChunk chunk) -> void;
        auto makeBIT32(int, int, int, int) -> BIT32;
        auto calcCRC(BIT8* data, unsigned int length) -> BIT32;

    private:
        void* inData;
        std::string pathFile;
        int width;
        int height;
        int sizePerData;

        std::ofstream file;
};

#endif //__PNGEXPORT_DECLARATION__
