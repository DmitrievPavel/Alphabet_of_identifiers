#pragma once

#include <iostream>
#include <string>
#include <vector>

class IdentifierGenerator {
public:
	IdentifierGenerator() = default;
	std::string getNextIdentifier(const std::string& identifier);
private:
	bool carry = false;
	const size_t maxLength = 18;
	const std::string letters = "ABCDEFGHIKNLOPRSTUVWXYZ";
	const std::string digits = "123456789";
	const char def = '-';
	void incSuffix(std::string& suf);
};
