#!/bin/bash
echo "🔧 Compiling OmniCrypt..."
g++ -std=c++11 main.cpp ciphers.cpp steganography.cpp encryption_tracker.cpp logger.cpp cascade_engine.cpp -o omnicrypt
echo " Done! Run with: ./omnicrypt"
