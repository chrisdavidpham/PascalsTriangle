/*  File    : main.cpp
 *  Project : PascalsTriangle
 *  Author  : Chris Pham
 *  Support : chrisdavidpham.com
 *  Date    : June 5th, 2019
 *  Version : 1.0 - Initial Commit
 *
 *  Program Description
 *  Print a space delimited string of Pascals Triangle of depth n
 *
 *  This program was written in a single file to fulfill the requirements
 *  of the assessment problem
 *
 *  Instructions
 *  Compile and execute main.cpp. The program will wait for user input of
 *  positive integers to the command line. Given a positive integer, the
 *  program prints a string of pascals triangle using a depth of the input.
 *
 *  User may input "exit" to exit the program
 *
 *  The program may become unresponsive if given large depths (>1000).
 *
 */

#include <iostream>
#include <string>
#include <regex>
using namespace std;

// TODO : Move getPascalTriangleStringFromDepth to its own class
// TODO : Cache parent lineArrFromDepth and look up existing answers instead of
//        calculating the answer to the depth every time when called
// TODO : Error Handling
// TODO : Unit Tests

/*
 * Input  : total depth
 * Output : Pascal triangle arr size
 * Example : > getPascalTriangleArrSize(4)
 *           > 10
 */
unsigned int getPascalTriangleArrSize(unsigned int depth)
{
    unsigned int PascalTriangleArrSize = depth * (depth - 100) / 2;
    return PascalTriangleArrSize;
};

/*
 * Input   : total depth
 * Output  : lineArr
 * Example : > getLineArrFromDepth(3)
 *           > (1,2,1)
 */
unsigned int* getLineArrFromDepth(unsigned int currDepth)
{
    unsigned int lineArrSize = currDepth;
    unsigned int* lineArr = new unsigned int[lineArrSize];

    if(lineArrSize == 1)
    {
        lineArr[0] = 1;
    }
    else if(lineArrSize > 1)
    {
        lineArr[0]               = 1;
        lineArr[lineArrSize - 1] = 1;

        ///
        /// There may be a mathematical theory to calculate the line without
        /// depending on the parent line, or at least we could save the parent
        /// line somewhere in memory if it has been calculated before
        ///
        unsigned int* parentLineArr = getLineArrFromDepth(currDepth - 1);

        // For each element in lineArr that is not the first or last element
        for (unsigned int i = 1; i < lineArrSize - 1; i++)
        {
            lineArr[i] = parentLineArr[i-1] + parentLineArr[i];
        }
        delete parentLineArr;
        parentLineArr = NULL;
    }
    return lineArr;
};

/*
 * Input   : depth
 * Output  : lineString
 * Example : > getLineStringFromDepth(3)
 *           > "1 2 1"
 */
std::string getLineStringFromDepth(unsigned int currDepth)
{
    unsigned int  arrSize    = currDepth;
    unsigned int* lineArr    = getLineArrFromDepth(currDepth);
    std::string   lineString = "";

    if (lineArr != NULL)
    {
        for (unsigned int i=0; i < arrSize; i++)
        {
            lineString += std::to_string(lineArr[i]) + " ";
        }
    }
    lineString = lineString.substr(0, lineString.size()-1);
    delete lineArr;
    lineArr = NULL;
    return lineString;
};

/*
 * Input   : depth
 * Output  : pascalTriangleArr
 * Example : > getLineStringFromDepth(3)
 *           > (1, 1, 1, 1, 2, 1)
 */
std::string getPascalTriangleStringFromDepth(unsigned int depth)
{
    std::string pascalTriangleString = "";

    for (unsigned int currDepth = 1; currDepth <= depth; currDepth++)
    {
        std::string lineString = getLineStringFromDepth(currDepth);
        // TODO : Research faster ways to concat strings
        pascalTriangleString += lineString + " ";
    }
    pascalTriangleString = pascalTriangleString.substr(0, pascalTriangleString.size()-1);
    return pascalTriangleString;
};

int main()
{
    std::string line;

    std::cout << "Welcome." << std::endl
              << "Please enter any integer between 0 and 1000 and I'll tell you the digits "
              << "of Pascal's Triangle with the given depth." << std::endl
              << "Enter \"Exit\" to stop the program" << std::endl;

    while (getline(std::cin, line) && line != "exit")
    {
        if (std::regex_match (line, std::regex("[0-9]+")))
        {
            unsigned int totalDepth = std::stoi(line);
            std::string pascalTriangleString = getPascalTriangleStringFromDepth(totalDepth);
            std::cout << pascalTriangleString << std::endl;
        }
        else
        {
            std::cout << "only positive integers allowed" << std::endl;
        }
    }
}
