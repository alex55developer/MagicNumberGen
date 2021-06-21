// Test for Magic Sequence Generator
// 21.6.2021, 18:33, +30C

#include "Sequence.h"

#include <string>
#include <iostream>

#include <QCoreApplication>

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    std::string input;
    int counter = 0;
    if (3 == argc)
    {
        // Get params..
        counter = atoi(argv[2]);
        if (counter <= 0)
        {
            std::cout << "*** wrong counter\n";
            return -1;
        }

        // Check input string..
        input = argv[1];
        if (!MagicSequence::ValidateFormat(input))
        {
            std::cout << "*** wrong input sequence\n";
            return -1;
        }
    }
    else
    {
        std::cout << "    Magic Sequence Generator\nParameters: initial sequence, counter\n";
        return 0;
    }

    std::string output;
    for (int ind = 0; ind < counter; ++ind)
    {
        if (!MagicSequence::GetNextSequence(input, output))
        {
            std::cout << ind << "\t" << "[" << input << "]\n";
            std::cout << "*** ERROR: can't find next sequence ***" << std::endl;
            break;
        }
        else
        {
            std::cout << ind + 1 << "\t[" << output << "]\n";
            input = output;
        }
    }

    return 0;
}
