#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <errno.h>

// Necessary for word subbing, especially if they overlap
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

// Substitute words based on the number mapping
void sub_words(std::string& line)
{
    for (const auto &num : NUMBER_MAP)
    {
        size_t pos = line.find(num.first);

        while (pos != std::string::npos)
        {
            line.replace(pos, num.first.length(), num.second);
            pos = line.find(num.first, pos + num.second.length());
        }
    }
}

// Extracts the "encoded" calibration value that is in the line
int extract_calibration(const std::string& line)
{
    int digits[2]{ };

    // Find the first digit
    for (const char& c : line)
    {
        if (std::isdigit(c))
        {
            digits[0] = c - '0';
            break;
        }
    }

    // Find the second digit
    for (auto it = line.rbegin(); it != line.rend(); ++it)
    {
        if (std::isdigit(*it))
        {
            digits[1] = *it - '0';
            break;
        }
    }

    return digits[0] * 10 + digits[1];
}

void process_lines(std::vector<std::string>& lines, int& sum)
{
    for (std::string l : lines)
    {
        sub_words(l);
        sum += extract_calibration(l);
    }
}

// Reads lines from input files and stored in a vector for later processing
std::vector<std::string> load_lines(const std::string& file_name)
{
    std::ifstream inf{ file_name };

    std::vector<std::string> lines{ };
    std::string line{ };

    while (std::getline(inf, line))
    {
        lines.push_back(line);
    }

    return lines;
}

int main(int argc, char* argv[])
{
    int sum{ };

    // Must include an input file as an arg
    if (argc != 2)
    {
        std::cerr << "Error!\n";
        std::cerr << "\tExpected form: Trebuchet.exe [name of input file].txt\n\n";
        std::cerr << "\tTerminating...\n";

        return EINVAL;
    }

    // Get file name
    std::string file_name{ argv[1] };

    // Get input lines for processing
    auto lines{ load_lines(file_name) };

    // Process the input
    process_lines(lines, sum);

    std::cout << "The sum of the calibration values is: " << sum << "\n";

    return 0;
}