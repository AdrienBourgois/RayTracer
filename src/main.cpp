#include "Device.h"

int main()
{
    Device* dev = new Device();

    dev->init();
   
    dev->run();
    
    dev->close();
    
    delete dev;
    
    return EXIT_SUCCESS;
}
