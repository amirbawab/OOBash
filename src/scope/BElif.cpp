#include <bashclass/BElif.h>
#include <bashclass/BElementType.h>
#include <iostream>
#include <bashclass/BReport.h>
#include <bashclass/BException.h>

std::stringstream BElif::getLabel() {
    std::stringstream stream = m_parentScope->getLabel();
    stream << "_elif_";
    return stream;
}

void BElif::setExpression(std::shared_ptr<IBExpression> expression) {

    // Store the condition/expression
    m_expression = expression;

    // Verify the type of the expression is boolean
    std::shared_ptr<IBType> expressionType = expression->getType();
    if(expressionType->isUndefined()) {
        BReport::getInstance().error()
                << "Elif statement condition cannot be of undefined type" << std::endl;
        BReport::getInstance().printError();
    } else if(!expressionType->isBoolean()) {
        BReport::getInstance().error()
                << "An elif condition must evaluate to a boolean instead of " << expressionType << std::endl;
        BReport::getInstance().printError();
    }
}