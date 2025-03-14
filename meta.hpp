#ifndef LWE_META_HEADER
#define LWE_META_HEADER

#include "enum.hpp"
#include "container.hpp"

/**************************************************************************************************
 * Meta~
 * - type_t      | type name to enum
 * - access_t    | access modifier to enum
 * - MetaField     | field information struct
 * - MetaMethod    | method information struct
 * - MetaClass     | class information struct
 * - MetaContainer | container information getter struct
 *
 * functions
 * - typecode   | get type enum
 * - typeinfo   | get type information vector
 * - typestring | get type name string
 **************************************************************************************************/

// clang-format off

enum class EType : int8 {
    UNREGISTERED,
    VOID,
    SIGNED_INT,
    SIGNED_CHAR,
    SIGNED_SHORT,
    SIGNED_LONG,
    SIGNED_LONG_LONG,
    UNSIGNED_SHORT,
    UNSIGNED_INT,
    UNSIGNED_CHAR,
    UNSIGNED_LONG,
    UNSIGNED_LONG_LONG,
    BOOL,
    CHAR,
    WCHAR_T,
    FLOAT,
    DOUBLE,
    LONG_DOUBLE,
    CLASS,
    UNION,
    POINTER,
    REFERENCE,
    FUNCTION,
    STD_STRING,
    STL_DEQUE,
};

enum class EAccess : int8 {
    PRIVATE,
    PROTECTED,
    PUBLIC,
    NONE,
};

// get container type code structur
template<typename, typename = std::void_t<>> struct ContainerCode {
    static constexpr EType VALUE = EType::UNREGISTERED;
};

/**
 * @brief type code: primitive type has 1 element, but pointer, reference, template, etc has more elements
 */
struct Type {
private:
    static constexpr size_t STACK = (sizeof(size_t) + sizeof(EType*));
    void                    push(EType in);

public:
    template<typename T> static void make(Type* out);

public:
    Type() = default;
    Type(const Type&);
    Type(Type&&) noexcept;
    ~Type();
    Type& operator=(const Type);
    Type& operator=(Type&&) noexcept;
    
public:
    const EType& operator[](size_t) const;
    const EType* begin() const;
    const EType* end() const;
    size_t        size() const;
    hash_t        hash() const;
    EType        type() const;
    const char*   stringify() const;

public:
    explicit operator string() const;
    operator EType() const;

private:
    size_t count = 0;
    union {
        struct {
            EType* heap;
            size_t capacitor;
        };
        EType stack[STACK] = { EType::UNREGISTERED };
    };
};

template<> struct std::hash<Type> {
    size_t operator()(const Type& obj) const {
        return obj.hash();
    } 
};

template<typename T> constexpr EType typecode();                     //!< get type enum value
template<> constexpr           EType typecode<void>();               //!< get type enum value
template<> constexpr           EType typecode<signed int>();         //!< get type enum value
template<> constexpr           EType typecode<signed char>();        //!< get type enum value
template<> constexpr           EType typecode<signed short>();       //!< get type enum value
template<> constexpr           EType typecode<signed long>();        //!< get type enum value
template<> constexpr           EType typecode<signed long long>();   //!< get type enum value
template<> constexpr           EType typecode<unsigned int>();       //!< get type enum value
template<> constexpr           EType typecode<unsigned char>();      //!< get type enum value
template<> constexpr           EType typecode<unsigned short>();     //!< get type enum value
template<> constexpr           EType typecode<unsigned long>();      //!< get type enum value
template<> constexpr           EType typecode<unsigned long long>(); //!< get type enum value
template<> constexpr           EType typecode<bool>();               //!< get type enum value
template<> constexpr           EType typecode<char>();               //!< get type enum value
template<> constexpr           EType typecode<wchar_t>();            //!< get type enum value
template<> constexpr           EType typecode<float>();              //!< get type enum value
template<> constexpr           EType typecode<double>();             //!< get type enum value
template<> constexpr           EType typecode<long double>();        //!< get type enum value
template<> constexpr           EType typecode<string>();             //!< get type enum value

constexpr const char*            typestring(EType);      //!< get type name string by enum
template<typename T> const char* typestring();            //!< get type name string explicit
template<typename T> const char* typestring(const T&);    //!< get type name string implicit
const char*                      typestring(const Type&); //!< get type name

template<typename T> const Type& typeof();          //!< get typeinfo by template
template<typename T> const Type& typeof(const T&);  //!< get typeinfo by argument
template<typename T> void        typeof(Type*);     //!< pirvate

/*
 * @breif metadata field
 */
struct MetaField {
    EAccess     level;  //!< NONE: exception
    Type        type;   //!< [0] is type: other is template parameters, [0] is pointer, reference count
    const char* name;   //!< vairable name
    size_t      size;   //!< variable size
    size_t      offset; //!< variable offset
};

// TODO:
/*
 * @breif metadata method
 */
struct MetaMethod {
    EAccess level;
    EType   result;
    Type   parameters;
};

/**
 * @brief member variable list
 */
using FieldInfo = std::vector<MetaField>;

/**
 * @brief member function list
 */
using MethodInfo = std::vector<MetaMethod>;

/*
 * @breif metadata class base
 */
struct MetaClass {
public:
    template<typename T> static MetaClass* get() {
        return nullptr;
    }
    template<typename T> static MetaClass* get(const T&) {
        return nullptr;
    }

public:
    virtual const char*      name() const       = 0;
    virtual size_t           size() const       = 0;
    virtual const FieldInfo& field() const = 0;
    virtual MetaClass*       base() const       = 0;
};

template<typename T> constexpr bool isSTL();                    //!< check container explicit
template<typename T> constexpr bool isSTL(const T&);            //!< check container implicit
template<> bool                     isSTL<EType>(const EType&); //!< check container type code

// clang-format on
#include "meta.ipp"
#endif