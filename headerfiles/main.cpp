#include "COE.h"
#include "ciphers.h"
#include "steganography.h"
#include "encryption_tracker.h"
#include "cascade_engine.h"
#include "logger.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(){
    coolBanner();
    
    int choice;
    string file, key;
    int s;

    do{
        cout << CYAN << "\n╔══════════════════════════════════════╗" << endl;
        cout << "║              MAIN MENU               ║" << endl;
        cout << "╠══════════════════════════════════════╣" << endl;
        cout << "║  1. Encrypt (Manual Cascade)         ║" << endl;
        cout << "║  2. Decrypt (Manual Cascade)         ║" << endl;
        cout << "║  3. Steganograph a BMP image         ║" << endl;
        cout << "║  4. Encryption Tracker               ║" << endl;
        cout << "║  5. Logger (check history)           ║" << endl;
        cout << "║  6. Encrypt with CascadeEngine       ║" << endl;
        cout << "║  7. Exit                             ║" << endl;
        cout << "╚══════════════════════════════════════╝" << RESET << endl;
        cout << CYAN << "SELECT: " << RESET;
        cin >> s;

        if(s != 7 && s != 5 && s != 6){
            cout << CYAN << "Enter the path/file: " << RESET;
            cin >> file;
        }

        // ========== OPTION 1 & 2: MANUAL CASCADE ==========
        if(s == 1 || s == 2){

            vector<string> manualCipherNames;
            vector<string> manualKeys;

            // outer try — catches file not found
            try {
            	ifstream testFile(file, ios::binary);
    			if(!testFile.is_open()){
        		throw runtime_error("File not found: " + file);
    			}
    			testFile.close();

                int n = 1;
                while(n <= 3){
                    cout << CYAN << "\n┌─[" << YELLOW << "Step " << n << "/3"
                         << CYAN << "] Select cipher:" << RESET << endl;
                    cout << "   1. Vigenere Cipher" << endl;
                    cout << "   2. XOR Cipher" << endl;
                    cout << "   3. Byte Reversal Cipher" << endl;
                    cout << "   4. Atbash Cipher" << endl;
                    cout << CYAN << "   Choice: " << RESET;
                    cin >> choice;

                    switch(choice){
                        case 1:{
                            cout << CYAN << "Enter string key: " << RESET;
                            cin >> key;
                            manualCipherNames.push_back("Vigenere");
                            manualKeys.push_back(key);
                            {
                                VigenereCipher v1(file, key);
                                if(s == 1){
                                    coolInfo("Encrypting through Vigenere Cipher...");
                                    v1.encrypt();
                                    v1.saveEncrypted();
                                    file = "Encrypted";
                                } else {
                                    coolInfo("Decrypting through Vigenere Cipher...");
                                    v1.decrypt();
                                    v1.saveDecrypted();
                                    file = "Decrypted";
                                }
                            }
                            break;
                        }
                        case 2:{
                            int k;
                            cout << CYAN << "Enter integer key: " << RESET;
                            cin >> k;
                            manualCipherNames.push_back("XOR");
                            manualKeys.push_back(to_string(k));
                            {
                                XORCipher x1(file, k);
                                if(s == 1){
                                    coolInfo("Encrypting through XOR Cipher...");
                                    x1.encrypt();
                                    x1.saveEncrypted();
                                    file = "Encrypted";
                                } else {
                                    coolInfo("Decrypting through XOR Cipher...");
                                    x1.decrypt();
                                    x1.saveDecrypted();
                                    file = "Decrypted";
                                }
                            }
                            break;
                        }
                        case 3:{
                            manualCipherNames.push_back("ByteReversal");
                            manualKeys.push_back("none");
                            {
                                ByteReversalCipher b1(file);
                                if(s == 1){
                                    coolInfo("Encrypting through Byte Reversal Cipher...");
                                    b1.encrypt();
                                    b1.saveEncrypted();
                                    file = "Encrypted";
                                } else {
                                    coolInfo("Decrypting through Byte Reversal Cipher...");
                                    b1.decrypt();
                                    b1.saveDecrypted();
                                    file = "Decrypted";
                                }
                            }
                            break;
                        }
                        case 4:{
                            manualCipherNames.push_back("Atbash");
                            manualKeys.push_back("none");
                            {
                                AtbashCipher a1(file);
                                if(s == 1){
                                    coolInfo("Encrypting through Atbash Cipher...");
                                    a1.encrypt();
                                    a1.saveEncrypted();
                                    file = "Encrypted";
                                } else {
                                    coolInfo("Decrypting through Atbash Cipher...");
                                    a1.decrypt();
                                    a1.saveDecrypted();
                                    file = "Decrypted";
                                }
                            }
                            break;
                        }
                        default:{
                            coolError("Incorrect selection");
                            n--;
                            break;
                        }
                    }
                    n++;
                }

                // inner try — catches EncryptionTracker errors
                if(s == 1){
                    try {
                        EncryptionTracker tracker("Encrypted", manualCipherNames, manualKeys);
                        tracker.saveMetadata();
                        coolSuccess("Metadata saved for manual cascade.");
                    } catch(runtime_error& e){
                        coolError(string("Tracker error: ") + e.what());
                    }
                }

                coolSuccess("Cascade complete!");

            } catch(runtime_error& e){
                // outer catch — file not found stops entire cascade
                coolError(string("Operation failed: ") + e.what());
                coolError("Please enter a valid file path.");
            }

        }
        // ========== OPTION 3: STEGANOGRAPHY ==========
        else if(s == 3){
            try {
                Steganography stego(file);
                int c;
                cout << CYAN << "\n1. Hide message" << endl;
                cout << "2. Extract message" << endl;
                cout << "Choose: " << RESET;
                cin >> c;
                if(c == 1){
                    cin.ignore(1000, '\n');
                    stego.HideMessage();
                } else if(c == 2){
                    stego.ExtractMessage();
                } else {
                    coolError("Invalid choice. Select 1 or 2.");
                }
            } catch(runtime_error& e){
                coolError(string("Steganography error: ") + e.what());
            }
        }
        // ========== OPTION 4: ENCRYPTION TRACKER ==========
        else if(s == 4){
            coolHeader("ENCRYPTION TRACKER");
            try {
                EncryptionTracker tracker(file,true);
                tracker.isTampered();
                //tracker.saveMetadata();
            } catch(runtime_error& e){
                coolError(string("Tracker error: ") + e.what());
            }
        }
        // ========== OPTION 5: LOGGER ==========
        else if(s == 5){
            coolHeader("LOGGER HISTORY");
            ifstream logFile("log.txt");
            if(logFile.is_open()){
                string line;
                cout << CYAN << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET << endl;
                while(getline(logFile, line)){
                    cout << line << endl;
                }
                cout << CYAN << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET << endl;
                logFile.close();
            } else {
                coolInfo("No log file found. Run encryption/decryption first.");
            }
        }
        // ========== OPTION 6: CASCADE ENGINE ==========
        else if(s == 6){
            coolHeader("CASCADE ENGINE");

            string fname;
            cout << CYAN << "Enter file path of the message file: " << RESET;
            cin >> fname;

            try {
                CascadeEngine engine(fname);

                int numCiphers;
                cout << CYAN << "How many ciphers in cascade? " << RESET;
                cin >> numCiphers;

                if(numCiphers < 1){
                    coolError("Must have at least 1 cipher.");
                } else {

                    for(int i = 0; i < numCiphers; i++){
                        int cipherType;
                        string cipherKey;

                        cout << CYAN << "\nCipher " << i+1 << ":" << RESET << endl;
                        cout << "   1. Vigenere" << endl;
                        cout << "   2. XOR" << endl;
                        cout << "   3. ByteReversal" << endl;
                        cout << "   4. Atbash" << endl;
                        cout << CYAN << "   Choice: " << RESET;
                        cin >> cipherType;

                        if(cipherType == 1){
                            cout << CYAN << "   Enter Vigenere key: " << RESET;
                            cin >> cipherKey;
                            engine.addCipher("vigenere", cipherKey);
                        }
                        else if(cipherType == 2){
                            cout << CYAN << "   Enter XOR key (integer): " << RESET;
                            cin >> cipherKey;
                            // validate XOR key is integer
                            try {
                                stoi(cipherKey);
                                engine.addCipher("xor", cipherKey);
                            } catch(invalid_argument& e){
                                coolError("XOR key must be an integer. Skipping cipher.");
                                i--; // retry da step
                            }
                        }
                        else if(cipherType == 3){
                            engine.addCipher("bytereversal");
                        }
                        else if(cipherType == 4){
                            engine.addCipher("atbash");
                        } else {
                            coolError("Invalid cipher type.");
                            i--; // retry the step
                        }
                    }

                    string imgPath;
                    cout << CYAN << "Enter BMP image for steganography (or 'none' to skip): " << RESET;
                    cin >> imgPath;
                    if(imgPath != "none"){
                        engine.attachSteganography(imgPath);
                    }

                    engine.attachTracker();
                    engine.printChain();

                    int encryptOrDecrypt;
                    cout << CYAN << "\n1. Encrypt" << endl;
                    cout << "2. Decrypt" << endl;
                    cout << "Choice: " << RESET;
                    cin >> encryptOrDecrypt;

                    if(encryptOrDecrypt == 1){
                        engine.encrypt();
                    } else if(encryptOrDecrypt == 2){
                        engine.decrypt();
                    } else {
                        coolError("Invalid choice. Select 1 or 2.");
                    }

                    engine.saveLog();
                    coolSuccess("CascadeEngine operation complete!");
                }

            } catch(runtime_error& e){
                coolError(string("CascadeEngine error: ") + e.what());
            }
        }
        // ========== OPTION 7: EXIT ==========
        else if(s == 7){
            coolSuccess("OmniCrypt logging out...");
        }
        else {
            coolError("Invalid option. Select 1-7.");
        }

    } while(s != 7);

    return 0;
}
