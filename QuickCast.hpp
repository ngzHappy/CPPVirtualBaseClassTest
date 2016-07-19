#if !defined(__PRAGMA_ONCE_QUICK_CAST_0_)
#define __PRAGMA_ONCE_QUICK_CAST_0_

#include <utility>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace __private {
class __QuickCast {
protected:
    /*测试是否可以执行static_cast*/
    class can_not_static_cast final { public:can_not_static_cast(decltype(nullptr)) {} };
    class can_static_cast final {};

    template<typename ...>
    static can_not_static_cast test_is_static_cast(...) { return nullptr; }

    template<typename ToType_,typename FromType_>
    static auto test_is_static_cast(FromType_ arg)->decltype((static_cast<ToType_>(arg),can_static_cast{})) {
        return (static_cast<ToType_>(arg),can_static_cast{});
    }
    /*测试是否可以执行dynamic_cast*/
    class can_not_dynamic_cast final { public:can_not_dynamic_cast(decltype(nullptr)) {} };
    class can_dynamic_cast final {};

    template<typename ...>
    static can_not_dynamic_cast test_is_dynamic_cast(...) { return nullptr; }

    template<typename ToType_,typename FromType_>
    static auto test_is_dynamic_cast(FromType_ arg)->decltype((dynamic_cast<ToType_>(arg),can_dynamic_cast{})) {
        return (dynamic_cast<ToType_>(arg),can_dynamic_cast{});
    }
};
}/*~__private*/

/*static_cast or dynamic_cast*/
template<typename TypeFrom,typename TypeTo>
class QuickCast final :private __private::__QuickCast {
private:
    /*can not create*/
    ~QuickCast()=delete;
    QuickCast()=delete;

    /*test ans*/
    using test_static_cast_ans=
        decltype(test_is_static_cast<TypeTo,TypeFrom>(std::declval<TypeFrom>()));
    using test_dynamic_cast_ans=
        decltype(test_is_dynamic_cast<TypeTo,TypeFrom>(std::declval<TypeFrom>()));

    /*static_cast*/
    template<
        typename TypeNotUse,
        typename=std::remove_reference_t<test_static_cast_ans>,
        typename=std::remove_reference_t<test_dynamic_cast_ans>
    >class Cast
        final :public std::true_type {
    public:
        static TypeTo cast(TypeFrom arg) { return static_cast<TypeTo>(arg); }
    };

    /*can not cast*/
    template<typename TypeNotUse>
    class Cast<TypeNotUse,can_not_static_cast,can_not_dynamic_cast>
        final :public std::false_type {
    public:
        static TypeTo cast(TypeFrom) { return nullptr; }
    };

    /*dynamic_cast*/
    template<typename TypeNotUse>
    class Cast <TypeNotUse,can_not_static_cast,can_dynamic_cast>
        final :public std::false_type {
    public:
        static TypeTo cast(TypeFrom arg) { return dynamic_cast<TypeTo>(arg); }
    };

    using cast_type=Cast<void>;
    using type=cast_type;
public:
    using from_type=TypeFrom;
    using to_type=TypeTo;
    constexpr static bool value=cast_type::value/*is static cast*/;
    static TypeTo cast(TypeFrom arg) { return type::cast(arg); }
};

/*static_cast or dynamic_cast*/
template<typename TypeTo_,typename TypeFrom_>
inline TypeTo_ quickCast(TypeFrom_ && arg) {
    return QuickCast<TypeFrom_,TypeTo_>::cast(std::forward<TypeFrom_>(arg));
}

/*static_cast or dynamic_cast*/
template<typename TypeTo_,typename TypeFrom_>
inline TypeTo_ quickCast(TypeFrom_ * arg) {
    static_assert(std::is_pointer<TypeTo_>::value,"TypeTo_ must be pointer");
    return QuickCast<TypeFrom_ *,TypeTo_>::cast(arg);
}

#endif/*~__PRAGMA_ONCE_QUICK_CAST_0_*/

