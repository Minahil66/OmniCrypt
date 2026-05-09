<p align="center">
  <img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=28&pause=1000&color=3A506B&center=true&vCenter=true&width=600&lines=OmniCrypt;Multi-Layer+Encryption;Defense+in+Depth" alt="Typing SVG" />
</p>
# OmniCrypt

Freshman year Computer science students walk into a terminal with one goal — build something that doesn't embarrass them in front of their professor.

This is that project.

Most encryption tools assume one lock is enough. One lock can be picked. So we built three. Because if you're going to fail, fail spectacularly. 
(Spoiler: it actually works.)

OmniCrypt applies multiple ciphers in sequence, hides the result inside a normal BMP image, and tracks tampering. Break one cipher? Two more remain. Find the file? It looks like a family photo.

## Features

- Cipher cascade — Run Vigenere, XOR, ByteReversal, or Atbash in any order
- Steganography — Hide encrypted data inside a BMP image at offset 0x36
- Tamper detection — Hash-based integrity check before decryption
- Logger — Every action recorded to log.txt with timestamp

## How to Install & Run

### 1. Clone the repository

git clone https://github.com/Minahil66/OmniCrypt.git

cd OmniCrypt

### 2. Install a C++ compiler (If you don't have one already)

**Windows (MinGW):**
- Download from [mingw-w64.org](https://www.mingw-w64.org)
- Install, add `C:\mingw64\bin` to System PATH
- Open Command Prompt or PowerShell

**Windows (WSL):**
- Open WSL terminal (Ubuntu)
- `sudo apt update && sudo apt install g++ -y`

**Linux:**
- `sudo apt install g++ -y`

### 3. Compile using:

**Windows:**
- `g++ -std=c++11 main.cpp cascade_engine.cpp ciphers.cpp encryption_tracker.cpp logger.cpp steganography.cpp -o omnicrypt`

 **WSL / Linux:** 

-Run script setup.sh:
- `chmod +x setup.sh`
-  `sed -i 's/\r$//' setup.sh`
-  `./setup.sh`
 
### 4. Run

- Linux / WSL: `./omnicrypt`
- Windows (MinGW): `omnicrypt.exe`

## Need help opening a terminal?

- **Windows:** Press `Win + R`, type `cmd`, press Enter
- **WSL:** Search "Ubuntu" in Start menu
- **Linux:** Press `Ctrl + Alt + T`

## Authors (M.U.R.M)

- Mariya Vayani
- Ujala Usman
- Rubaisha Arif
- Minahil Khan


