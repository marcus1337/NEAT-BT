#include "IOHandler.h"
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

void IOHandler::makeFolder(std::string folderName) {
    std::string folderPath = std::filesystem::current_path().string();
    folderPath += "\\" + folderName;
    fs::create_directory(folderPath);
}