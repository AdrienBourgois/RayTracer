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

#endif //__PNGEXPORT_DECLARATION__
