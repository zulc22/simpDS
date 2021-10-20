#include "gfx.h"

#include "logoscreen_bm.h"

void initGfx() {
    consoleDemoInit();

    // powerOn(POWER_ALL); // doesn't seem to do anything
    videoSetMode(MODE_5_2D);
    vramSetBankA(VRAM_A_MAIN_BG);
    bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

    iprintf("Logoscreen_bm size %zx\n", logoscreen_bmBitmapLen);
    memcpy(BG_GFX, logoscreen_bmBitmap, logoscreen_bmBitmapLen);
    iprintf("Memcpy finished\n");
}