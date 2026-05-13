#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "OpStats.h"

class Logger {
private:
    std::ofstream logFile;
    OpStats totalUnordered, totalOrdered, totalAVL, totalHash;

public:
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios::out);
        logFile << "=== Table Operations Log ===\n\n";
    }

    ~Logger() {
        logFile << "\n=== FINAL SUMMARY (Total Operations) ===\n";
        WriteSummary("Unordered Table", totalUnordered);
        WriteSummary("Ordered Table", totalOrdered);
        WriteSummary("AVL Tree Table", totalAVL);
        WriteSummary("Hash Table", totalHash);
        logFile.close();
    }

    void LogOperation(const std::string& opName, const std::string& key,
        const OpStats& unord, const OpStats& ord,
        const OpStats& avl, const OpStats& hash) {

        logFile << "Operation: " << opName << " | Key: " << key << "\n";
        WriteRow("Unordered", unord);
        WriteRow("Ordered", ord);
        WriteRow("AVL Tree", avl);
        WriteRow("Hash Table", hash);
        logFile << "--------------------------------------------------\n";

        totalUnordered += unord;
        totalOrdered += ord;
        totalAVL += avl;
        totalHash += hash;
    }

private:
    void WriteRow(const std::string& name, const OpStats& s) {
        logFile << std::left << std::setw(12) << name
            << " -> Total Operations: " << s.total << "\n";
    }

    void WriteSummary(const std::string& name, const OpStats& s) {
        logFile << name << ": " << s.total << " ops\n";
    }
};