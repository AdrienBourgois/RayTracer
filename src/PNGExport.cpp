#include "PNGExport.h"

PNGExport::PNGExport(BIT8* _dataPointer, int _width, int _height, std::string _pathFile)
: dataPointer(_dataPointer), pathFile(_pathFile)
{
    this->header.width = _width;
    this->header.height = _height;
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
        this->header.crc = calcCRC(this->header.getDataForCRC(), this->header.length + 4);
    }

    if (_type == EchunkType::DataChunk)
    {
        this->data.length = this->header.width * this->header.height;
        this->data.type = makeBIT32('I', 'D', 'A', 'T');
        this->data.crc = calcCRC(this->data.getDataForCRC(), this->data.length + 4);
    }

    if (_type == EchunkType::TrailerChunk)
    {
        this->trailer.length = 0;
        this->trailer.type = makeBIT32('I', 'E', 'N', 'D');
        this->trailer.crc = 0xAE426082;
    }
}

auto PNGExport::writeChunk(int type) -> void
{
    this->file << this->header.length;
    this->file << this->header.type;
    if (type == EchunkType::HeaderChunk)
        this->file << this->header.width << this->header.height << this->header.depth << this->header.colorType << this->header.compression << this->header.filter << this->header.interlace;
    if (type == EchunkType::DataChunk)
        this->file << this->data.colorData;
    this->file << this->header.crc;
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
    prepareChunk(EchunkType::HeaderChunk); writeChunk(EchunkType::HeaderChunk);
    prepareChunk(EchunkType::DataChunk); writeChunk(EchunkType::DataChunk);
    prepareChunk(EchunkType::TrailerChunk); writeChunk(EchunkType::TrailerChunk);
}

auto PNGHeaderChunk::getDataForCRC() -> BIT8*
{
    BIT8* CRCdata = new BIT8[(2*4) + 5]; // 2 * BIT32 fields and 5 * BIT8 fields

    CRCdata[0] = this->width & 0xff;
    CRCdata[1] = (this->width >> 8)  & 0xff;
    CRCdata[2] = (this->width >> 16) & 0xff;
    CRCdata[3] = (this->width >> 24) & 0xff;
    CRCdata[4] = this->height & 0xff;
    CRCdata[5] = (this->height >> 8)  & 0xff;
    CRCdata[6] = (this->height >> 16) & 0xff;
    CRCdata[7] = (this->height >> 24) & 0xff;
    CRCdata[8] = this->depth;
    CRCdata[9] = this->colorType;
    CRCdata[10]= this->compression;
    CRCdata[11]= this->filter;
    CRCdata[12]= this->interlace;

    return CRCdata;
}

auto PNGDataChunk::getDataForCRC() -> BIT8*
{
    BIT8* CRCdata = new BIT8[this->length + 4]; // Add 4 bytes for name field
    CRCdata[0] = this->type;

    for (BIT32 i = 0; i < this->length; ++i)
        CRCdata[i + 4] = this->colorData[i];

    return CRCdata;
}

auto PNGExport::calcCRC(BIT8* data, BIT32 length) -> BIT32
{
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

    for (n = 0; n < (length + 4); n++)
        c = table[(c ^ data[n]) & 0xff] ^ (c >> 8);

    delete data;

    return c ^ 0xffffffffL;
}
