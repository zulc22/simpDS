#include "wifimgr.h"
#include "errors.h"

bool _wifimgr_wifiIsInited = false;
bool _wifimgr_retryIfUnable = false;

void manageWifi() {

    if (!_wifimgr_wifiIsInited) {
        _wifimgr_wifiIsInited = Wifi_InitDefault(false);
        throwErrorIf(
            !_wifimgr_wifiIsInited,
            "Unable to initialize dswifi!"
        );
    }

    int assocStatus = Wifi_AssocStatus();

    if (
        assocStatus == ASSOCSTATUS_DISCONNECTED ||
        (_wifimgr_retryIfUnable && assocStatus == ASSOCSTATUS_CANNOTCONNECT)
    )
        Wifi_AutoConnect();

}

struct wifiDisplayInfo generateWifiDisplayInfo() {
    struct wifiDisplayInfo returnMe;
    int assocStatus = Wifi_AssocStatus();
    returnMe.status = _wifimgr_assocstatusName(assocStatus);
    returnMe.isConnecting = (
        assocStatus == ASSOCSTATUS_CANNOTCONNECT ||
        assocStatus == ASSOCSTATUS_DISCONNECTED ||
        assocStatus == ASSOCSTATUS_ASSOCIATED
    );
    returnMe.isConnected = (assocStatus == ASSOCSTATUS_ASSOCIATED);
    return returnMe;
}

const char* _wifimgr_assocstatusName(int assocstatus) {
    switch (assocstatus) {
        case ASSOCSTATUS_ACQUIRINGDHCP:
            return "Acquiring IP address...";
        case ASSOCSTATUS_ASSOCIATED:
            return "Connected";
        case ASSOCSTATUS_ASSOCIATING:
            return "Associating...";
        case ASSOCSTATUS_AUTHENTICATING:
            return "Authenticating...";
        case ASSOCSTATUS_CANNOTCONNECT:
            return "Could not connect!";
        case ASSOCSTATUS_DISCONNECTED:
            return "Not connected";
        case ASSOCSTATUS_SEARCHING:
            return "Searching for hotspot...";
        default:
            return "Unknown status????";
    }
}