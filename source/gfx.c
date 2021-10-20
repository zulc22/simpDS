#include "gfx.h"

void initGfx() {
    consoleDemoInit();
    // powerOn(POWER_ALL); // doesn't seem to do anything
    videoSetMode(MODE_5_2D);
    vramSetBankA(VRAM_A_MAIN_BG);
    bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
    // bgShow(3); // maybe i need this?
    iprintf("Logoscreen.bin size %zx\n", logoscreen_bin_size);
    memcpy(BG_GFX, logoscreen_bin, logoscreen_bin_size);
    iprintf("Memcpy finished\n");
}