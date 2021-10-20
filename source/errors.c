#include "errors.h"

void throwErrorIf(bool condition, const char* errorMessage) {
    if (condition) throwError(errorMessage);
}

void throwError(const char* errorMessage) {
    consoleDemoInit();
    iprintf(errorMessage);
    // Wait 10s before shutoff
    for (int c=600; c>=0; c--) swiWaitForVBlank();
    // Shutoff
    exit(1);
}