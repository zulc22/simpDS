#include "glob.h"

struct wifiDisplayInfo
{
    bool isConnecting;
    const char* status;
};

void manageWifi();
struct wifiDisplayInfo generateWifiDisplayInfo();
const char* wifiAssocStatusDisplayStr(int assocstatus);