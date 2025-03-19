#ifndef LWE_INLINE_HEADER
#define LWE_INLINE_HEADER
#include "meta.ipp"
#include "serialize.ipp"
#include "object.ipp"
#include "container.ipp"

REGISTER_ENUM_BEGIN(EType) {
    REGISTER_ENUM(UNREGISTERED);
    REGISTER_ENUM(VOID);
    REGISTER_ENUM(SIGNED_INT);
    REGISTER_ENUM(SIGNED_CHAR);
    REGISTER_ENUM(SIGNED_SHORT);
    REGISTER_ENUM(SIGNED_LONG);
    REGISTER_ENUM(SIGNED_LONG_LONG);
    REGISTER_ENUM(UNSIGNED_SHORT);
    REGISTER_ENUM(UNSIGNED_INT);
    REGISTER_ENUM(UNSIGNED_CHAR);
    REGISTER_ENUM(UNSIGNED_LONG);
    REGISTER_ENUM(UNSIGNED_LONG_LONG);
    REGISTER_ENUM(BOOL);
    REGISTER_ENUM(CHAR);
    REGISTER_ENUM(WCHAR_T);
    REGISTER_ENUM(FLOAT);
    REGISTER_ENUM(DOUBLE);
    REGISTER_ENUM(LONG_DOUBLE);
    REGISTER_ENUM(ENUM);
    REGISTER_ENUM(CLASS);
    REGISTER_ENUM(UNION);
    REGISTER_ENUM(POINTER);
    REGISTER_ENUM(REFERENCE);
    REGISTER_ENUM(FUNCTION);
    REGISTER_ENUM(STD_STRING);
    REGISTER_ENUM(STL_DEQUE);
    REGISTER_ENUM(CONST);
}
REGISTER_ENUM_END;

#endif