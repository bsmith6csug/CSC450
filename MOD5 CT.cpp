
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <filesystem>

void appendToFile(const std::string& filename) {
    std::ifstream checkFile(filename);
    bool fileExists = checkFile.good();
    checkFile.close();

    std::ofstream file(filename, std::ios::app);
    if (!file) {
        std::cerr << "Error occurred: Unable to open " << filename << ", :(";
        return;
    }

    std::string userInput;
    std::cout << "To append " << filename << ", please enter some text: ";
    std::getline(std::cin, userInput);

    if (fileExists && std::filesystem::file_size(filename) > 0) {
        file << std::endl;
    }

    file << userInput;

    if (file.good()) {
        std::cout << "Successfully appended " << filename <<", :)";
    } else {
        std::cerr << "Error occurred: Append failed :(" << std::endl;
    }
}

void reverseFileContent(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "Error occurred: Unable to open " << inputFile << ", :(";
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Error occurred: Unable to open " << outputFile << ", :(";
        return;
    }

    for (const auto& originalLine : lines) {
        std::string reversedLine = originalLine;
        std::reverse(reversedLine.begin(), reversedLine.end());
        outFile << reversedLine << std::endl;
    }

    std::cout << "Text has been reversed and saved to: " << outputFile << std::endl;
}

int main() {
    const std::string INPUT_FILE = "CSC450_CT5_mod5.txt";
    const std::string OUTPUT_FILE = "CSC450-mod5-reverse.txt";

    appendToFile(INPUT_FILE);
    std::cout << "\n--- Text is being reversed ---\n";
    reverseFileContent(INPUT_FILE, OUTPUT_FILE);

    return 0;
}





