#ifndef LWE_OBJECT_HEADER
#define LWE_OBJECT_HEADER

#include "meta.hpp"

//! @brief
class Object {
    friend struct MetaClass;
    struct ObjectMeta: MetaClass {
        virtual const char*      name() const override { return "Object"; }
        virtual size_t           size() const override { return sizeof(Object); }
        virtual const FieldInfo& fields() const override {
            static const FieldInfo EMPTY; // default
            return EMPTY;
        }
        virtual MetaClass* base() const override { return nullptr; }
    };

public:
    virtual MetaClass* metaclass() const {
        static ObjectMeta meta;
        return &meta;
    }
    virtual MetaClass* metabase() { return nullptr; }

public:
    std::string serialize() const;
    void        deserialize(const std::string& in);
    static void deserialize(Object* out, const std::string& in);
};

#endif