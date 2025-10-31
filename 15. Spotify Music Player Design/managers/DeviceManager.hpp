#pragma once
#include "../device/IAudioOutputDevice.hpp"
#include "../enums/DeviceType.hpp"
#include "../factory/DeviceFactory.hpp"
#include <iostream>

using namespace std;

class DeviceManager {
private:
    static DeviceManager* instance;
    IAudioOutputDevice* currentOutputDevice;
    DeviceManager() {
        currentOutputDevice = nullptr;
    }
public:
    static DeviceManager* getInstance() {
        if(instance == nullptr) {
            instance = new DeviceManager();
        }
        return instance;
    }

    void connect(DeviceType devicetype) {
        if(currentOutputDevice) {
            delete currentOutputDevice;
        }
        currentOutputDevice = DeviceFactory::createDevice(devicetype);
        switch(devicetype) {
            case DeviceType::BLUETOOTH:
                cout << "Bluetooth Device Connected.." << endl;
                break;
            case DeviceType::HEADPHONE:
                cout << "Headphone Connected.." << endl;
                break;
            case DeviceType::WIRED:
                cout << "Wired Device Connected.." << endl;
                break;
        }
    }

    IAudioOutputDevice* getOutputDevice() {
        if(!currentOutputDevice) {
            throw runtime_error("No output device is connected...");
        }
        return currentOutputDevice;
    }

    bool hasOutputDevice() {
        return currentOutputDevice != nullptr;
    }
};

DeviceManager* DeviceManager::instance = nullptr;