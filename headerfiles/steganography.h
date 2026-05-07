#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include <vector>
#include <string>

using namespace std;

class Steganography {
    string filename;
    int size;
    vector<char> imgdata;
    
public:
    Steganography(string n);
    void HideMessage();
    void ExtractMessage();
    void hideData(vector<char>& encryptedData);
};

#endif