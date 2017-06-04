#include <bashclass/BReturn.h>
#include <bashclass/BException.h>
#include <bashclass/BFunction.h>
#include <bashclass/BReport.h>
#include <bashclass/BTypes.h>
#include <iostream>

void BReturn::verifyReturn() {

    if(!m_expression) {
        throw BException("Cannot verify a return statement without an expression");
    }

    // Get ancestor function
    auto function = m_parentScope->findClosestFunction();
    if(!function) {
        throw BException("Cannot verify a return statement without a function");
    }

    // If function is of type void, then a return statement is not expected
    if(function->requiresReturn()) {
        std::string functionType = function->getType()->getValue();
        std::string expressionType = m_expression->getTypeValueAsString();
        if(!function->hasKnowType()) {
            BReport::getInstance().error()
                    << "Cannot return expression in function " << function->getName()->getValue()
                    << " of undefined type" << std::endl;
            BReport::getInstance().printError();
        } else if(expressionType == BType::UNDEFINED) {
            BReport::getInstance().error()
                    << "Function " << function->getName()->getValue()
                    << " has return statement but of undefined type" << std::endl;
            BReport::getInstance().printError();
        } else if(functionType != BType::TYPE_VALUE_ANY && functionType != expressionType) {
            BReport::getInstance().error()
                    << "Function " << function->getName()->getValue() << " is of type " << functionType
                    << " but return expression is of type " << expressionType << std::endl;
            BReport::getInstance().printError();
        }
    } else {
        BReport::getInstance().error()
                << "Function " << function->getName()->getValue()
                << " does not expect to return an expression" << std::endl;
        BReport::getInstance().printError();
    }
}
