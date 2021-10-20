#include "glob.h"
#include "wifimgr.h"
#include "gfx.h"

int main() {

    // swiWaitForVBlank();
    initGfx();

    // Display loop
    while (true) {

        swiWaitForVBlank();
        manageWifi();


    }

    return 0;
}