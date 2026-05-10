#include "cascade_engine.h"
#include <iostream>

using namespace std;

CascadeEngine::CascadeEngine(string filename) : inputFile(filename), stego(nullptr), tracker(nullptr) {
    logger.info("CascadeEngine initialized", "Engine", 0, "INIT", filename);
    cout << "[Engine] CascadeEngine ready. Stego and Tracker not created yet." << endl;
}

void CascadeEngine::addCipher(string type, string key) {
    Ciphers* c = nullptr;
    
    if (type == "atbash") {
        c = new AtbashCipher(inputFile);
        cipherNames.push_back("Atbash");
        keys.push_back("none");
    }
    else if (type == "bytereversal") {
        c = new ByteReversalCipher(inputFile);
        cipherNames.push_back("ByteReversal");
        keys.push_back("none");
    }
    else if (type == "vigenere") {
        c = new VigenereCipher(inputFile, key);
        cipherNames.push_back("Vigenere");
        keys.push_back(key);
    }
    else if (type == "xor") {
        int k = stoi(key);
        c = new XORCipher(inputFile, k);
        cipherNames.push_back("XOR");
        keys.push_back(key);
    }
    else {
        cout << "Unknown cipher type: " << type << endl;
        return;
    }
    
    cipherChain.push_back(c);
    logger.info("Cipher added to chain", cipherNames.back(), cipherChain.size(), "ADD", inputFile);
}

void CascadeEngine::attachSteganography(string imagePath) {
    stego = new Steganography(imagePath);
    cout << "[Engine] Steganography created and owned by engine." << endl;
    logger.info("Steganography attached", "Stego", 0, "ATTACH", imagePath);
}

void CascadeEngine::attachTracker() {
    tracker = new EncryptionTracker(inputFile, cipherNames, keys);
    cout << "[Engine] EncryptionTracker created and owned by engine." << endl;
    logger.info("EncryptionTracker attached", "Tracker", 0, "ATTACH", inputFile);
}

void CascadeEngine::encrypt() {
    if (cipherChain.empty()) {
        cout << "No ciphers in chain!" << endl;
        return;
    }
    
    cout << "\n════════════════════════════════════════" << endl;
    cout << "  STARTING ENCRYPTION CASCADE" << endl;
    cout << "════════════════════════════════════════" << endl;
    
    // First cipher encrypts its own data
    cipherChain[0]->encrypt();
    
    // Pass data through remaining ciphers using getter/setter
    for (size_t i = 1; i < cipherChain.size(); i++) {
        cout << "[Step " << i+1 << "] Applying " << cipherNames[i] << "..." << endl;
        cipherChain[i]->setData(cipherChain[i-1]->getData());
        cipherChain[i]->encrypt();
        logger.info("Encryption step complete", cipherNames[i], i+1, "ENCRYPT", inputFile);
    }
    
    // Save final encrypted file
    cipherChain.back()->saveEncrypted();
    
    if (stego) {
        cout << "[Stego] Hiding encrypted data in image..." << endl;
        stego->hideData(cipherChain.back()->getData());
        logger.info("Steganography hiding step", "Stego", 0, "HIDE", "");
    }
    
    if (tracker) {
        tracker->saveMetadata();
        logger.info("Metadata saved", "Tracker", 0, "SAVE", inputFile);
    } else {
        cout << "[Tracker] No tracker attached. Skipping metadata save." << endl;
    }
    
    cout << "════════════════════════════════════════" << endl;
    cout << "  ENCRYPTION COMPLETE" << endl;
    cout << "════════════════════════════════════════" << endl;
    
    logger.info("Encryption cascade completed", "Engine", 0, "END", inputFile);
}

void CascadeEngine::decrypt() {
    if (cipherChain.empty()) {
        cout << "No ciphers in chain!" << endl;
        return;
    }
    
    cout << "\n════════════════════════════════════════" << endl;
    cout << "  STARTING DECRYPTION CASCADE" << endl;
    cout << "════════════════════════════════════════" << endl;
    
    if (tracker) {
        cout << "[Tracker] Checking file integrity..." << endl;
        try {
            tracker->verifyOrThrow();
            cout << "[OK] Integrity check passed." << endl;
        } catch (runtime_error& e) {
            cout << "[ERROR] " << e.what() << endl;
            cout << "Aborting decryption." << endl;
            logger.warn("Tamper detected during decryption", "Engine", 0, "DECRYPT", inputFile);
            return;
        }
    } else {
        cout << "[Tracker] No tracker attached. Skipping integrity check." << endl;
    }
    
    // Load the encrypted file into the LAST cipher
    ifstream infile("Encrypted", ios::binary);
    if (!infile.is_open()) {
        coolError("Cannot open encrypted file 'Encrypted'");
        return;
    }
    infile.seekg(0, ios::end);
    streampos fileSize = infile.tellg(); //streampos to hold large files
    infile.seekg(0, ios::beg);
    vector<char> encryptedData(static_cast<size_t>(fileSize));
    infile.read(encryptedData.data(), static_cast<streamsize>(fileSize));
    infile.close();
    
    cipherChain.back()->setData(encryptedData);
    
    // Decrypt in reverse order (ONCE per cipher)
        for (int i = cipherChain.size() - 1; i >= 0; i--) {
    cout << "[Step " << cipherChain.size() - i << "] Reversing " << cipherNames[i] << "..." << endl;
    cipherChain[i]->decrypt(); // decrypt FIRST
    
    if (i > 0) {
        cipherChain[i-1]->setData(cipherChain[i]->getData()); // THEN pass result down
    }
        logger.info("Decryption step complete", cipherNames[i], i+1, "DECRYPT", inputFile);
    }
    
    cipherChain[0]->saveDecrypted();
    
    cout << "════════════════════════════════════════" << endl;
    cout << "  DECRYPTION COMPLETE" << endl;
    cout << "════════════════════════════════════════" << endl;
    
    logger.info("Decryption cascade completed", "Engine", 0, "END", inputFile);
}
void CascadeEngine::saveMetadata() {
    if (tracker) {
        tracker->saveMetadata();
        logger.info("Metadata saved", "Engine", 0, "META", inputFile);
    } else {
        EncryptionTracker meta(inputFile, cipherNames, keys);
        meta.saveMetadata();
        logger.info("Metadata saved (temporary tracker)", "Engine", 0, "META", inputFile);
    }
}

void CascadeEngine::printChain() {
    if (cipherChain.empty()) {
        cout << "Chain is empty." << endl;
        return;
    }
    
    cout << "\nCipher Chain: ";
    for (size_t i = 0; i < cipherNames.size(); i++) {
        cout << cipherNames[i];
        if (keys[i] != "none") cout << "(\"" << keys[i] << "\")";
        if (i < cipherNames.size() - 1) cout << " -> ";
    }
    cout << endl;
    
    cout << "Steganography: " << (stego ? "ENABLED (engine owns)" : "DISABLED") << endl;
    cout << "EncryptionTracker: " << (tracker ? "CREATED (engine owns)" : "NOT CREATED") << endl;
}

void CascadeEngine::printLog() {
    logger.print();
}

void CascadeEngine::saveLog() {
    logger.saveToFile();
    cout << "Log saved to log.txt" << endl;
}

CascadeEngine::~CascadeEngine() {
    if (stego) {
        cout << "[Engine] Destroying Steganography (engine owned it)" << endl;
        delete stego;
    }
    if (tracker) {
        cout << "[Engine] Destroying EncryptionTracker (engine owned it)" << endl;
        delete tracker;
    }
    
    for (size_t i = 0; i < cipherChain.size(); i++) {
        delete cipherChain[i];
    }
    cipherChain.clear();
    
    cout << "[Engine] CascadeEngine destroyed." << endl;
}
