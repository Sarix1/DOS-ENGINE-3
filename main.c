#include "common.h"
#include "system.h"

int main(void)
{
    init();

    while (1) // while (System.running)
    {
        input();
        // logic();
        physics();
        draw();
        render();
    }

    quit();

    return 0;
}
