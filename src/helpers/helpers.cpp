#include "helpers.h"

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