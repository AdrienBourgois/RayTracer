#include "PNGExport.h"

PNGExport::PNGExport(BIT8* _dataPointer, int _pixelsNumber, std::string _pathFile)
: dataPointer(_dataPointer), pathFile(_pathFile)
{
    unsigned char a[4];
    a[0] = _pixelsNumber & 0xff;
    a[1] = (_pixelsNumber>>8)  & 0xff;
    a[2] = (_pixelsNumber>>16) & 0xff;
    a[3] = (_pixelsNumber>>24) & 0xff;

    this->pixelsNumber = a;

    this->file.open(this->pathFile, std::ofstream::binary | std::ofstream::trunc);
}

PNGExport::~PNGExport()
{
    this->file.close();
}

auto PNGExport::prepareChunk(int _type) -> void
{
    if (_type == EchunkType::HeaderChunk)
    {
        this->header.length = 13;
        this->header.type = makeBIT32('I', 'H', 'D', 'R');
        this->header.data = this->pixelsNumber;
        this->header.calcCRC();
    }

    if (_type == EchunkType::DataChunk)
    {
        this->data.length = 3;
        this->data.type = makeBIT32('I', 'D', 'A', 'T');
        this->data.data = this->dataPointer;
        this->data.calcCRC();
    }

    if (_type == EchunkType::TrailerChunk)
    {
        this->trailer.length = 0;
        this->trailer.type = makeBIT32('I', 'E', 'N', 'D');
        this->trailer.data = 0;
        this->trailer.calcCRC();
    }
}

auto PNGExport::writeChunk(PNGChunk chunk) -> void
{
    this->file << chunk.length;
    this->file << chunk.type;
    this->file << chunk.data;
    this->file << chunk.crc;
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

auto PNGExport::write() -> void
{
    prepareChunk(EchunkType::HeaderChunk); writeChunk(this->header);
    prepareChunk(EchunkType::DataChunk); writeChunk(this->data);
    prepareChunk(EchunkType::TrailerChunk); writeChunk(this->trailer);
}

auto PNGChunk::calcCRC() -> void
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

    this->crc = c ^ 0xffffffffL;
}
