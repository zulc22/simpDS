#include "glob.h"
#include <nds/arm9/video.h>
#include <nds/arm9/decompress.h>

void initGfx() {
    videoSetMode(MODE_FB0);
    videoSetModeSub(MODE_FB1);
    // memcpy(logodata, VRAM_A, logolen)
}