

#ifndef LAB5_EX3_H
#define LAB5_EX3_H

#include <cstring>
#include <iostream>

class incorrect_index_array : std::exception {};

class logical_values_array {
   protected:
	unsigned int value;

   public:
	logical_values_array(unsigned int value = 0) : value(value){};

	unsigned int get_value() const;

	bool get_bit(unsigned int index) const;
	bool equals(const logical_values_array& second) const;
	void to_char_arr(char* result) const;

	logical_values_array operator~() const;
	logical_values_array operator&(const logical_values_array& second) const;
	logical_values_array operator|(const logical_values_array& second) const;
	logical_values_array operator^(const logical_values_array& second) const;
	logical_values_array operator<=(const logical_values_array& second) const; // импликация
	logical_values_array operator>(const logical_values_array& second) const; // коимпликация
	logical_values_array operator==(const logical_values_array& second) const;
	logical_values_array pierce_arrow(const logical_values_array& second) const;
	logical_values_array sheffer_stroke(const logical_values_array& second) const;


};

std::ostream& operator<<(std::ostream& out, const logical_values_array& value);

#endif  // LAB5_EX3_H
