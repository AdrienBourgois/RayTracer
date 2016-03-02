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
    }

    if (_type == EchunkType::DataChunk)
    {
        this->data.length = this->header.width * this->header.height;
        this->data.type = makeBIT32('I', 'D', 'A', 'T');
    }

    if (_type == EchunkType::TrailerChunk)
    {
        this->trailer.length = 0;
        this->trailer.type = makeBIT32('I', 'E', 'N', 'D');
        this->trailer.crc = 0xAE426082;
    }
}

auto PNGExport::writeData(BIT8 data) -> void
{
    this->file.write((char*)&data, sizeof(data));
    this->CRCVector.push_back(data);
}

auto PNGExport::writeData(BIT32 data, bool rev) -> void
{
    if(rev)
    {
        for (int i = 3; i >= 0; i--)
        {
            BIT8* bytePointer = (BIT8*) &data;
            this->file.write((char*)&bytePointer[i], sizeof(BIT8));
            this->CRCVector.push_back((BIT8)bytePointer[i]);
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            BIT8* bytePointer = (BIT8*) &data;
            this->file.write((char*)&bytePointer[i], sizeof(BIT8));
            this->CRCVector.push_back((BIT8)bytePointer[i]);
        }
    }
}

auto PNGExport::writeChunk(int type) -> void
{
    this->CRCVector.clear();

    if (type == EchunkType::HeaderChunk)
    {
        writeData(this->header.length, true);
        writeData(this->header.type);
        writeData(this->header.width, true);
        writeData(this->header.height, true);
        writeData(this->header.depth);
        writeData(this->header.colorType);
        writeData(this->header.compression);
        writeData(this->header.filter);
        writeData(this->header.interlace);
        this->header.crc = calcCRC(this->header.getDataForCRC(), this->header.length + 4);
        writeData(this->header.crc, true);
    }
    if (type == EchunkType::DataChunk)
    {
        writeData(this->data.length, true);
        writeData(this->data.type);
        for (unsigned int i = 0; i < ((this->header.width * this->header.height)*3); i++)
        {
            BIT8* bytePointer = (BIT8*) &this->data.colorData;
            this->file.write((char*)&bytePointer[i], sizeof(BIT8));
        }
        this->data.crc = calcCRC(this->data.getDataForCRC(), this->data.length + 4);
        writeData(this->data.crc, true);
    }
    if (type == EchunkType::TrailerChunk)
    {
        writeData(this->trailer.length, true);
        writeData(this->trailer.type);
        writeData(this->trailer.crc, true);
    }
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
    PNGSignature signature;
    for (int i = 0; i < 8; ++i)
        this->file.write((char*)&signature.Signature[i], sizeof(BIT8));
    prepareChunk(EchunkType::HeaderChunk); writeChunk(EchunkType::HeaderChunk);
    //prepareChunk(EchunkType::DataChunk); writeChunk(EchunkType::DataChunk);
    //prepareChunk(EchunkType::TrailerChunk); writeChunk(EchunkType::TrailerChunk);
}

auto PNGExport::calcCRC() -> BIT32
{
    this->CRCVector.erase(this->CRCVector.begin(), this->CRCVector.begin()+4);

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

    for (n = 0; n < (this->CRCVector.size()); n++)
        c = table[(c ^ this->CRCVector[n]) & 0xff] ^ (c >> 8);

    std::cout << "-->" << std::hex << (c ^ 0xffffffffL) << std::dec << std::endl;
    return c ^ 0xffffffffL;
}
