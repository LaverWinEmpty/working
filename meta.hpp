#ifndef LWE_META_HEADER
#define LWE_META_HEADER

#include "hal.hpp"
#include "common.hpp"

/**
 * @brief type codes
 */
enum class EType : uint8 {
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
    ENUM,
    CLASS,
    UNION,
    POINTER,
    REFERENCE,
    FUNCTION,
    STD_STRING,
    STL_DEQUE,
    CONST,
};

/**
 * @brief type info
 */
struct Type {
    template<typename T> static const Type& deserialize();

public:
    Type() = default;
    Type(const Type&);
    Type(Type&&) noexcept;
    Type(EType);
    ~Type();
    Type& operator=(const Type);
    Type& operator=(Type&&) noexcept;

public:
    const EType& operator[](size_t) const;
    const EType* begin() const;
    const EType* end() const;
    size_t       size() const;
    hash_t       hash() const;
    EType        type() const;
    const char*  serialize() const;

public:
    explicit operator string() const;
    operator EType() const;

private:
    static constexpr size_t STACK = (sizeof(size_t) + sizeof(EType*));

private:
    void                             push(EType);
    template<typename T> static void deserialize(Type*);

private:
    hash_t hashed = 0;
    size_t count  = 0;
    union {
        struct {
            EType* heap;
            size_t capacitor;
        };
        EType stack[STACK] = { EType::UNREGISTERED };
    };
};

// clang-format off
template<typename T> constexpr EType typecode(); //!< get type code

constexpr const char*            typestring(EType);      //!< reflect type name string by enum
template<typename T> const char* typestring();            //!< reflect type name string explicit
template<typename T> const char* typestring(const T&);    //!< reflect type name string implicit
const char*                      typestring(const Type&); //!< reflect type name

template<typename T> const Type& typeof();         //!< reflect typeinfo by template
template<typename T> const Type& typeof(const T&); //!< reflect typeinfo by argument
template<typename T> void        typeof(Type*);    //!< pirvate
// clang-format on

struct Variable {
    Type        type;
    const char* name;
    size_t      size;
};

struct Field: Variable {
    size_t offset;
};

struct Enumerator {
    uint64      value;
    const char* name;
};

template<typename T> struct Reflector {
    template<class C> static const Reflector<T>& reflect();

public:
    template<typename C> static const Reflector<T>& find();              //!< get registred C type data
    template<typename C> static const Reflector<T>& find(const C&);      //!< get registred C type data
    static const Reflector<T>&                      find(const char*);   //!< get registred C type data by name c string
    static const Reflector<T>&                      find(const string&); //!< get registred C type data by name string

public:
    Reflector() = default;
    Reflector(const Reflector&);
    Reflector(Reflector&&) noexcept;
    Reflector(const std::initializer_list<T>&);
    ~Reflector();

public:
    Reflector& operator=(const Reflector);
    Reflector& operator=(Reflector&&) noexcept;

public:
    const T& operator[](size_t) const;

public:
    const T* begin() const;
    const T* end() const;
    size_t   size() const;

private:
    template<typename Arg> void push(Arg&&);
    void                        shrink();

private:
    T*     data      = nullptr;
    size_t capacitor = 0;
    size_t count     = 0;

private:
    inline static std::unordered_map<string, Reflector<T>> map;
};

using Enumerate = Reflector<Enumerator>;
using Structure = Reflector<Field>;

enum class Registered : bool {
    REGISTERED = 1
};

struct Class {
    friend class Object;
    template<typename T> friend Registered registclass();
    friend Class*                          metaclass(const string&);

public:
    virtual const char*      name() const   = 0;
    virtual size_t           size() const   = 0;
    virtual const Structure& fields() const = 0;
    virtual const Class*     base() const   = 0;
};

struct Enum {
    template<typename T> friend Registered registenum();
    friend Enum*                           metaenum(const string&);

public:
    virtual const char*      name() const  = 0;
    virtual size_t           size() const  = 0;
    virtual const Enumerate& enums() const = 0;

public:
    template<typename E> static const char* stringify(E);
    static const char*                      stringify(const string&, uint64);
    static const char*                      stringify(const char*, uint64);

public:
    template<typename E> static E parse(const char*);
    template<typename E> static E parse(const string&);
    static uint64_t               parse(const string&, const string&);
};

template<typename T> class Registry {
public:
    using Map = std::unordered_map<string, T*>;

public:
    template<typename U> static void add(const string&);
    template<typename U> static void add(const char*);

public:
    static T* find(const char*);
    static T* find(const string&);

private:
    Registry() = default;

public:
    ~Registry();

private:
    Map map;

private:
    static Map& instance();
};

template<typename T> Registered registclass();
template<typename T> Registered registenum();

template<typename T> const Object* statics();
template<typename T> const Object* statics(const T&);
const Object*                      statics(const char*);
const Object*                      statics(const string&);

template<typename T> Class* metaclass();
template<typename T> Class* metaclass(const T&);
Class*                      metaclass(const char*);
Class*                      metaclass(const string&);

template<typename T> Enum* metaenum();
template<typename T> Enum* metaenum(const T&);
Enum*                      metaenum(const char*);
Enum*                      metaenum(const string&);

template<> struct std::hash<Type> {
    size_t operator()(const Type& obj) const { return obj.hash(); }
};

#endif