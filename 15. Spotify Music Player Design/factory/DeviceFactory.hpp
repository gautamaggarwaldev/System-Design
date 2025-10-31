#pragma once
#include "../device/IAudioOutputDevice.hpp"
#include "../device/BluetoothSpeakerAdapter.hpp"
#include "../device/HeadphoneAdapter.hpp"
#include "../device/WiredSpeakerAdapter.hpp"
#include "../enums/DeviceType.hpp"
#include <iostream>

using namespace std;

class DeviceFactory {
public:
    static IAudioOutputDevice* createDevice(DeviceType devicetype) {
        if(devicetype == DeviceType::BLUETOOTH) {
            return new BluetoothSpeakerAdapter(new BluetoothSpeakerAPI());
        }
        else if(devicetype == DeviceType::HEADPHONE) {
            return new HeadphoneAdapter(new HeadphoneAPI());
        }
        else {
            return new WiredSpeakerAdapter(new WiredSpeakerAPI());
        }
    }
};
