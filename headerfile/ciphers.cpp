#include "ciphers.h"
#include "COE.h"
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

// ========== CIPHERS BASE CLASS ==========

Ciphers::Ciphers(string n) : filename(n) {
    ifstream file(n, ios::binary);
    if(!file.is_open()){
        coolError("File failed to open " + n);
        return;
    }
    file.seekg(0, ios::end);
    size = file.tellg();
    file.seekg(0, ios::beg);
    holder.resize(size);
    if(file.fail()){
        coolError("Failed to read file " + n);
        return;
    }
    file.read(holder.data(), size);
    file.close();
    coolInfo("Successfully read " + to_string(size) + " bytes into memory");
}

void Ciphers::saveEncrypted(){
    string name;
    cout << CYAN << "Save file as: " << RESET;
    cin >> name;
    ofstream outfile(name, ios::binary);
    outfile.write(holder.data(), holder.size());
    outfile.close();
    coolSuccess("File saved as: " + name);
}

void Ciphers::saveDecrypted(){
    string name;
    cout << CYAN << "Save file as: " << RESET;
    cin >> name;
    ofstream outfile("DecryptedVer", ios::binary);
    outfile.write(holder.data(), holder.size());
    outfile.close();
    coolSuccess("File saved as: " + name);
}

// ========== ATBASH CIPHER ==========

AtbashCipher::AtbashCipher(string n) : Ciphers(n) {}

void AtbashCipher::encrypt() {
    for(int i = 0; i < holder.size(); i++){
        holder[i] = 255 - (unsigned char)holder[i];
    }
}

void AtbashCipher::decrypt() {
    for(int i = 0; i < holder.size(); i++){
        holder[i] = 255 - (unsigned char)holder[i];
    }
}

// ========== BYTE REVERSAL CIPHER ==========

ByteReversalCipher::ByteReversalCipher(string n) : Ciphers(n) {}

void ByteReversalCipher::encrypt() {
    reverse(holder.begin(), holder.end());
}

void ByteReversalCipher::decrypt() {
    reverse(holder.begin(), holder.end());
}

// ========== VIGENERE CIPHER ==========

VigenereCipher::VigenereCipher(string n, string k) : Ciphers(n), key(k) {}

void VigenereCipher::encrypt() {
    int keyIndex = 0;
    for (int i = 0; i < holder.size(); i++) {
        char c = holder[i];
        if (isalpha(c)) {
            char k = key[keyIndex % key.length()];
            int kValue = toupper(k) - 'A';
            if (isupper(c)) {
                int tValue = c - 'A';
                holder[i] = ((tValue + kValue) % 26) + 'A';
            } else {
                int tValue = c - 'a';
                holder[i] = ((tValue + kValue) % 26) + 'a';
            }
            keyIndex++;
        }
    }
}

void VigenereCipher::decrypt() {
    int keyIndex = 0;
    for (int i = 0; i < holder.size(); i++) {
        char c = holder[i];
        if (isalpha(c)) {
            char k = key[keyIndex % key.length()];
            int kValue = toupper(k) - 'A';
            if (isupper(c)) {
                int cValue = c - 'A';
                holder[i] = ((cValue - kValue + 26) % 26) + 'A';
            } else {
                int cValue = c - 'a';
                holder[i] = ((cValue - kValue + 26) % 26) + 'a';
            }
            keyIndex++;
        }
    }
}

// ========== XOR CIPHER ==========

XORCipher::XORCipher(string n, int k) : Ciphers(n), key(k) {}

void XORCipher::encrypt() {
    for (int i = 0; i < holder.size(); i++) {
        holder[i] = holder[i] ^ key;
    }
}

void XORCipher::decrypt() {
    for (int i = 0; i < holder.size(); i++) {
        holder[i] = holder[i] ^ key;
    }
}
