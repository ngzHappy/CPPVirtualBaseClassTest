
#ifndef PRAGMA_IN_CPP_FILE_ONCE_VIRTUAL_CLASS_
#define PRAGMA_IN_CPP_FILE_ONCE_VIRTUAL_CLASS_

/*
此文件只能被cpp文件包含
此文件必须被最后包含
此文件在不同cpp文件中编译结果不同
*/

#include "VirtualClass.hpp"

namespace {
/*强制编译器为每一个cpp文件生成不同的函数*/

namespace __VirtualClass_ {
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

}/*~__VirtualClass_*/

template<typename Type>
Type _cppfile_VirtualClass_getData(const VirtualClass * arg) {
    switch (arg->type()) {
        case VirtualClass::Type::IndexVoid:return nullptr; break;
        case VirtualClass::Type::IndexConstVoid:return nullptr; break;

        case VirtualClass::Type::Index_XXX_QObject:return __VirtualClass_::quickCast<Type>(reinterpret_cast<xxx::QObject*>(arg->data())); break;
        case VirtualClass::Type::IndexConst_XXX_QObject:return __VirtualClass_::quickCast<Type>(reinterpret_cast<const xxx::QObject*>(arg->data())); break;

        case VirtualClass::Type::Index_JJJ_xxxxd:return __VirtualClass_::quickCast<Type>(reinterpret_cast<jjj::xxxxd*>(arg->data())); break;
        case VirtualClass::Type::IndexConst_JJJ_xxxxd:return __VirtualClass_::quickCast<Type>(reinterpret_cast<const jjj::xxxxd*>(arg->data())); break;


        default:return nullptr; break;
    }
}
}/*~namespace*/

template<typename Type>
Type VirtualClass::getData() const {
    static_assert(std::is_pointer<Type>::value,"Type must be pointer");
    if (_data_void_==nullptr) { return nullptr; }
    return _cppfile_VirtualClass_getData<Type>(this);
}


#endif

