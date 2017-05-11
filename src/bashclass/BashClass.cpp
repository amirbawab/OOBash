#include <bashclass/BashClass.h>
#include <iostream>

BashClass::BashClass() {
    m_global = std::make_shared<BGlobal>();
    m_scopeStack.push(m_global);
}

void BashClass::initHandlers() {
    m_startClass = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE) {
            auto newClass = m_global->createClass();
            m_scopeStack.push(newClass);
        }
    };

    m_className = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE) {
            auto createdClass = std::dynamic_pointer_cast<BClass>(m_scopeStack.top());
            createdClass->setName(lexicalVector[index]->getValue());
        }
    };

    m_endClass = [&](int phase, LexicalTokens &lexicalVector, int index, bool stable){
        if(phase == BashClass::PHASE_CREATE) {
            m_scopeStack.pop();
        }
    };
}
