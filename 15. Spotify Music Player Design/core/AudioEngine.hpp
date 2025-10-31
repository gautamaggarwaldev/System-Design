#pragma once
#include "../models/Song.hpp"
#include "../device/IAudioOutputDevice.hpp"
#include "iostream"

using namespace std;

class AudioEngine {
private:
    Song* currSong;
    bool isSongPaused;
public:
    AudioEngine() {
        currSong = nullptr;
        isSongPaused = false;
    }

    string getCurrSongTitle() const {
        if(currSong) {
            return currSong->getTitle();
        }
        return "";
    }

    bool isPaused() const {
        return isSongPaused;
    }

    void play(IAudioOutputDevice* aod, Song* song) {
        if (song == nullptr) {
            throw runtime_error("Cannot play a null song.");
        }
        // Resume if same song was paused
        if (isSongPaused && song == currSong) {
            isSongPaused = false;
            cout << "Resuming song: " << song->getTitle() << "\n";
            aod->playAudio(song);
            return;
        }

        currSong = song;
        isSongPaused = false;
        cout << "Playing song: " << song->getTitle() << "\n";
        aod->playAudio(song);
    }

    void pause() {
        if(currSong == nullptr) {
            throw runtime_error("No song is currently playing to pause...");
        }
        isSongPaused = true;
        cout << "Pausing song: " << currSong->getTitle() << endl;
    }
};