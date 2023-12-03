#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <errno.h>

const std::unordered_map<std::string, int> RGB_TRANSLATE{
    {"red", 0},
    {"green", 1},
    {"blue", 2}
};

std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> result{ };
    std::istringstream iss{ s };
    std::string token;

    while (std::getline(iss, token, delimiter))
    {
        result.push_back(token);
    }

    return result;
}

std::vector<std::string> load_lines(const std::string& file_name)
{
    std::ifstream inf{ file_name };

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(inf, line))
    {
        lines.push_back(line);
    }

    return lines;
}

bool process_subsets(std::vector<std::string>& subsets,
    std::vector<int>& rgb)
{
    for (std::string s : subsets)
    {
        auto cubes{ split(s, ',') };


        for (std::string draw : cubes)
        {
            auto vals{ split(draw, ' ')};
            vals.erase(vals.begin());

            // std::cout << std::stoi(vals[0]);
            if (std::stoi(vals[0]) > RGB_TRANSLATE.at(vals[1]))
            {
                return false;
            }
            // if (std::stoi(vals[0]) > RGB_TRANSLATE.find(vals[1]))
            //     return false;
        }
    }

    return true;
}

std::vector<int> process_lines(std::vector<std::string>& lines,
    std::vector<int>& rgb)
{
    std::vector<int> game_ids{ };

    for (std::string s : lines)
    {
        auto game_split{ split(s, ':') };
        auto cube_split{ split(game_split[1], ';') };

        process_subsets(cube_split, rgb);
    }

    return game_ids;
}

int main(int argc, char* argv[])
{
    // Must include input file and three RGB values
    if (argc != 5)
    {
        std::cerr << "Error!";
        std::cerr << "\tExpected form: Cube-Conundrum.exe <file_name> <r> <g> <b>";
        std::cerr << "\tTerminating...\n";

        return EINVAL;
    }

    // Get file name
    std::string file_name{ argv[1] };

    // Extract RGB values
    std::vector<int> rgb{ atoi(argv[2]), atoi(argv[3]), atoi(argv[4]) };

    // Obtain lines
    auto lines{ load_lines(file_name) };

    auto dum{ process_lines(lines, rgb) };

    return 0;
}