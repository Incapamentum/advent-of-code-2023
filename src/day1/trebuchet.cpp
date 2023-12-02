#include <array>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

#include <errno.h>

// Debug purposes
// #define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
#include <filesystem>

void print_cwd(void)
{
    std::filesystem::path cwd = std::filesystem::current_path();
    std::cerr << "Current working directory: "
        << cwd << "\n";
}
#endif

// Global variable time
const std::unordered_map<std::string, std::string> NUMBER_MAP{
    {"one", "o1e"},
    {"two", "t20"},
    {"three", "t3e"},
    {"four", "f4r"},
    {"five", "f5e"},
    {"six", "s6x"},
    {"seven", "s7n"},
    {"eight", "e8t"},
    {"nine", "n9e"},
};

int obtain_val(const std::array<int, 2> &d)
{
    int num{ };

    for (const auto& n : d)
    {
        num = num * 10 + n;
    }

    return num;
}

int extract_calibration_val(std::string_view sv)
{
    std::array<int, 2> digits{ -1, -1 };

    for (const auto& c : sv)
    {
        if (isdigit(c))
        {
            // Populate with first encountered digit
            if (digits[0] == -1)
            {
                digits[0] = c - '0';
                digits[1] = c - '0';
            }
            else
            {
                digits[1] = c - '0';
            }
        }
    }

    std::cout << "Extracted number: " << digits[0] << digits[1] << "\n";

    return obtain_val(digits);
}

int main(int argc, char* argv[])
{
#ifdef ENABLE_DEBUG
print_cwd();
#endif

    // Must include an input file as an arg
    if (argc != 2)
    {
        std::cerr << "Error!\n";
        std::cerr << "\tExpected form: Trebuchet.exe [name of input file].txt\n\n";
        std::cerr << "\tTerminating...\n";

        return EINVAL;
    }

    std::stringstream file_name{ argv[1] };
    std::ifstream inf{ file_name.str() };
    int acc{ };

    // Check if file was able to be opened
    if (!inf)
    {
        std::cerr << "Uh oh, sample-puzzle.txt could not be opened for reading!\n";
        return ENOENT;
    }

    // Read from file, line by line
    std::string line;
    while (std::getline(inf, line))
    {
        // Replace words
        for (const auto &num : NUMBER_MAP)
        {
            size_t pos = line.find(num.first);
            while (pos != std::string::npos)
            {
                line.replace(pos, num.first.length(), num.second);
                pos = line.find(num.first, pos + num.second.length());
            }
        }

        acc += extract_calibration_val(line);
    }

    std::cout << "The sum of the calibration values is: " << acc << "\n";

    return 0;
}