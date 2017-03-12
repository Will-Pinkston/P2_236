 //
//  main.cpp
//  Lexical_Analyzer_p1
//
//  Created by William Pinkston on 2/2/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <ctype.h>

#include "Analyzer.h"
#include "Parser.h"

void ReadFile(std::string filename, std::vector<char>& Input)
{
    std::ifstream inFile(filename.c_str());
    if (inFile.fail())
    {
        return;
    }
    char inChar = inFile.get();
    while (inFile.good())
    {
        Input.push_back(inChar);
        //std::cout << inChar;
        inChar = inFile.get();
    }
    if (inFile.eof())
    {
        Input.push_back('\0');
    }
}


int main(int argc, const char * argv[]) {
    
    if (argc < 2)
    {
        std::cout << "Incorrect usage. Expected " << argv[0] << " <filename>" << std::endl;
        return 0;
    }
    //
    //
    //

//    std::string test4 = "this is a \"test\" to see how groovy strings are.";
//    char finder = test4.find("\"");
//    test4.erase(0,++finder);
//    finder = test4.find("\"");
//    char finder2 = test4.find(EOF);
//    test4.erase(finder, finder2);
//    std::cout << test4 << std::endl;
    
    //
    //
    //
    analyzer lexer;
    
    std::vector<char> Input;
    ReadFile(argv[1],Input);
    std::stack<std::string> tokens;
    tokens = lexer.run(Input);

    parser logParser(tokens);
    logParser.run();
    
    return 0;
}






