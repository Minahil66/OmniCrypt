#ifndef CIPHERS_H
#define CIPHERS_H

#include <vector>
#include <string>

using namespace std;

class Ciphers{
    private:
        string filename;
    protected:
        vector<char> holder;
        int size;
    public:
        virtual void encrypt()=0;
        virtual void decrypt()=0;
        void saveEncrypted();
        void saveDecrypted();
        Ciphers(string n);
        string getFilename() const;
        int getsize() const;
        virtual ~Ciphers();
};

class AtbashCipher: public Ciphers{
    public:
        AtbashCipher(string n);
        void encrypt() override;
        void decrypt() override;
};

class ByteReversalCipher: public Ciphers{
    public:
        ByteReversalCipher(string n);
        void encrypt() override;
        void decrypt() override;
};

class VigenereCipher : public Ciphers {
    string key;
public:
    VigenereCipher(string n, string k);
    void encrypt() override;
    void decrypt() override;
};

class XORCipher : public Ciphers {
private:
    int key;
public:
    XORCipher(string n, int k);
    void encrypt() override;
    void decrypt() override;
};

#endif
