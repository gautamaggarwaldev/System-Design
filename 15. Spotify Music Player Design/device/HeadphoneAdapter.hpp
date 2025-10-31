
#pragma once
#include "../models/Song.hpp"
#include "../external_apis/HeadphoneAPI.hpp"
#include "IAudioOutputDevice.hpp"

using namespace std;

class HeadphoneAdapter : public IAudioOutputDevice {
private:
    HeadphoneAPI* headphoneapi;
public:
    HeadphoneAdapter(HeadphoneAPI* api) {
        this->headphoneapi = api;
    }

    void playAudio(Song* song) override {
        string payload = song->getTitle() + " by " + song->getArtist();
        headphoneapi->playSoundViaHeadphone(payload);
    }
};