#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint> // Для uint8_t
#include <stdexcept>
#include <string>

class encoder {
private:
    std::vector<uint8_t> key;

    // Инициализация S-блока
	void rc4_init(std::vector<uint8_t>& S, const std::vector<uint8_t>& key) {
		for (size_t i = 0; i < 256; ++i) {
			S[i] = static_cast<uint8_t>(i);
		}

		size_t j = 0;
		for (size_t i = 0; i < 256; ++i) {
			j = (j + S[i] + key[i % key.size()]) % 256;
			std::swap(S[i], S[j]);
		}
	}

    // RC4 криптографический алгоритм
    void rc4_crypt(std::istream& input, std::ostream& output, const std::vector<uint8_t>& key) {
        std::vector<uint8_t> S(256);
        rc4_init(S, key);

        uint8_t i = 0, j = 0;

        char ch;
        while (input.get(ch)) {
            i = i + 1;
            j = j + S[i];

            std::swap(S[i], S[j]);

            uint8_t k = S[S[i] + S[j]];
            char encrypted_ch = ch ^ static_cast<char>(k);
            output.put(encrypted_ch);
        }
    }

public:
    encoder(const std::vector<uint8_t>& encryption_key) : key(encryption_key) {
        if (key.empty()) {
            throw std::invalid_argument("Encryption key cannot be empty");
        }
    }

    // Mutator для ключа
    void set_key(const std::vector<uint8_t>& new_key) {
        if (new_key.empty()) {
            throw std::invalid_argument("New key cannot be empty");
        }
        key = new_key;
    }

    void encode(const std::string& input_file, const std::string& output_file, [[maybe_unused]] bool encrypt) {
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
        std::vector<uint8_t> key = {1, 2, 3, 4};
        encoder enc(key);

        enc.encode("original.txt", "encrypted.txt", true);  // Шифрование
        enc.encode("encrypted.txt", "decrypted.txt", false); // Дешифрование

        std::cout << "Шифрование и дешифрование завершены. Проверьте файлы." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
