#ifdef LWE_UTIL_HASH

LWE_BEGIN
namespace util {

struct Hash::String {
    String(const Hash* in) {
        // to stirng, without null (fixed size)
        snprintf(buffer, 16, "%016llX", in->val);
        buffer[16] = 0;
    }
    operator string() { return buffer; }
    operator const char* () { return buffer; }
private:
    char buffer[17];
};

Hash::Hash(const void* in, size_t n): val(FNV1A64_BASIS) {
    const unsigned char* ptr = static_cast<const unsigned char*>(in);
    for (size_t i = 0; i < n; i++) {
        val ^= ptr[i];
        val *= FNV1A64_PRIME;
    }
}

Hash::Hash(const string& in): Hash(in.c_str(), in.size()) {}

bool Hash::operator==(const Hash& in) const {
    return val == in.val;
}

bool Hash::operator!=(const Hash& in) const {
    return val != in.val;
}

Hash::Hash(const char* in) : Hash(in, std::strlen(in)) {}

template<typename T> Hash::Hash(const T& in): Hash(&in, sizeof(T)) {}

Hash::operator string () const {
    return operator*();
}

auto Hash::operator*() const -> String {
    return String(this);
}

Hash::operator hash_t() const {
    return val;
}

}
LWE_END
#endif