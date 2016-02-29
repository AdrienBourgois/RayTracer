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
};

struct PNGHeaderChunk
:public PNGChunk
{
    BIT32 width;
    BIT32 height;
    BIT8  depth = 8;
    BIT8  colorType = 2;
    BIT8  compression = 0;
    BIT8  filter = 0;
    BIT8  interlace = 0;

    BIT8 size;
    auto getDataForCRC() -> BIT8*;
};

struct PNGDataChunk
:public PNGChunk
{
    BIT8* colorData;

    BIT8 size;
    auto getDataForCRC() -> BIT8*;
};

struct PNGTrailerChunk
:public PNGChunk
{

};

enum EchunkType : int
{
    HeaderChunk = 1,
    DataChunk,
    TrailerChunk
};

class PNGExport
{
    public:
        PNGExport(BIT8*, int, int, std::string);
        ~PNGExport();

        PNGExport(PNGExport const&) = delete;
        PNGExport(PNGExport &&) = delete;
        auto operator=(PNGExport const&) -> PNGExport = delete;
        auto operator=(PNGExport &&) -> PNGExport = delete;

        auto prepareChunk(int type) -> void;
        auto writeChunk(int type) -> void;
        auto makeBIT32(int, int, int, int) -> BIT32;
        auto calcCRC(BIT8* data, BIT32 length) -> BIT32;

        auto write() -> void;

    private:
        BIT8* dataPointer;
        std::string pathFile;
        BIT8* pixelsNumber;

        PNGHeaderChunk header;
        PNGDataChunk data;
        PNGTrailerChunk trailer;

        std::ofstream file;
};

#endif //__PNGEXPORT_DECLARATION__
