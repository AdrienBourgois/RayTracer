#include "Device.h"
#include "gui.h"

int main()
{
    Gui_class* gui = new Gui_class();
    gui.open();

    while(gui.updateEvent())
    {
        gui.newFrame();
        gui.configWindow();
        gui.render();
    }

    /* Device* dev = new Device();

    dev->init();
   
    dev->run();
    
    dev->close();
    
    delete dev; */
    
    return EXIT_SUCCESS;
}
