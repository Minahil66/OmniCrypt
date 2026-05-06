#include "ciphers.h"
#include <fstream>
#include <iostream>
#include <algorithm>

class Ciphers{
    private:
    string filename;
    protected:
    vector<char> holder;
    int size;
    public:
    virtual void encrypt()=0;
    virtual void decrypt()=0;
    void saveEncrypted(){
        string name;
        cout<<"Save file as:(Enter name) "<<endl;
        cin>>name;
         ofstream outfile(name, ios::binary);
        outfile.write(holder.data(), holder.size());
        outfile.close();
        cout<<"File saved as: "<<name<<endl<<endl;
        }
    void saveDecrypted(){
        string name;
        cout<<"Save file as:(Enter name) "<<endl;
        cin>>name;
        ofstream outfile("DecryptedVer", ios::binary);
        outfile.write(holder.data(), holder.size());
        outfile.close();
        cout<<"File saved as: "<<name<<endl<<endl;
    }
    Ciphers(string n):filename(n){ //enter name/path
        ifstream file(n, ios::binary);
        if(!file.is_open()){
        cout<<"Error: File failed to open"<<n<<endl;
        return;
        }
        file.seekg(0, ios::end); //put the cursor in the end of the file and DO NOT MOV any positions
        size=file.tellg(); //snce file is already in binary, tell us the size
        file.seekg(0,ios::beg); //okay size done, now put the cursor back to the beginning
        holder.resize(size); //changing the size of our vector
        if(file.fail()){
        cout << "Error: Failed to read file " << n << endl;
        return;
        }
        file.read(holder.data(), size); //data() is a raw pointer to the place/mem where vector is storing elements, so file.read(where to put data (expects a pointer), how many bytes to read(int));
        file.close(); //close the file
        cout<<"Successfully read "<<size<<" bytes into memory"<<endl;
    }
    string getFilename()const{ return filename;}
    int getsize()const{return size;}
    virtual ~Ciphers(){}
};
class AtbashCipher:public Ciphers{
    public:
    AtbashCipher(string n):Ciphers(n){}
    void encrypt()override{
    for(int i=0;i<holder.size();i++){
    holder[i]=255-(unsigned char)holder[i];
    }
    }
    void decrypt()override{
    for(int i=0;i<holder.size();i++){
    holder[i]=255-(unsigned char)holder[i];
    }
    }
};
class ByteReversalCipher:public Ciphers{
public:
    ByteReversalCipher(string n) : Ciphers(n) {}
    
    void encrypt() override {
    reverse(holder.begin(), holder.end());
    }
    void decrypt() override{    
    reverse(holder.begin(), holder.end());  // Reverse back
    }
};
class VigenereCipher : public Ciphers {
    string key;
public:
    VigenereCipher(string n, string k):Ciphers(n) {
    key = k; }
    void encrypt() override {
        int keyIndex = 0;
        
    for (int i = 0; i < holder.size(); i++) {
    char c = holder[i];
    if (isalpha(c)) {
    char k = key[keyIndex % key.length()];
    
    int kValue = toupper(k) - 'A';
    if (isupper(c)) {
    int tValue = c - 'A';
    holder[i] = ((tValue + kValue) % 26) + 'A'; //tottal alphabets = 26
    }
    else
    { //lowercase
    int tValue = c - 'a';
    holder[i] = ((tValue + kValue) % 26) + 'a';
    } 
    keyIndex++;  //increment key index
    }
}
}
    void decrypt() override 
    {
        int keyIndex = 0;
    for (int i = 0; i < holder.size(); i++) {
    char c = holder[i];
    
    if (isalpha(c)) {

    char k = key[keyIndex % key.length()]; //to repeat key until length matches as of text
 
    int kValue = toupper(k) - 'A';
    if (isupper(c)) {
        int cValue = c - 'A';
        holder[i] = ((cValue - kValue + 26) % 26) + 'A';
     }
     else { // lowercase
        int cValue = c - 'a';
        holder[i] = ((cValue - kValue + 26) % 26) + 'a';
                }
        keyIndex++;        
    } } } };
    
class XORCipher : public Ciphers {
private:
    int key;
public:
    XORCipher(string n, int k) : Ciphers(n) {
    key = k;
    }
    void encrypt() override {
    for (int i = 0; i < holder.size(); i++) {
    holder[i] = holder[i] ^ key;
    }
    }
    void decrypt() override {
    for (int i = 0; i < holder.size(); i++) {
    holder[i] = holder[i] ^ key;   // XOR reverses itself
    } } };
