#ifndef ENCRYPTION_TRACKER_H
#define ENCRYPTION_TRACKER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <stdexcept>

using namespace std;

class EncryptionTracker {
private:
    string filename;
    size_t fileSize;
    vector<string> cipherNames;
    vector<string> keys;
    string hash;
    bool tamperedFlag;

    string computeHash(const string& path);
    size_t computeFileSize(const string& path);
    string getCurrentTimestamp();

public:
    // Constructor with encryption chain (for encryption mode)
    EncryptionTracker(string fname, vector<string> cNames, vector<string> cKeys);
    
    // Constructor without chain (for decryption mode)
    EncryptionTracker(string fname);
    
    // Save metadata to .meta file
    void saveMetadata();
    
    // Check if file has been tampered
    bool isTampered();
    
    // Throw exception if tampered
    void verifyOrThrow();
    
    // Getters
    string getFilename() const;
    size_t getFileSize() const;
    string getHash() const;
    bool hasTampered() const;
    vector<string> getCipherNames() const;
    vector<string> getKeys() const;
    
    // Get encryption chain as readable string
    string getEncryptionChain() const;
};

#endif
