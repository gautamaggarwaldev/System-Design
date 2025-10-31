#pragma once
#include <iostream>

using namespace std;

class BluetoothSpeakerAPI {
public:
    void playSoundViaBluetooth(const string& data) {
        cout << "[Bluetooth Speaker] Playing: " << data << endl;
    }
};
