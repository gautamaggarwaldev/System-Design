#pragma once
#include <iostream>

using namespace std;

class Song {
private:
    string title;
    string artist;
    string filePath;
public:
    Song(string t, string a, string fp) {
        this->title = t;
        this->artist = a;
        this->filePath = fp;
    }

    string getTitle() {
        return title;
    }

    string getArtist() {
        return artist;
    }

    string getFilePath() {
        return filePath;
    }
};