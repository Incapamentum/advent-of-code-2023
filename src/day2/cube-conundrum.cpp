#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <errno.h>

#include "helpers.h"

const std::unordered_map<std::string, int> RGB_TRANSLATE
{
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

// Processes
bool process_encounter(std::string game, std::vector<int>& rgb)
{
    std::regex game_pattern("\\s*(\\d+)\\s*(red|green|blue)");
    std::smatch matches{ };
    std::map<std::string, int> vals{ };

    std::string::const_iterator start(game.cbegin());

    // Obtain a mapping
    while (std::regex_search(start, game.cend(), matches, game_pattern))
    {
        vals[matches[2]] = std::stoi(matches[1]);
        start = matches.suffix().first;
    }

    // Process the results
    for (const auto& pair : vals)
    {
        // Determine possibility
        if (pair.second > rgb[RGB_TRANSLATE.at(pair.first)])
        {
            return false;
        }
    }

    return true;
}

// Determines if a game by processing each encounter
bool valid_game(std::vector<std::string>& subsets,
    std::vector<int>& rgb)
{
    // Process each encounter
    for (std::string encounter : subsets)
    {
        if (!process_encounter(encounter, rgb))
        {
            return false;
        }
    }

    return true;
}

int extract_game_id(const std::string& s)
{
    std::regex rgx{"Game (\\d+)"};
    std::smatch match{ };

    std::regex_search(s, match, rgx);

    return std::stoi(match.str(1));
}

// Process the lines from the input file
//
// Idea is to split the input line into two parts, with the first being used to
// extract the game ID, and the second being further processed to determine if
// the set of games is possible
void process_lines(std::vector<std::string>& lines,
    std::vector<int>& rgb, int& sum)
{
    for (std::string s : lines)
    {
        auto game_split{ split(s, ':') };
        auto gameset_split{ split(game_split[1], ';') };
        auto game_id{ extract_game_id(game_split[0]) };

        if (valid_game(gameset_split, rgb))
        {
            sum += game_id;
        }
    }
}

int main(int argc, char* argv[])
{
    int sum{ };

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

    // Process the input
    process_lines(lines, rgb, sum);

    std::cout << "The sum of the IDs of valid games is: " << sum << "\n";

    return 0;
}