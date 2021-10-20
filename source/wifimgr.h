#include "glob.h"

struct wifiDisplayInfo
{
    bool isConnecting;
    bool isConnected;
    const char* status;
};

void manageWifi();
struct wifiDisplayInfo generateWifiDisplayInfo();
const char* _wifimgr_assocstatusName(int assocstatus);