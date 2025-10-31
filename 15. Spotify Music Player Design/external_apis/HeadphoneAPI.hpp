#pragma once
#include <iostream>

using namespace std;

class HeadphoneAPI {
public:
    void playSoundViaHeadphone(const string& data) {
        cout << "[Headphone] Playing: " << data << endl;
    }
};
