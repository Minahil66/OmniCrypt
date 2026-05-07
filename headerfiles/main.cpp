#include "COE.h"
#include "ciphers.h"
#include "steganography.h"
#include "encryption_tracker.h"
#include "cascade_engine.h"
#include <iostream>

using namespace std;

int main(){
    coolBanner();
    
    int choice;
    string file, key;
    int s;
    
    cout << CYAN << "Enter the path/file: " << RESET;
    cin >> file;
    
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
        
        // ========== OPTION 1 & 2: MANUAL CASCADE (Your original code) ==========
        if (s == 1 || s == 2){
            int n = 1;
            while(n <= 3){
                cout << CYAN << "\n┌─[" << YELLOW << "Step " << n << "/3" << CYAN << "] Select cipher:" << RESET << endl;
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
                        {
                            VigenereCipher v1(file, key);
                            if(s == 1){
                                coolInfo("Encrypting through Vigenere Cipher...");
                                v1.encrypt();
                                v1.saveEncrypted();
                                file = "EncryptedVer";
                            } else {
                                coolInfo("Decrypting through Vigenere Cipher...");
                                v1.decrypt();
                                v1.saveDecrypted();
                                file = "DecryptedVer";
                            }
                        }
                        break;
                    }
                    case 2:{
                        int k;
                        cout << CYAN << "Enter integer key: " << RESET;
                        cin >> k;
                        {
                            XORCipher x1(file, k);
                            if(s == 1){
                                coolInfo("Encrypting through XOR Cipher...");
                                x1.encrypt();
                                x1.saveEncrypted();
                                file = "EncryptedVer";
                            } else {
                                coolInfo("Decrypting through XOR Cipher...");
                                x1.decrypt();
                                x1.saveDecrypted();
                                file = "DecryptedVer";
                            }
                        }
                        break;
                    }
                    case 3:{
                        {
                            ByteReversalCipher b1(file);
                            if(s == 1){
                                coolInfo("Encrypting through Byte Reversal Cipher...");
                                b1.encrypt();
                                b1.saveEncrypted();
                                file = "EncryptedVer";
                            } else {
                                coolInfo("Decrypting through Byte Reversal Cipher...");
                                b1.decrypt();
                                b1.saveDecrypted();
                                file = "DecryptedVer";
                            }
                        }
                        break;
                    }
                    case 4:{
                        {
                            AtbashCipher a1(file);
                            if(s == 1){
                                coolInfo("Encrypting through Atbash Cipher...");
                                a1.encrypt();
                                a1.saveEncrypted();
                                file = "EncryptedVer";
                            } else {
                                coolInfo("Decrypting through Atbash Cipher...");
                                a1.decrypt();
                                a1.saveDecrypted();
                                file = "DecryptedVer";
                            }
                        }
                        break;
                    }
                    default: {
                        coolError("Incorrect selection");
                        break;
                    }
                }
                n++;
            }
            coolSuccess("Cascade complete!");
        } 
        // ========== OPTION 3: STEGANOGRAPHY ==========
        else if(s == 3){
            Steganography stego(file);
            int c;
            cout << CYAN << "\n1. Hide message" << endl;
            cout << "2. Extract message" << endl;
            cout << "Choose: " << RESET;
            cin >> c;
            if(c == 1) {
                cin.ignore(1000, '\n');
                stego.HideMessage();
            } else if(c == 2) {
                stego.ExtractMessage();
            }
        }
        // ========== OPTION 4: ENCRYPTION TRACKER ==========
        else if(s == 4){
            coolHeader("ENCRYPTION TRACKER");
            EncryptionTracker tracker(file);
            tracker.isTampered();
            tracker.saveMetadata();
        }
        // ========== OPTION 5: LOGGER ==========
        else if(s == 5){
    coolHeader("LOGGER HISTORY");
    
    ifstream logFile("log.txt");
    if(logFile.is_open()) {
        string line;
        cout << CYAN << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET << endl;
        while(getline(logFile, line)) {
            cout << line << endl;
        }
        cout << CYAN << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET << endl;
        logFile.close();
    } else {
        coolInfo("No log file found. Run encryption/decryption first to generate logs.");
    }
}
        // ========== OPTION 6: CASCADE ENGINE (NEW!) ==========
        else if(s == 6){
            coolHeader("CASCADE ENGINE");
            
            string fname;
            cout << CYAN << "Enter file path: " << RESET;
            cin >> fname;
            
            // Create engine
            CascadeEngine engine(fname);
            
            // Ask for number of ciphers
            int numCiphers;
            cout << CYAN << "How many ciphers in cascade? " << RESET;
            cin >> numCiphers;
            
            // Add ciphers
            for(int i = 0; i < numCiphers; i++) {
                int cipherType;
                string cipherKey;
                
                cout << CYAN << "\nCipher " << i+1 << ":" << RESET << endl;
                cout << "   1. Vigenere" << endl;
                cout << "   2. XOR" << endl;
                cout << "   3. ByteReversal" << endl;
                cout << "   4. Atbash" << endl;
                cout << CYAN << "   Choice: " << RESET;
                cin >> cipherType;
                
                if(cipherType == 1) {
                    cout << CYAN << "   Enter Vigenere key: " << RESET;
                    cin >> cipherKey;
                    engine.addCipher("vigenere", cipherKey);
                }
                else if(cipherType == 2) {
                    cout << CYAN << "   Enter XOR key: " << RESET;
                    cin >> cipherKey;
                    engine.addCipher("xor", cipherKey);
                }
                else if(cipherType == 3) {
                    engine.addCipher("bytereversal");
                }
                else if(cipherType == 4) {
                    engine.addCipher("atbash");
                }
            }
            
            // Ask for steganography
            string imgPath;
            cout << CYAN << "Enter BMP image for steganography (or 'none' to skip): " << RESET;
            cin >> imgPath;
            if(imgPath != "none") {
                engine.attachSteganography(imgPath);
            }
            
            // Attach tracker and run
            engine.attachTracker();
            engine.printChain();
            
            int encryptOrDecrypt;
            cout << CYAN << "\n1. Encrypt" << endl;
            cout << "2. Decrypt" << endl;
            cout << "Choice: " << RESET;
            cin >> encryptOrDecrypt;
            
            if(encryptOrDecrypt == 1) {
                engine.encrypt();
            } else {
                engine.decrypt();
            }
            
            engine.saveLog();
            coolSuccess("CascadeEngine operation complete!");
        }
        else if(s == 7){
            coolSuccess("OmniCrypt logging out...");
        }
        else {
            coolError("Invalid option");
        }
    } while (s != 7);
    
    return 0;
}
