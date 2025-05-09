
#ifndef LWE_MACRO
#define LWE_MACRO

// namespace
#define LWE       lwe
#define LWE_BEGIN namespace LWE {
#define LWE_END   }

#ifndef STRING
#    define STRING(x) #x
#endif

#ifndef MACRO
#    define MACRO(x) STRING(x)
#endif

#define DECLARE_NO_COPY(Class)                                                                                         \
    Class(const Class&)            = delete;                                                                           \
    Class(Class&&)                 = delete;                                                                           \
    Class& operator=(const Class&) = delete;                                                                           \
    Class& operator=(Class&&)      = delete

#define DECLARE_STATIC_CLASS(Class)                                                                                    \
    Class()  = delete;                                                                                                 \
    ~Class() = delete;                                                                                                 \
    DECLARE_NO_COPY(Class)

#define ERROR_STRING(x)                                                                                                \
    std::string() + "File: " + __FILE__ + "\nLine: " + MACRO(__LINE__) + "\nFunction: " + __func__ + "\nFailed: " + #x

#ifndef ASSERT
#    ifdef NDEBUG
#        define ASSERT(x)                                                                                              \
            do {                                                                                                       \
            } while(false)
#    else
#        define ASSERT(x)                                                                                              \
            do {                                                                                                       \
                if(!(x)) {                                                                                             \
                    ERROR_PRINT(ERROR_STRING(x));                                                                      \
                    std::terminate();                                                                                  \
                }                                                                                                      \
            } while(false)
#    endif
#endif

#ifdef _MSC_VER
#    define UNINIT_BEGIN __pragma(warning(disable : 26495))
#    define UNINIT_END   __pragma(warning(default : 26495))
#elif(defined(__GNUC__) || defined(__clang__))
#    define UNINIT_BEGIN _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
#    define UNINIT_END   _Pragma("GCC diagnostic pop")
#else
#    define UNINIT_BEGIN
#    define UNINIT_END
#endif

#ifndef _T
#    ifdef UNICODE
#        define _T(x) L##x
#    else
#        define _T(x) x
#    endif
#endif

#ifndef TEXT
#    define TEXT _T
#endif

#ifndef PROP
#    define PROP(...) __declspec(property(__VA_ARGS__))
#endif

#define LWE_API __declspec(dllexport)

#define LWE_NODISCARD [[nodiscard]]

#ifndef NDEBUG
#    ifndef DEBUG
#        define DEBUG
#    endif
#endif

#ifndef __cplusplus
#    ifdef _MSC_VER
#        define __cplusplus 199711L
#    endif
#endif

#define CPP98 1998
#define CPP03 2003
#define CPP11 2011
#define CPP14 2014
#define CPP17 2017
#define CPP20 2020
#define CPP23 2023

#ifndef CPP_VERSION
#    if __cplusplus >= 202302L
#        define CPP_VERSION CPP23
#    elif __cplusplus >= 202002L
#        define CPP_VERSION CPP20
#    elif __cplusplus >= 201703L
#        define CPP_VERSION CPP17
#    elif __cplusplus >= 201402L
#        define CPP_VERSION CPP14
#    elif __cplusplus >= 201103L
#        define CPP_VERSION CPP11
#    elif __cplusplus >= 199711L
#        define CPP_VERSION CPP03
#    else
#        define CPP_VERSION 0
#    endif
#endif

#if defined(_MSC_VER)
#    define ALLOC_API __declspec(allocator)
#elif defined(__clang__) || defined(__GNUC__)
#    define ALLOC_API __attribute__((malloc))
#else
#    define ALLOC_API
#endif

// use #prgma MESSAGE
#define MESSAGE(x) message(__FILE__ " [" MACRO(__LINE__) "] " #x)

#define LOCKGUARD(lock) if(std::lock_guard<decltype(lock)> MACRO_lock_guard(lock); true)

// clang-format off

#define GET_MACRO_1(a, NAME, ...) NAME                         //! for macro overloading, param count 0 ~ 1
#define GET_MACRO_2(a, b, NAME, ...) NAME                      //! for macro overloading, param count 0 ~ 2
#define GET_MACRO_3(a, b, c, NAME, ...) NAME                   //! for macro overloading, param count 0 ~ 3
#define GET_MACRO_4(a, b, c, d, NAME, ...) NAME                //! for macro overloading, param count 0 ~ 4
#define GET_MACRO_5(a, b, c, d, e, NAME, ...) NAME             //! for macro overloading, param count 0 ~ 5
#define GET_MACRO_6(a, b, c, d, e, f, NAME, ...) NAME          //! for macro overloading, param count 0 ~ 6
#define GET_MACRO_7(a, b, c, d, e, f, g, NAME, ...) NAME       //! for macro overloading, param count 0 ~ 7
#define GET_MACRO_8(a, b, c, d, e, f, g, h, NAME, ...) NAME    //! for macro overloading, param count 0 ~ 8
#define GET_MACRO_9(a, b, c, d, e, f, g, h, i, NAME, ...) NAME //! for macro overloading, param count 0 ~ 9

/*
 * @brief register metadata inner class
 */
#define CLASS_BODY(TYPE, BASE)                                                                                         \
public:                                                                                                                \
	friend lwe::meta::Structure;                                                                                       \
    friend struct TYPE##Meta;                                                                                          \
    virtual LWE::meta::Class* meta() const override;                                                                   \
    using Base = BASE

#define REGISTER_FIELD_BEGIN(...) GET_MACRO_2(__VA_ARGS__,\
        Macro__register_field_begin_scoped,\
        Macro__register_field_begin_global \
    )(__VA_ARGS__)
#define Macro__register_field_begin_global(TYPE)         Macro__register_field_begin_implementation(TYPE, )
#define Macro__register_field_begin_scoped(TYPE, SCOPE ) Macro__register_field_begin_implementation(TYPE, SCOPE::)
#define Macro__register_field_begin_implementation(TYPE, SCOPE)                                                        \
    template<> LWE::meta::Class* LWE::meta::classof<SCOPE TYPE>() {                                                    \
        static LWE::meta::Class* META = nullptr;                                                                       \
        if(!META) META = LWE::meta::Registry<LWE::meta::Class>::find(#TYPE);                                           \
        return META;                                                                                                   \
    }                                                                                                                  \
    template<> LWE::meta::Object* LWE::meta::statics<SCOPE TYPE>() {                                                   \
        static LWE::meta::Object* OBJ = nullptr;                                                                       \
        if(!OBJ) OBJ = LWE::meta::Registry<LWE::meta::Object>::find(#TYPE);                                            \
        return OBJ;                                                                                                    \
    }                                                                                                                  \
    struct TYPE##Meta: LWE::meta::Class {                                                                              \
        virtual const char* name() const override {                                                                    \
            return #TYPE;                                                                                              \
        }                                                                                                              \
        virtual size_t size() const override {                                                                         \
            return sizeof(SCOPE TYPE);                                                                                 \
        }                                                                                                              \
        virtual LWE::meta::Class* base() const override {                                                              \
            return LWE::meta::classof<SCOPE TYPE::Base>();                                                             \
        }                                                                                                              \
        virtual LWE::meta::Object* statics() const override {                                                          \
            return LWE::meta::statics<SCOPE TYPE>();                                                                   \
        }                                                                                                              \
        virtual const LWE::meta::Structure& fields() const override;                                                   \
    };                                                                                                                 \
    LWE::meta::Class* SCOPE TYPE::meta() const {                                                                       \
        return LWE::meta::classof<TYPE>();                                                                             \
    }                                                                                                                  \
    template<> template<> const LWE::meta::Structure& LWE::meta::Structure::reflect<SCOPE TYPE>();                     \
    template<> LWE::meta::Registered LWE::meta::registclass<SCOPE TYPE>() {                                            \
        LWE::meta::Structure::reflect<SCOPE TYPE>();                                                                   \
        LWE::meta::Registry<LWE::meta::Object>::add<SCOPE TYPE>(#TYPE);                                                \
        LWE::meta::Registry<LWE::meta::Class>::add<TYPE##Meta>(#TYPE);                                                 \
        return LWE::meta::Registered::REGISTERED;                                                                      \
    }                                                                                                                  \
    LWE::meta::Registered TYPE##_RGISTERED = LWE::meta::registclass<SCOPE TYPE>();                                     \
    const LWE::meta::Structure& TYPE##Meta::fields() const {                                                           \
        static const LWE::meta::Structure& REF = LWE::meta::Structure::reflect<SCOPE TYPE>();                          \
        return REF;                                                                                                    \
    }                                                                                                                  \
    template<> template<> const LWE::meta::Structure& LWE::meta::Structure::reflect<SCOPE TYPE>() {                    \
        using CLASS = SCOPE TYPE;                                                                                      \
        const char* NAME = #TYPE;                                                                                      \
        auto result = map.find(NAME);                                                                                  \
        if (result != map.end()) {                                                                                     \
        	return result->second;                                                                                     \
        }                                                                                                              \
        LWE::meta::Structure meta; // {
#define REGISTER_FIELD(FIELD)                                                                                          \
        meta.push(                                                                                                     \
                LWE::meta::Field {                                                                                     \
                    typeof<decltype(CLASS::FIELD)>(),                                                                  \
                    #FIELD,                                                                                            \
                    sizeof(CLASS::FIELD),                                                                              \
                    offsetof(CLASS, FIELD)                                                                             \
                }                                                                                                      \
            ) // }
#define REGISTER_FIELD_END                                                                                             \
        meta.shrink();                                                                                                 \
        map.insert({ NAME, meta });                                                                                    \
        return map[NAME];                                                                                              \
    }

#define REGISTER_ENUM_BEGIN(...) GET_MACRO_2(__VA_ARGS__,\
        Macro__register_enum_begin_scoped,\
        Macro__register_enum_begin_global \
    )(__VA_ARGS__)
#define Macro__register_enum_begin_global(TYPE)        Macro__register_enum_begin_implementation(TYPE, )
#define Macro__register_enum_begin_scoped(TYPE, SCOPE) Macro__register_enum_begin_implementation(TYPE, SCOPE::)
#define Macro__register_enum_begin_implementation(TYPE, SCOPE)                                                         \
    struct TYPE##Meta;                                                                                                 \
    template<> template<> const LWE::meta::Enumerate& LWE::meta::Enumerate::reflect<SCOPE TYPE>();                     \
    struct TYPE##Meta: LWE::meta::Enum {                                                                               \
        virtual const char* name() const {                                                                             \
            return #TYPE;                                                                                              \
        }                                                                                                              \
        virtual size_t size() const {                                                                                  \
            return sizeof(SCOPE TYPE);                                                                                 \
        }                                                                                                              \
        virtual const LWE::meta::Enumerate& enums() const {                                                            \
            static const LWE::meta::Enumerate& REF = LWE::meta::Enumerate::reflect<SCOPE TYPE>();                      \
            return REF;                                                                                                \
        }                                                                                                              \
    };                                                                                                                 \
    template<> LWE::meta::Enum* LWE::meta::enumof<SCOPE TYPE>() {                                                      \
        static LWE::meta::Enum* ENUM = nullptr;                                                                        \
        if(!ENUM) ENUM = LWE::meta::Registry<Enum>::find(#TYPE);                                                       \
        return ENUM;                                                                                                   \
    }                                                                                                                  \
    template<> LWE::meta::Registered LWE::meta::registenum<SCOPE TYPE>() {                                             \
        LWE::meta::Enumerate::reflect<SCOPE TYPE>();                                                                   \
        LWE::meta::Registry<Enum>::add<TYPE##Meta>(#TYPE);                                                             \
        return LWE::meta::Registered::REGISTERED;                                                                      \
    }                                                                                                                  \
    LWE::meta::Registered TYPE##_REGISTERED = LWE::meta::registenum<SCOPE TYPE>();                                     \
    template<> template<> const LWE::meta::Enumerate& LWE::meta::Enumerate::reflect<SCOPE TYPE>() {                    \
        using enum SCOPE TYPE;                                                                                         \
        const char* NAME = #TYPE;                                                                                      \
        auto result = map.find(NAME);                                                                                  \
        if (result != map.end()) {                                                                                     \
        	return result->second;                                                                                     \
        }                                                                                                              \
        LWE::meta::Enumerate meta; // {
#define REGISTER_ENUM(VALUE)                                                                                           \
        meta.push(LWE::meta::Enumerator{ static_cast<uint64>(VALUE), #VALUE }) // }
#define REGISTER_ENUM_END                                                                                              \
        meta.shrink();                                                                                                 \
        map.insert({ NAME, meta });                                                                                    \
        return map[NAME];                                                                                              \
    }

/**
 * @brief container enum value register
 */
#define REGISTER_CONTAINER(CONTAINER, ENUM)                                                                            \
    template<typename T> struct LWE::meta::ContainerCode<T, std::void_t<typename T::CONTAINER##Element>> {             \
        using enum meta::EType;                                                                                        \
        static constexpr meta::EType VALUE = ENUM;                                                                     \
    }

/**
 * @brief default container serializer and deserializer override
 */
#define CONTAINER_BODY(CONTAINER, ELEMENT, ...)                                                                        \
public:                                                                                                                \
	friend lwe::meta::Container;                                                                                       \
    using CONTAINER##Element = ELEMENT;                                                                                \
    virtual void parse(const string& in) override {                                                                    \
        *this = Container::parse<CONTAINER<ELEMENT  __VA_OPT__(,) __VA_ARGS__>>(in);                                   \
    }                                                                                                                  \
    virtual std::string stringify() const override {                                                                   \
        return Container::stringify<CONTAINER<ELEMENT __VA_OPT__(,) __VA_ARGS__>>(this);                               \
    }                                                                                                                  \
    using value_type = CONTAINER##Element

// clang-format on

// header guard end
#endif