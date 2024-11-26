#pragma once

#include <cstddef>
#include <iostream>
#include <vector>
#include <filesystem>


class encoder {
   private:
	std::vector<uint8_t> key;

	static void initialize_s_box(std::vector<uint8_t>& s_box, const std::vector<uint8_t>& key);
	static uint8_t generate_key_stream(std::vector<uint8_t>& s_box, size_t& i, size_t& j);

   public:
	explicit encoder(const std::vector<uint8_t>& key) : key(key){};

	void encode(const std::string& input_filename, const std::string& output_filename,
	            [[maybe_unused]] bool is_encryption);
	void set(const std::vector<uint8_t>& key);
	std::vector<uint8_t> get() const;
};
