#ifndef LWE_OBJECT_HEADER
#define LWE_OBJECT_HEADER

#include "meta.hpp"

//! @brief
class Object {
    template<typename T> friend Registered registclass();
    friend const Object*                   statics(const string&);

public:
    virtual Class* meta() const;

public:
    std::string serialize() const;
    void        deserialize(const std::string& in);
    static void deserialize(Object* out, const std::string& in);

private:
    inline static std::unordered_map<string, const Object*> Map;
};

struct ObjectMeta: Class {
    virtual const char*      name() const override;
    virtual size_t           size() const override;
    virtual const Structure& fields() const override;
    virtual Class*           base() const override;
};

#endif