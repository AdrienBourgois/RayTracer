#include "Driver.h"
#include "gui.h"

int main()
{
    Gui_class* interface = new Gui_class();
    interface->open();

    while(interface->updateEvent())
    {
        interface->newFrame();
        interface->configWindow();
        interface->render();
    }

    delete interface;

    return EXIT_SUCCESS;
}
