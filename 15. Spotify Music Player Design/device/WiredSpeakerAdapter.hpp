
#pragma once
#include "../models/Song.hpp"
#include "../external_apis/WiredSpeakerAPI.hpp"
#include "IAudioOutputDevice.hpp"

using namespace std;

class WiredSpeakerAdapter : public IAudioOutputDevice {
private:
    WiredSpeakerAPI* wiredapi;
public:
    WiredSpeakerAdapter(WiredSpeakerAPI* api) {
        this->wiredapi = api;
    }

    void playAudio(Song* song) override {
        string payload = song->getTitle() + " by " + song->getArtist();
        wiredapi->playSoundViaWiredSpeaker(payload);
    }
};