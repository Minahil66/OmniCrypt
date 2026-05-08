#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

using namespace std;

class Log {
public:
    string cipherName;
    int stepNumber;
    string operation;
    string fileName;
    string message;
    string level;
    string timestampStr;

    void setter(string msg, string lev, string cipher, int step, string opr, string file);
};

class Logger {
private:
    vector<Log> logs;

public:
    void log(string msg, string level, string cipherName, int stepNumber, string operation, string fileName);
    void info(string msg, string cipherName, int stepNumber, string operation, string fileName);
    void error(string msg, string cipherName, int stepNumber, string operation, string fileName);
    void debug(string msg, string cipherName, int stepNumber, string operation, string fileName);
    void warn(string msg, string cipherName, int stepNumber, string operation, string fileName);
    void print()const;
    void saveToFile()const;
    void clearLogs();
};

#endif
