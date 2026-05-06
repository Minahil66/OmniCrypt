#ifndef CIPHERS_H
#define CIPHERS_H

#include <vector>
#include <string>

class Ciphers {
protected:
    std::vector<char> holder;
    int size;
    std::string filename;
public:
    Ciphers(std::string n);
    virtual void encrypt() = 0;
    virtual void decrypt() = 0;
    void saveEncrypted();
    void saveDecrypted();
    virtual ~Ciphers() {}
    
    std::vector<char>& getData() { return holder; }
    void setData(std::vector<char>& newData) { holder = newData; }
};

class AtbashCipher : public Ciphers {
public:
    AtbashCipher(std::string n);
    void encrypt() override;
    void decrypt() override;
};

class ByteReversalCipher : public Ciphers {
public:
    ByteReversalCipher(std::string n);
    void encrypt() override;
    void decrypt() override;
};

class XORCipher : public Ciphers {
    int key;
public:
    XORCipher(std::string n, int k);
    void encrypt() override;
    void decrypt() override;
};

#endif
