#include <bashclass/BashClass.h>
#include <iostream>
#include <sstream>

BashClass::BashClass() {
    m_global = std::make_shared<BGlobal>();
    m_scopeStack.push(m_global);
    m_focusScope = nullptr;
    m_focusVariable = nullptr;
    initHandlers();
}

void BashClass::printStructure() {
    std::cout << m_global->getStructure().str() << std::endl;
}

void BashClass::initHandlers() {

    /**************************************
     *          CLASSES
     **************************************/
    m_startClass = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE) {
            auto newClass = m_scopeStack.top()->createClass(lexicalVector[index]);
            m_scopeStack.push(newClass);
            m_focusScope = newClass;
        } else if(phase == BashClass::PHASE_EVAL_GEN) {
            auto newClass = m_scopeStack.top()->getScope(lexicalVector[index]);
            m_scopeStack.push(newClass);
            m_focusScope = newClass;
        }
    };

    m_className = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE) {

            // Check if class already exists
            const char* className = lexicalVector[index]->getValue().c_str();
            auto getClass = m_scopeStack.top()->getParentScope()->findAllClasses(className);
            if(!getClass.empty()) {
                std::cerr << "Class '" << className << "' is defined multiple times" << std::endl;
            }

            // Set class name
            auto createdClass = std::dynamic_pointer_cast<BClass>(m_focusScope);
            createdClass->setName(lexicalVector[index]->getValue());
        }
    };

    m_endClass = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE || phase == BashClass::PHASE_EVAL_GEN) {
            m_scopeStack.pop();
            m_focusScope = nullptr;
        }
    };

    /**************************************
     *          FUNCTIONS
     **************************************/
    m_startFunction = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE) {
            auto newFunction = m_scopeStack.top()->createFunction(lexicalVector[index]);
            m_scopeStack.push(newFunction);
            m_focusScope = newFunction;
        } else if(phase == BashClass::PHASE_EVAL_GEN) {
            auto newFunction = m_scopeStack.top()->getScope(lexicalVector[index]);
            m_scopeStack.push(newFunction);
            m_focusScope = newFunction;
        }
    };

    m_functionType = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE) {
            auto createdFunction = std::dynamic_pointer_cast<BFunction>(m_focusScope);
            createdFunction->setType(lexicalVector[index]->getValue());
        }
    };

    m_functionName = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE) {

            // Check if function already exists in the current scope and has the same number of params
            const char* funcName = lexicalVector[index]->getValue().c_str();
            auto getFunc = m_scopeStack.top()->getParentScope()->findAllFunctions(funcName);
            if(!getFunc.empty()) {
                std::cerr << "Function '" << funcName << "' is defined multiple times in the same scope" << std::endl;
            }

            auto createdFunction = std::dynamic_pointer_cast<BFunction>(m_focusScope);
            createdFunction->setName(lexicalVector[index]->getValue());
        }
    };

    m_endFunction = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE || phase == BashClass::PHASE_EVAL_GEN) {
            m_scopeStack.pop();
            m_focusScope = nullptr;
        }
    };

    /**************************************
     *          VARIABLES
     **************************************/
    m_startVar = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE) {
            auto variable = m_scopeStack.top()->createVariable(lexicalVector[index]);
            m_focusVariable = variable;
        }
    };

    m_varType = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE) {
            m_focusVariable->setType(lexicalVector[index]->getValue());
        }
    };

    m_varName = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE) {

            // Check if variable already exists in the current scope
            const char* varName = lexicalVector[index]->getValue().c_str();
            auto getVar = m_scopeStack.top()->findAllVariables(varName);
            if(!getVar.empty()) {
                std::cerr << "Variable '" << varName << "' is defined multiple times in the same scope" << std::endl;
            }

            m_focusVariable->setName(lexicalVector[index]->getValue());
        }
    };

    m_endVar = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE) {
            m_focusVariable = nullptr;
        }
    };


    /**************************************
     *          PARAMETERS
     **************************************/
    m_startParam = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE) {
            auto createdVar = m_scopeStack.top()->createVariable(lexicalVector[index]);
            createdVar->setIsParam(true);
        }
    };

    m_paramType = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE) {
            const auto &variables = m_scopeStack.top()->findAllVariables();
            variables[variables.size()-1]->setType(lexicalVector[index]->getValue());
        }
    };

    m_paramName = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE) {
            const auto &variables = m_scopeStack.top()->findAllVariables();
            variables[variables.size()-1]->setName(lexicalVector[index]->getValue());
        }
    };

    m_endParam = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE) {
            m_focusVariable = nullptr;
        }
    };
}
