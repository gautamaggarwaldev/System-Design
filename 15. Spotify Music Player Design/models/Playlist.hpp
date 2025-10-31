#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Song.hpp"

using namespace std;

class Playlist {
private:
    string playlistName;
    vector<Song*> songs;
public:
    Playlist(string n) {
        this->playlistName = n;
    }

    string getPlaylistName() {
        return playlistName;
    }

    const vector<Song*> getSongs() {
        return songs;
    }

    int getSize() {
        return songs.size();
    }

    void addSongsToPlaylist(Song* song) {
        if(song==nullptr) {
            throw runtime_error("Cannot add a null song to a playlist...");
        }
        else {
            songs.push_back(song);
        }
    }
};
