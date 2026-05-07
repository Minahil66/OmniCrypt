#ifndef COE_H
#define COE_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\034[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

#define CLEAR_SCREEN "\033[2J\033[H"

inline void coolBanner() {
    std::cout << CLEAR_SCREEN;
    std::cout << CYAN << BOLD << R"(
╔══════════════════════════════════════════════════════════════╗
║                                                              ║
║      ██████╗ ███╗   ███╗███╗   ██╗██╗                        ║
║     ██╔═══██╗████╗ ████║████╗  ██║██║                        ║
║     ██║   ██║██╔████╔██║██╔██╗ ██║██║                        ║
║     ██║   ██║██║╚██╔╝██║██║╚██╗██║██║                        ║
║     ╚██████╔╝██║ ╚═╝ ██║██║ ╚████║██║                        ║
║      ╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═══╝╚═╝                        ║
║                                                              ║
║      ██████╗██████╗ ██╗   ██╗██████╗ ████████╗               ║
║     ██╔════╝██╔══██╗╚██╗ ██╔╝██╔══██╗╚══██╔══╝               ║
║     ██║     ██████╔╝ ╚████╔╝ ██████╔╝   ██║                  ║
║     ██║     ██╔══██╗  ╚██╔╝  ██╔═══╝    ██║                  ║
║     ╚██████╗██║  ██║   ██║   ██║        ██║                  ║
║      ╚═════╝╚═╝  ╚═╝   ╚═╝   ╚═╝        ╚═╝                  ║
║                                                              ║
║              MULTI-LAYER ENCRYPTION SUITE                    ║
║         Cipher Cascade · Steganography · Security            ║
║                   Made by: M U R M                           ║
║                                                              ║
╚══════════════════════════════════════════════════════════════╝
)" << RESET << std::endl;
}

inline void coolHeader(const std::string& title) {
    std::cout << CYAN << "\n┌─────────────────────────────────────────────────┐\n";
    std::cout << "│ " << BOLD << title << RESET << std::string(49 - title.length(), ' ') << CYAN << "│\n";
    std::cout << "└─────────────────────────────────────────────────┘\n" << RESET << std::endl;
}

inline void coolSuccess(const std::string& msg) {
    std::cout << GREEN << " ✓ " << msg << RESET << std::endl;
}

inline void coolError(const std::string& msg) {
    std::cout << RED << " ✗ " << msg << RESET << std::endl;
}

inline void coolInfo(const std::string& msg) {
    std::cout << CYAN << " ℹ " << msg << RESET << std::endl;
}

inline void coolSpinner(const std::string& msg, int durationMs = 500) {
    std::cout << CYAN << " ⏳ " << msg << RESET;
    std::cout.flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(durationMs));
    std::cout << "\r" << GREEN << " ✓ " << msg << RESET << std::endl;
}

#endif
