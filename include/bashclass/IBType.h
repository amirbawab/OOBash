#ifndef BASHCLASS_IBTYPE_H
#define BASHCLASS_IBTYPE_H

#include <string>
#include <memory>
#include <bashclass/BClass.h>

class IBType {
private:

    // Values defining the built-in types names. For example:
    // var [int] a;
    // lexicalToken->getName()
    static const std::string TYPE_NAME_INT;
    static const std::string TYPE_NAME_CHAR;
    static const std::string TYPE_NAME_BOOLEAN;
    static const std::string TYPE_NAME_STRING;
    static const std::string TYPE_NAME_ANY;
    static const std::string TYPE_NAME_VOID;
    static const std::string TYPE_NAME_IDENTIFIER;

    // Values defining the built-in types values. For example:
    // var [int] a;
    // lexicalToken->getValue()
    static const std::string TYPE_VALUE_INT;
    static const std::string TYPE_VALUE_CHAR;
    static const std::string TYPE_VALUE_BOOLEAN;
    static const std::string TYPE_VALUE_STRING;
    static const std::string TYPE_VALUE_ANY;
    static const std::string TYPE_VALUE_VOID;

    // Undefined type is used by the compiler when an expression has an unknown type
    // e.g. Divide a string by another
    // When "undefined" is used by the user as input, it will behave as an alias
    // to "null"
    // "undefined" must be a reserved word to avoid a user defined class called
    // undefined
    static const std::string UNDEFINED;

    // Null is used to unlink a reference of an object
    static const std::string NULL_VALUE;

    // Those values represent the type name of data
    // a = [1234];
    // lexicalToken->getName()
    static const std::string DATA_TYPE_NAME_INT;
    static const std::string DATA_TYPE_NAME_STRING;
    static const std::string DATA_TYPE_NAME_CHAR;
    static const std::string DATA_TYPE_NAME_BOOLEAN;
    static const std::string DATA_TYPE_NAME_BASH_SUB;
    static const std::string DATA_TYPE_NAME_BASH_INLINE;
    static const std::string DATA_TYPE_NAME_BASH_BLOCK;

protected:

    // Hold type scope
    std::shared_ptr<BClass> m_typeScope;
public:

    /**
     * Get type name
     * @return type name
     */
    virtual std::string getTypeName()=0;

    /**
     * Get type value
     * @return type value
     */
    virtual std::string getTypeValue()=0;

    /**
     * Get type scope
     * @return type scope
     */
    std::shared_ptr<BClass> getTypeScope() {return m_typeScope;}

    /**
     * Int check
     * @return boolean
     */
    bool isInt() { return getTypeName() == IBType::TYPE_NAME_INT;};

    /**
     * String check
     * @return boolean
     */
    bool isString() { return getTypeName() == IBType::TYPE_NAME_STRING;}

    /**
     * Any check
     * @return boolean
     */
    bool isAny() { return getTypeName() == IBType::TYPE_NAME_ANY;}

    /**
     * Void check
     * @return boolean
     */
    bool isVoid() {return getTypeName() == IBType::TYPE_NAME_VOID;}

    /**
     * Char check
     * @return boolean
     */
    bool isChar() {return getTypeName() == IBType::TYPE_NAME_CHAR;}

    /**
     * Boolean check
     * @return boolean
     */
    bool isBoolean() {return getTypeName() == IBType::TYPE_NAME_BOOLEAN;}

    /**
     * Null check
     * @return boolean
     */
    bool isNull() {return getTypeName() == IBType::NULL_VALUE;}

    /**
     * Undefined check
     * @return boolean
     */
    bool isUndefined() { return getTypeName() == IBType::UNDEFINED;}

    /**
     * Check if the type is built-in
     */
    bool isBuiltInType();
};

#endif