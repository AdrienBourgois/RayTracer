#include "PNGExport.h"

PNGExport::PNGExport(void* _data, int _sizePerData, int _width, int _height, std::string _pathFile)
: inData(_data), pathFile(_pathFile), width(_width), height(_height), sizePerData(_sizePerData)
{
    this->file.open(this->pathFile);
}

auto PNGExport::prepareChunk(int type, BIT8* data) -> PNGChunk
{
    PNGChunk chunk;

    if (type == EchunkType::HeaderChunk)
    {
        chunk.length = 13;
        chunk.type = makeBIT32('I', 'H', 'D', 'R');
        chunk.data = data;
        //chunk.crc = calcCRC();
    }

    if (type == EchunkType::DataChunk)
    {

    }

    if (type == EchunkType::TrailerChunk)
    {

    }

    return chunk;
}

auto PNGExport::writeChunk(PNGChunk chunk) -> void
{

}

auto PNGExport::makeBIT32(int _1, int _2, int _3, int _4) -> BIT32
{
    BIT32 bytes = 0;
    BIT8* bytePointer = (BIT8*) &bytes;

    *(bytePointer) = _1;
    *(bytePointer + 1) = _2;
    *(bytePointer + 2) = _3;
    *(bytePointer + 3) = _4;

    return bytes;
}
