#pragma once
#include "../models/Playlist.hpp"
#include "../models/Song.hpp"
#include <iostream>

using namespace std;

class PlayStrategy {
public:
    virtual ~PlayStrategy() {}
    virtual void setPlaylist(Playlist* playlist) = 0;
    virtual Song* next() = 0;
    virtual bool hasNext() = 0;
    virtual Song* previous() = 0;
    virtual bool hasPrevious() = 0;
    virtual void addToNext(Song* song) {};
};