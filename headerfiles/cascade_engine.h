#ifndef CASCADE_ENGINE_H
#define CASCADE_ENGINE_H

#include "ciphers.h"
#include "steganography.h"
#include "encryption_tracker.h"
#include "logger.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class CascadeEngine {
private:
    vector<Ciphers*> cipherChain;
    vector<string> cipherNames;
    vector<string> keys;
    string inputFile;
    Logger logger;
    
    Steganography* stego;
    EncryptionTracker* tracker;

public:
    CascadeEngine(string filename);
    void addCipher(string type, string key = "none");
    void attachSteganography(string imagePath);
    void attachTracker();
    void encrypt();
    void decrypt();
    void saveMetadata();
    void printChain();
    void printLog();
    void saveLog();
    ~CascadeEngine();
};

#endif