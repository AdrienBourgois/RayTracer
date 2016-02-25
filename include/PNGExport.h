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

struct PNGChunck
{
    BIT32 length;
    BIT32 type;
    BIT32 crc;
    BIT8 data[];
};

#endif //__PNGEXPORT_DECLARATION__
