#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>
#include <cstddef>

class Encoder {
private:
    std::vector<std::byte> key;

    void initializeRC4State(std::vector<unsigned char>& S) const {
        const size_t keyLength = key.size();
        for (size_t i = 0; i < 256; ++i) {
            S[i] = static_cast<unsigned char>(i);
        }

        size_t j = 0;
        for (size_t i = 0; i < 256; ++i) {
            j = (j + S[i] + static_cast<unsigned char>(key[i % keyLength])) % 256;
            std::swap(S[i], S[j]);
        }
    }

    unsigned char getNextKeyByte(std::vector<unsigned char>& S) const {
        static size_t i = 0, j = 0;
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        std::swap(S[i], S[j]);
        return S[(S[i] + S[j]) % 256];
    }

public:
    Encoder(const std::vector<std::byte>& encryptionKey) : key(encryptionKey) {}

    Encoder(const Encoder& other) : key(other.key) {}

    Encoder& operator=(const Encoder& other) {
        if (this != &other) {
            key = other.key;
        }
        return *this;
    }

    void encode(const std::string& inputFile, const std::string& outputFile, bool encrypt) const {
        if (inputFile.empty() || outputFile.empty()) {
            throw std::invalid_argument("File paths cannot be empty");
        }

        std::ifstream inFile(inputFile, std::ios::binary);
        if (!inFile.is_open()) {
            throw std::runtime_error("Error opening input file");
        }

        std::ofstream outFile(outputFile, std::ios::binary);
        if (!outFile.is_open()) {
            throw std::runtime_error("Error opening output file");
        }

        std::vector<unsigned char> S(256);
        initializeRC4State(S);

        char byte;
        while (inFile.get(byte)) {
            unsigned char keyByte = getNextKeyByte(S);
            char result = byte ^ keyByte;
            outFile.put(result);
        }

        inFile.close();
        outFile.close();
    }

    void setKey(const std::vector<std::byte>& newKey) {
        key = newKey;
    }
};

int main() { //компиляция: g++ -std=c++17 -o 2 task_2.cpp
    try {
        std::string inputFile, outputFile, action;
        std::vector<std::byte> encryptionKey = { std::byte{0x01}, std::byte{0x02}, std::byte{0x03}, std::byte{0x04} };

        std::cout << "Enter the input file path: ";
        std::cin >> inputFile;

        std::cout << "Enter the output file path: ";
        std::cin >> outputFile;

        std::cout << "Enter the action (encrypt/decrypt): ";
        std::cin >> action;

        if (action != "encrypt" && action != "decrypt") {
            throw std::invalid_argument("Invalid action. Please enter 'encrypt' or 'decrypt'");
        }

        bool encrypt = (action == "encrypt");

        Encoder encoder(encryptionKey);

        encoder.encode(inputFile, outputFile, encrypt);

        if (encrypt) {
            std::cout << "Encryption completed" << std::endl;
        } else {
            std::cout << "Decryption completed" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
