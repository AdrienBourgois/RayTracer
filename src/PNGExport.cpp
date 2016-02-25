#include "PNGExport.h"

PNGExport::PNGExport(void* _data, int _sizePerData, int _width, int _height, std::string _pathFile)
: inData(_data), pathFile(_pathFile), width(_width), height(_height), sizePerData(_sizePerData)
{
    this->file.open(this->pathFile);
}
