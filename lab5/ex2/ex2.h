
#ifndef LAB5_EX2_H
#define LAB5_EX2_H

#include <cstddef>
#include <iostream>
#include <vector>

class not_open_stream : std::exception {};

class encoder {
   private:
	std::vector<std::byte> key;

	static void initialize_s_box(std::vector<std::byte>& s_box, const std::vector<std::byte>& key);
	static std::byte generate_key_stream(std::vector<std::byte>& s_box, size_t& i, size_t& j);

   public:
	encoder(const std::vector<std::byte>& key) : key(key){};

	void encode(const std::string& input_filename, const std::string& output_filename,
	            [[maybe_unused]] bool is_encryption);
	void set(const std::vector<std::byte>& key);
	std::vector<std::byte> get() const;

};

#endif  // LAB5_EX2_H
