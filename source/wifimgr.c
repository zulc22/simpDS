#include "wifimgr.h"

void manageWifi() {

}

struct wifiDisplayInfo generateWifiDisplayInfo() {
    struct wifiDisplayInfo returnMe;
    int assocStatus = Wifi_AssocStatus();
    returnMe.status = wifiassocDisplayName(assocStatus);
    returnMe.isConnecting = (
        assocStatus == ASSOCSTATUS_CANNOTCONNECT ||
        assocStatus == ASSOCSTATUS_DISCONNECTED ||
        assocStatus == ASSOCSTATUS_ASSOCIATED
    );
}

const char* wifiassocDisplayName(int assocstatus) {
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
    }
}