#include "encryption_tracker.h"
#include "COE.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <stdexcept>

using namespace std;

string EncryptionTracker::computeHash(const string& path) {
    ifstream file(path, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file for hashing.");
    }
    
    unsigned long long h = 5381;
    char c;
    while (file.get(c)) {
        h = (h * 33) + (unsigned char)c;
    }
    file.close();

    stringstream ss;
    ss << hex << setw(16) << setfill('0') << h;
    return ss.str();
}

size_t EncryptionTracker::computeFileSize(const string& path) {
    ifstream file(path, ios::binary | ios::ate);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file for size calculation.");
    }
    size_t size = file.tellg();
    file.close();
    return size;
}

string EncryptionTracker::getCurrentTimestamp() {
    time_t now = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

EncryptionTracker::EncryptionTracker(string fname, vector<string> cNames, vector<string> cKeys)
    : filename(fname), cipherNames(cNames), keys(cKeys), tamperedFlag(false) {
    
    if (keys.size() != cipherNames.size()) {
        throw runtime_error("Mismatch in cipher names and keys.");
    }
    fileSize = computeFileSize(fname);
    hash = computeHash(fname);
    
    coolInfo("[EncryptionTracker] Initialized with encryption chain.");
    cout << "  File     : " << filename << endl;
    cout << "  Size     : " << fileSize << " bytes" << endl;
    cout << "  Hash     : " << hash << endl;
    cout << "  Chain    : ";
    for (size_t i = 0; i < cipherNames.size(); i++) {
        cout << cipherNames[i];
        if (i < cipherNames.size() - 1) cout << " → ";
    }
    cout << endl;
}

EncryptionTracker::EncryptionTracker(string fname) : filename(fname), tamperedFlag(false) {
    fileSize = computeFileSize(fname);
    hash = computeHash(fname);
    
    coolInfo("[EncryptionTracker] Initialized (simple mode).");
    cout << "  File : " << filename << endl;
    cout << "  Size : " << fileSize << " bytes" << endl;
    cout << "  Hash : " << hash << endl;
}

void EncryptionTracker::saveMetadata() {
    string metaFile = filename + ".meta";
    ofstream out(metaFile);

    if (!out.is_open()) {
        coolError("[EncryptionTracker] Could not save metadata.");
        return;
    }

    out << "===== Cipher Cascade Encryption Data =====" << endl;
    out << "Generated    : " << getCurrentTimestamp() << endl;
    out << "Filename     : " << filename << endl;
    out << "File Size    : " << fileSize << " bytes" << endl;
    out << "Hash (djb2)  : " << hash << endl;
    
    if (!cipherNames.empty()) {
        out << "Cipher Chain : ";
        for (size_t i = 0; i < cipherNames.size(); i++) {
            out << cipherNames[i];
            if (i < cipherNames.size() - 1) out << " → ";
        }
        out << endl;
        
        out << "Keys         : ";
        for (size_t i = 0; i < keys.size(); i++) {
            out << keys[i];
            if (i < keys.size() - 1) out << ", ";
        }
        out << endl;
    }
    
    out << "Status       : " << (tamperedFlag ? "TAMPERED" : "CLEAN") << endl;
    out.close();

    coolSuccess("[EncryptionTracker] Metadata saved to: " + metaFile);
}

bool EncryptionTracker::isTampered() {
    string currentHash = computeHash(filename);
    
    cout << "\n[EncryptionTracker] Integrity Check" << endl;
    cout << "  Stored hash  : " << hash << endl;
    cout << "  Current hash : " << currentHash << endl;

    if (currentHash == hash) {
        cout << GREEN << "  Result       : ✓ INTEGRITY OK" << RESET << endl;
        return false;
    } else {
        tamperedFlag = true;
        cout << RED << "  Result       : ✗ WARNING — File TAMPERED!" << RESET << endl;
        
        string metaFile = filename + ".meta";
        ofstream out(metaFile, ios::app);
        if (out.is_open()) {
            out << "Tamper Detected : " << getCurrentTimestamp() << endl;
            out.close();
        }
        return true;
    }
}

void EncryptionTracker::verifyOrThrow() {
    if (isTampered()) {
        throw runtime_error("File integrity check failed! Possible tampering.");
    }
}

string EncryptionTracker::getFilename() const { return filename; }
size_t EncryptionTracker::getFileSize() const { return fileSize; }
string EncryptionTracker::getHash() const { return hash; }
bool EncryptionTracker::hasTampered() const { return tamperedFlag; }
vector<string> EncryptionTracker::getCipherNames() const { return cipherNames; }
vector<string> EncryptionTracker::getKeys() const { return keys; }

string EncryptionTracker::getEncryptionChain() const {
    if (cipherNames.empty()) return "No encryption";
    if (cipherNames.size() != keys.size()) {
        return "ERROR: Invalid cipher-key mapping";
    }
    
    stringstream ss;
    for (size_t i = 0; i < cipherNames.size(); i++) {
        ss << cipherNames[i] << "(\"" << keys[i] << "\")";
        if (i < cipherNames.size() - 1) ss << " → ";
    }
    return ss.str();
}
