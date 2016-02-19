#include "Driver.h"
#include "gui.h"

int main()
{
    Gui_class* interface = new Gui_class();
    interface->open();

    Driver* driver = new Driver();
    driver->init(1200, 800);

    while(interface->updateEvent())
    {
        driver->render();
        interface->newFrame();
        interface->configWindow();
        interface->render();
    }

    delete interface;

    return EXIT_SUCCESS;
}
