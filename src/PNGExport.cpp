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
        chunk.length = 3;
        chunk.type = makeBIT32('I', 'D', 'A', 'T');
        //chunk.data = BIT8[];
        //chunk.crc = calcCRC();
    }

    if (type == EchunkType::TrailerChunk)
    {
        chunk.length = 0;
        chunk.type = makeBIT32('I', 'E', 'N', 'D');
        chunk.data = 0;
        //chunk.crc = calcCRC();
    }

    return chunk;
}

/* auto PNGExport::writeChunk(PNGChunk chunk) -> void
{

} */

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

auto PNGChunk::calcCRC() -> BIT32
{
    BIT8 data_whit_name_field[this->length + 4]; // Add 4 bytes for name field

    data_whit_name_field[0] = this->type;
    for (BIT32 i = 0; i < this->length; ++i)
        data_whit_name_field[i + 4] = this->data[i];

    BIT32 table[256];

    /* -----Make table----- */

    BIT32 c, n, k;

    for (n = 0; n < 256; ++n)
    {
        c = n;
        for (k = 0; k < 8; k++)
        {
            if (c & 1)
                c = 0xedb88320L ^ (c >> 1);
            else c = c >> 1;
        }
        table[n] = c;
    }

    /* ----Calc----- */

    c = 0xffffffffL;

    for (n = 0; n < (this->length + 4); n++)
        c = table[(c ^ data_whit_name_field[n]) & 0xff] ^ (c >> 8);

    return c ^ 0xffffffffL;
}
