#pragma once

#include <cstring>
#include <iostream>

class logical_values_array {
   protected:
	unsigned int value;

   public:
	logical_values_array(unsigned int value) : value(value){};
	logical_values_array(const logical_values_array& ar);
	logical_values_array& operator=(const logical_values_array& ar);

	unsigned int get_value() const;

	bool get_bit(unsigned int index) const;
	static bool equals(const logical_values_array& first, const logical_values_array& second);
	void to_char_arr(char* result) const;

	logical_values_array operator~() const;
	logical_values_array operator&(const logical_values_array& second) const;
	logical_values_array operator|(const logical_values_array& second) const;
	logical_values_array operator^(const logical_values_array& second) const;
	logical_values_array operator<=(const logical_values_array& second) const;  // импликация
	logical_values_array operator>(const logical_values_array& second) const;   // коимпликация
	logical_values_array operator==(const logical_values_array& second) const;
	logical_values_array pierce_arrow(const logical_values_array& second) const;
	logical_values_array sheffer_stroke(const logical_values_array& second) const;
};

std::ostream& operator<<(std::ostream& out, const logical_values_array& value);
