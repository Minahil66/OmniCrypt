#include "steganography.h"
#include "COE.h"
#include <fstream>
#include <iostream>
#include<vector>

using namespace std;

Steganography::Steganography(string n) : filename(n) {
    ifstream infile(filename, ios::binary);
    if(!infile.is_open()){
        coolError("File failed to open");
        return;
    }
    infile.seekg(0, ios::end);
    size = infile.tellg();
    imgdata.resize(size);
    infile.seekg(0, ios::beg);
    if(infile.fail()){
        coolError("Failed to read data into memory");
        return;
    }
    infile.read(imgdata.data(), size);
    infile.close();
    coolInfo("Successfully read file into memory");
}

void Steganography::HideMessage() {
    string msg;
    cout << CYAN << "Enter the message to hide: " << RESET;
    getline(cin, msg);

    vector<char> message(msg.begin(), msg.end());
    message.push_back('\0');

    if(message.size() > imgdata.size() - 0x36){
        coolError("Message too long: Exceeds image size");
        return;
    }
    for(int i = 0; i < message.size(); i++){
        imgdata[0x36 + i] = message[i];
    }
    ofstream outfile("stega_" + filename, ios::binary);
    outfile.write(imgdata.data(), imgdata.size());
    outfile.close();
    coolSuccess("Hidden in stega_" + filename);
}

void Steganography::ExtractMessage() {
    vector<char> msg;
    for(int i = 0x36; i <= imgdata.size(); i++){
        if(imgdata[i] == '\0') break;
        msg.push_back(imgdata[i]);
    }
    string message(msg.begin(), msg.end());
    cout << GREEN << "Hidden message: " << BOLD << message << RESET << endl;
}
void Steganography::hideData(vector<char>& encryptedData) {
    cout << "[Stego] Hiding " << encryptedData.size() << " bytes of encrypted data in image..." << endl;
    
    for (int i = 0; i < encryptedData.size() && (0x36 + i) < imgdata.size(); i++) {
        imgdata[0x36 + i] = encryptedData[i];
    }
    
    ofstream outfile("stego_" + filename, ios::binary);
    outfile.write(imgdata.data(), imgdata.size());
    outfile.close();
    
    cout << "[Stego] Encrypted data hidden in stego_" << filename << endl;
}
