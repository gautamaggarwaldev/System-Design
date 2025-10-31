#pragma once
#include <iostream>

using namespace std;

class WiredSpeakerAPI {
public:
    void playSoundViaWiredSpeaker(const string& data) {
        cout << "[Wired Speaker] Playing: " << data << endl;
    }
};

