#pragma once
#include "../models/Song.hpp"

using namespace std;

class IAudioOutputDevice {
public:
    virtual void playAudio(Song* song) = 0;
    virtual ~IAudioOutputDevice() {};
};
