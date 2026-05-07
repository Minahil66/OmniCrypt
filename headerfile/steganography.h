#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include <vector>
#include <string>

class Steganography {
    std::string filename;
    int size;
    std::vector<char> imgdata;
    
public:
    Steganography(std::string n);
    void HideMessage();
    void ExtractMessage();
};

#endif
