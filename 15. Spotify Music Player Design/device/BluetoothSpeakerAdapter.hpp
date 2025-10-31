#pragma once
#include "../models/Song.hpp"
#include "../external_apis/BluetoothSpeakerAPI.hpp"
#include "IAudioOutputDevice.hpp"

using namespace std;

class BluetoothSpeakerAdapter : public IAudioOutputDevice {
private:
    BluetoothSpeakerAPI* bluetoothapi;
public:
    BluetoothSpeakerAdapter(BluetoothSpeakerAPI* api) {
        this->bluetoothapi = api;
    }

    void playAudio(Song* song) override {
        string payload = song->getTitle() + " by " + song->getArtist();
        bluetoothapi->playSoundViaBluetooth(payload);
    }
};