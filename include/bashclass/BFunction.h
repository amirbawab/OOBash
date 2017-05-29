#ifndef BASHCLASS_BFUNCTION_H
#define BASHCLASS_BFUNCTION_H

#include <vector>
#include <memory>
#include <bashclass/BScope.h>
#include <bashclass/IBCallable.h>

class BFunction : public BScope {
private:
    std::shared_ptr<ecc::LexicalToken> m_name;
    std::shared_ptr<ecc::LexicalToken> m_type;
    std::shared_ptr<BScope> m_typeScope;
    std::shared_ptr<IBCallable> m_returnExpression;
    bool m_knownType = false;
public:

    /**
     * Get function name token
     * @return name
     */
    std::shared_ptr<ecc::LexicalToken> getName() const{return m_name;}

    /**
     * Set function name token
     * @param name
     */
    void setName(std::shared_ptr<ecc::LexicalToken> name) { m_name = name;}

    /**
     * Get function type token
     * @return type
     */
    std::shared_ptr<ecc::LexicalToken> getType() const {return m_type; }

    /**
     * Set function type token
     * @param type
     */
    void setType(std::shared_ptr<ecc::LexicalToken> type) { m_type = type;}

    /**
     * Get variable type scope
     * @return type
     */
    std::shared_ptr<BScope> getTypeScope() const {return m_typeScope;}

    /**
     * Set variable type scope
     * @param type
     */
    void setTypeScope(std::shared_ptr<BScope> scope) {m_typeScope = scope;}

    /**
     * Get type value as a string
     * @return type string
     */
    std::string getTypeValue() const;

    /**
     * Check if this function is a class member
     */
    bool isClassMember();

    /**
     * Get function label
     */
    std::stringstream getLabel();

    /**
     * Set if the function has a known type
     */
    void setKnownType(bool knownType) {m_knownType = knownType;}

    /**
     * Check if the type of the function is known
     */
    bool hasKnowType() const { return m_knownType;}

    /**
     * Set return expression
     * @param returnExpression
     */
    void setReturnExpression(std::shared_ptr<IBCallable> returnExpression) {m_returnExpression = returnExpression;}

    /**
     * Get return expression
     * @return expression
     */
    std::shared_ptr<IBCallable> getExpression() {return m_returnExpression;}
};

#endif
