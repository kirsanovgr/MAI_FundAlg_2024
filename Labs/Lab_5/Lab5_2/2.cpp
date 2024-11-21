#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include <string>

class encoder {
private:
    std::vector<std::byte> key;

    //для инициализации S-блока
    void rc4_init(std::vector<std::byte>& S, const std::vector<std::byte>& key) {
        for (size_t i = 0; i < 256; ++i) {
            S[i] = static_cast<std::byte>(i);
        }

        size_t j = 0;
        for (size_t i = 0; i < 256; ++i) {
            j = (j + static_cast<size_t>(S[i]) + static_cast<size_t>(key[i % key.size()])) % 256;
            std::swap(S[i], S[j]);
        }
    }

    // для RC4
    void rc4_crypt(std::istream& input, std::ostream& output, const std::vector<std::byte>& key) {
        std::vector<std::byte> S(256);
        rc4_init(S, key);

        size_t i = 0, j = 0;

        char ch;
        while (input.get(ch)) {
            i = (i + 1) % 256;
            j = (j + static_cast<size_t>(S[i])) % 256;

            std::swap(S[i], S[j]);

            std::byte k = S[(static_cast<size_t>(S[i]) + static_cast<size_t>(S[j])) % 256];
            char encrypted_ch = ch ^ static_cast<char>(k);
            output.put(encrypted_ch);
        }
    }

public:
    encoder(const std::vector<std::byte>& encryption_key) : key(encryption_key) {
        if (key.empty()) {
            throw std::invalid_argument("Encryption key cannot be empty");
        }
    }

    // Mutator для ключа
    void set_key(const std::vector<std::byte>& new_key) {
        if (new_key.empty()) {
            throw std::invalid_argument("New key cannot be empty");
        }
        key = new_key;
    }

    void encode(const std::string& input_file, const std::string& output_file, bool encrypt) {
        (void)encrypt; // Указывает компилятору, что параметр используется намеренно
        std::ifstream input(input_file, std::ios::binary);
        if (!input) {
            throw std::ios_base::failure("Failed to open input file");
        }

        std::ofstream output(output_file, std::ios::binary);
        if (!output) {
            throw std::ios_base::failure("Failed to open output file");
        }

        rc4_crypt(input, output, key);
    }

};

int main() {
    try {
        std::vector<std::byte> key = {std::byte(1), std::byte(2), std::byte(3), std::byte(4)};
        encoder enc(key);

        enc.encode("original.txt", "encrypted.txt", true);  // Шифрование
        enc.encode("encrypted.txt", "decrypted.txt", false); // Дешифрование

        std::cout << "Шифрование и дешифрование завершены. Проверьте файлы." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
