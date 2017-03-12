//
//  Predicate.cpp
//  Datalog_Parser_p2
//
//  Created by William Pinkston on 3/9/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#include "Predicate.h"

//enum predicate::state {off=0, on};

predicate::predicate(std::string initId)
{
    char finder = initId.find("\"");
    initId.erase(0,++finder);
    finder = initId.find("\"");
    char finder2 = initId.find(EOF);
    initId.erase(finder, finder2);
    _Id = initId;
    openExpression = NULL;
    expressionSwitch = predicate::off;
    parenCount = 0;
}

bool predicate::addParam(std::string paramToken)
{
    std::stringstream tokenParser;
    tokenParser << paramToken;
    tokenParser.get(); //discard opening parenthesis of token
    
    std::string tokenName;
    std::getline(tokenParser, tokenName, ','); //grab name of token
    
    std::string tokenContents;
    std::getline(tokenParser, tokenContents, '"');
    std::getline(tokenParser, tokenContents, '"');
    
    if (fillExpression(tokenName, tokenContents)) return true;

    parameter *point;
    
    if (tokenName == "STRING")
    {
        point = new parameter_string(tokenContents);
        parameterList.push(point);
    }
    if (tokenName == "ID")
    {
        point = new parameter_id(tokenContents);
        parameterList.push(point);
    }
    
    if (tokenName == "LEFT_PAREN")
    {
        openExpression = new parameter_expression();
        expressionSwitch = predicate::on;
        parenCount++;
    }

    return true;
}

bool predicate::fillExpression(std::string tokenName, std::string tokenContents)
{
    if (expressionSwitch == predicate::off)
    {
        return false;
    }
    if (tokenName == "LEFT_PAREN")
    {
        parenCount++;
        if (openExpression->addExpression()) return true;
    }
    if (tokenName == "ID")
    {
        if (openExpression->addID(tokenContents)) return true;
    }
    if (tokenName == "STRING")
    {
        if (openExpression->addString(tokenContents)) return true;
    }
    if (tokenName == "ADD")
    {
        if (openExpression->addOperator('+')) return true;
    }
    if (tokenName == "MULTIPLY")
    {
        if (openExpression->addOperator('*')) return true;
    }
    if (tokenName == "RIGHT_PAREN")
    {
        parenCount--;
        if ((parenCount == 0) && openExpression->checkComplete())
        {
            expressionSwitch = predicate::off;
            parameterList.push(openExpression);
//            delete openExpression;
            openExpression = NULL;
            return true;
        }
        else return true;
    }
    return false;
}


std::string predicate::toString()
{
    if (parameterList.size() == 0)
    {
        return "";
    }
    std::stringstream retVal;
    retVal << _Id << "(" << parameterList.front()->toString();
    parameterList.pop();
    int max = (int)parameterList.size();
    for (int i = 0; i < max; i++)
    {
        retVal << "," << parameterList.front()->toString();
        parameterList.pop();
    }
    retVal << ")";
    return retVal.str();
}



