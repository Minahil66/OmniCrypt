#include "logger.h"

void Log::setter(string msg, string lev, string cipher, int step, string opr, string file) {
    cipherName = cipher;
    stepNumber = step;
    operation = opr;
    fileName = file;
    message = msg;
    level = lev;

    time_t rawTime;
    time(&rawTime);
    timestampStr = ctime(&rawTime);

    // Remove trailing newline if present
    if (!timestampStr.empty() && timestampStr.back() == '\n') {
        timestampStr.pop_back();
    }
}

void Logger::log(string msg, string level, string cipherName, int stepNumber, string operation, string fileName) {
    Log l1;
    l1.setter(msg, level, cipherName, stepNumber, operation, fileName);
    logs.push_back(l1);
}

void Logger::info(string msg, string cipherName, int stepNumber, string operation, string fileName) {
    log(msg, "INFO", cipherName, stepNumber, operation, fileName);
}

void Logger::error(string msg, string cipherName, int stepNumber, string operation, string fileName) {
    log(msg, "ERROR", cipherName, stepNumber, operation, fileName);
}

void Logger::debug(string msg, string cipherName, int stepNumber, string operation, string fileName) {
    log(msg, "DEBUG", cipherName, stepNumber, operation, fileName);
}

void Logger::warn(string msg, string cipherName, int stepNumber, string operation, string fileName) {
    log(msg, "WARN", cipherName, stepNumber, operation, fileName);
}
void Logger::print() {
    for (size_t i = 0; i < logs.size(); i++) {
        cout << "[" << logs[i].timestampStr << "] "
             << "[" << logs[i].level << "] "
             << "[Step " << logs[i].stepNumber << "] "
             << "[" << logs[i].cipherName << "] "
             << "[" << logs[i].operation << "] "
             << logs[i].message
             << " (File: " << logs[i].fileName << ")"
             << endl;
    }
}

void Logger::saveToFile() {
    ofstream out("log.txt", ios::app);  // ios::app = append mode
    if (!out.is_open()) {
        cout << "Error: File failed to open\n";
        return;
    }

    for (size_t i = 0; i < logs.size(); i++) {
        out << "[" << logs[i].timestampStr << "] "
            << "[" << logs[i].level << "] "
            << "[Step " << logs[i].stepNumber << "] "
            << "[" << logs[i].cipherName << "] "
            << "[" << logs[i].operation << "] "
            << logs[i].message
            << " (File: " << logs[i].fileName << ")"
            << endl;
    }

    out.close();
}

void Logger::clearLogs() {
     	if(!logs.empty()){
    	logs.clear();
    	cout<<"History cleared"<<endl;
    }
    else{
    	cout<<"History already empty"<<endl;
			}
}
