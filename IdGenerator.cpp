#include "IdGenerator.h"

std::string IdentifierGenerator::getNextIdentifier(const std::string& identifier)
{
    std::vector<std::string> id;
    std::string nextId;
    for (int i = 0; i < identifier.length() - 1; i++)
    {
        if (identifier[i] == def || digits.find(identifier[i]) != std::string::npos) continue;
        std::string suffix;
        suffix += identifier[i];
        suffix += identifier[i + 1];
        id.push_back(suffix);
    }
    for (int i = id.size() - 1; i >= 0; i--)
    {
        incSuffix(id[i]);
        if (!carry) break;
    }
    for (int i = 0; i < id.size(); i++)
    {
        nextId += id[i];
        if (id.size() >= 2 && i < id.size() - 1)
        {
            nextId += def;
        }
    }
    if (carry)
    {
        if (nextId.length() >= maxLength)
        {
            throw std::range_error("Max size identificator");
        }
        else
        {
            return "A1-" + nextId;
        }
    }
    return nextId;
}

void IdentifierGenerator::incSuffix(std::string& suf)
{
    char letter = suf[0];
    char digit = suf[1];
    int letterPos = letters.find(letter);
    int digitPos = digits.find(digit);
    if (letterPos == std::string::npos || digitPos == std::string::npos)
    {
        throw std::invalid_argument("Uncorrect identidier");
    }
    else
    {
        if (digitPos == digits.length() - 1 && letterPos == letters.length() - 1)
        {
            digit = digits[0];
            letter = letters[0];
            carry = true;
        }
        else if (digitPos == digits.length() - 1)
        {
            digit = digits[0];
            letter = letters[letterPos + 1];
            carry = false;
        }
        else
        {
            digit = digits[digitPos + 1];
            carry = false;
        }

    }
    suf = { letter, digit };
}

int main()
{
    IdentifierGenerator generator;
    std::string id;

    // Пример использования
    try {
        id = "A1";
        std::cout << generator.getNextIdentifier(id) << std::endl; // A2
        id = "A9";
        std::cout << generator.getNextIdentifier(id) << std::endl; // B1
        id = "Z9";
        std::cout << generator.getNextIdentifier(id) << std::endl; // A1-A1
        id = "A1-A1";
        std::cout << generator.getNextIdentifier(id) << std::endl; // A1-A2
        id = "A1-Z9";
        std::cout << generator.getNextIdentifier(id) << std::endl; // A2-A1
        id = "Z9-Z9";
        std::cout << generator.getNextIdentifier(id) << std::endl; // A1-A1-A1
        id = "A1-Z9-Z9";
        std::cout << generator.getNextIdentifier(id) << std::endl; // A2-A1-A1
        id = "Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9";
        std::cout << generator.getNextIdentifier(id) << std::endl; // exception
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

}