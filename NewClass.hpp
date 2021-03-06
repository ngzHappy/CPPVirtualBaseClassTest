﻿#ifndef PRAGMA_ONCE_NEW_CLASS_HPP_0_
#define PRAGMA_ONCE_NEW_CLASS_HPP_0_

#include <memory>
#include <utility>
#include <typeinfo>
#include <typeindex>
#include <type_traits>

//namespace cpp_virtual_base {
//template<>
//class LogicalClass<_Type_> {
//public:
//    using type=_Type_;
//};
//}

namespace cpp_virtual_base {

class VirtualClass {
public:
    virtual ~VirtualClass()=default;
    VirtualClass()=default;
    VirtualClass(const VirtualClass&)=default;
    VirtualClass(VirtualClass&&)=default;
    VirtualClass&operator=(const VirtualClass&)=default;
    VirtualClass&operator=(VirtualClass&&)=default;
public:
    virtual std::type_index concept_type_index() const=0;
    VirtualClass * concept_class() { return this; }
    const VirtualClass * concept_class()const { return this; }
};

template<typename _Type_>
class LogicalClass {
public:
    /*using type=_Type_;*/
};

}

#if defined(NDEBUG)

#ifndef check_cpp_virtual_base
#define check_cpp_virtual_base(_x_)
#endif

#else
#include <cassert>

namespace cpp_virtual_base {
namespace __debug {
namespace __private {

class MixCheck {
public:
    template<typename _Type_>
    static void check(_Type_&&_x_) {
        if (_x_) {
            assert(dynamic_cast<const volatile cpp_virtual_base::VirtualClass*>(_x_));
        }
    }
};

class DoNothing {
public:
    template<typename _Type_>
    static void check(_Type_&&) {}
};

}
}
}

template<typename _Type_>
inline void check_cpp_virtual_base(_Type_ &&_x_) {
    using _TYPE_=std::remove_cv_t<
        std::remove_pointer_t<
        std::remove_reference_t<_Type_>>>;

    using _CHECKTYPE_=std::conditional_t<
        (std::has_virtual_destructor<_TYPE_>::value&&!
        (std::is_base_of<cpp_virtual_base::VirtualClass,_TYPE_>::value)),
        cpp_virtual_base::__debug::__private::MixCheck,
        cpp_virtual_base::__debug::__private::DoNothing
    >;

    _CHECKTYPE_::template check(std::forward<_Type_>(_x_));
}

#endif

namespace cpp_virtual_base {

namespace __private {

class DirectDelete {
public:
    template<typename _Type_>
    static void free(_Type_&&arg) {

        using _TYPE_=std::remove_cv_t<
            std::remove_pointer_t<
            std::remove_reference_t<_Type_>>>;

        static_assert(std::has_virtual_destructor<_TYPE_>::value==false,
            "the function just use for not virtual");

        delete arg;
    }
    template<typename _Type_>
    static void free_virtual(_Type_&&arg) {

        using _TYPE_=std::remove_cv_t<
            std::remove_pointer_t<
            std::remove_reference_t<_Type_>>>;

        static_assert(std::has_virtual_destructor<_TYPE_>::value==true,
            "the function just use for virtual");

        delete arg;
    }
};

class DirectNew {
public:
    template<typename _Type_,typename ... _Args_>
    static auto create(_Args_&&...args) {
        static_assert(std::has_virtual_destructor<_Type_>::value==false,
            "the function just use for not virtual");
        return new _Type_(std::forward<_Args_>(args)...);
    }
    template<typename _Type_,typename ... _Args_>
    static auto create_virtual(_Args_&&...args) {
        static_assert(std::has_virtual_destructor<_Type_>::value==true,
            "the function just use for virtual");
        return new _Type_(std::forward<_Args_>(args)...);
    }
};

class MixDelete {
public:
    template<typename _Type_>
    static void free(_Type_&&arg) {
        check_cpp_virtual_base(arg);
        DirectDelete::template free_virtual(std::forward<_Type_>(arg));
    }
};

class DirectMixNew {
public:
    template<typename _Type_,typename ... _Args_>
    static auto create(_Args_&&...args) {
        return DirectNew::template create_virtual<_Type_>(std::forward<_Args_>(args)...);
    }
};

template<
    typename _Type_,
    bool _is_move_construct_/*false*/,
    bool _is_construct_/*false*/>
    class MixType {
    /*remove cv*/
    using _TYPE_=std::remove_cv_t<
        std::remove_reference_t<_Type_>>;
    /*mix type*/
    class _MIXTYPE_ :
        public _TYPE_,
        public cpp_virtual_base::VirtualClass {
    public:
        virtual std::type_index concept_type_index() const override {
            return typeid(typename cpp_virtual_base::LogicalClass<_TYPE_>::type);
        }
        VirtualClass * concept_class() { return cpp_virtual_base::VirtualClass::concept_class(); }
        const VirtualClass * concept_class()const { return cpp_virtual_base::VirtualClass::concept_class(); }
        using _TYPE_::_TYPE_;
        _MIXTYPE_()=default;
    };
    public:
        using type=_MIXTYPE_;
};

template<typename _Type_>
class MixType<_Type_,true,true> {
    /*remove cv*/
    using _TYPE_=std::remove_cv_t<
        std::remove_reference_t<_Type_>>;
    /*mix type*/
    class _MIXTYPE_ :
        public _TYPE_,
        public cpp_virtual_base::VirtualClass {
    public:
        virtual std::type_index concept_type_index() const override {
            return typeid(typename cpp_virtual_base::LogicalClass<_TYPE_>::type);
        }
        VirtualClass * concept_class() { return cpp_virtual_base::VirtualClass::concept_class(); }
        const VirtualClass * concept_class()const { return cpp_virtual_base::VirtualClass::concept_class(); }
        using _TYPE_::_TYPE_;
        _MIXTYPE_()=default;
        _MIXTYPE_(const _TYPE_&arg):_TYPE_(arg) {}
        _MIXTYPE_(_TYPE_&&arg):_TYPE_(std::move(arg)) {}
    };
public:
    using type=_MIXTYPE_;
};

template<typename _Type_>
class MixType<_Type_,true,false> {
    /*remove cv*/
    using _TYPE_=std::remove_cv_t<
        std::remove_reference_t<_Type_>>;
    /*mix type*/
    class _MIXTYPE_ :
        public _TYPE_,
        public cpp_virtual_base::VirtualClass {
    public:
        virtual std::type_index concept_type_index() const override {
            return typeid(typename cpp_virtual_base::LogicalClass<_TYPE_>::type);
        }
        VirtualClass * concept_class() { return cpp_virtual_base::VirtualClass::concept_class(); }
        const VirtualClass * concept_class()const { return cpp_virtual_base::VirtualClass::concept_class(); }
        using _TYPE_::_TYPE_;
        _MIXTYPE_()=default;
        _MIXTYPE_(_TYPE_&&arg):_TYPE_(std::move(arg)) {}
    };
public:
    using type=_MIXTYPE_;
};

template<typename _Type_>
class MixType<_Type_,false,true> {
    /*remove cv*/
    using _TYPE_=std::remove_cv_t<
        std::remove_reference_t<_Type_>>;
    /*mix type*/
    class _MIXTYPE_ :
        public _TYPE_,
        public cpp_virtual_base::VirtualClass {
    public:
        virtual std::type_index concept_type_index() const override {
            return typeid(typename cpp_virtual_base::LogicalClass<_TYPE_>::type);
        }
        VirtualClass * concept_class() { return cpp_virtual_base::VirtualClass::concept_class(); }
        const VirtualClass * concept_class()const { return cpp_virtual_base::VirtualClass::concept_class(); }
        using _TYPE_::_TYPE_;
        _MIXTYPE_()=default;
        _MIXTYPE_(const _TYPE_&arg):_TYPE_(arg) {}
    };
public:
    using type=_MIXTYPE_;
};

template<bool _is_move_construct_=false,bool _is_construct_=false>
class MixNew {
public:
    template<typename _Type_,typename ... _Args_>
    static auto create(_Args_&&...args) {
        using _MIXTYPE_=typename MixType<_Type_,_is_move_construct_,_is_construct_>::type;
        /*create mix type*/
        return DirectNew::template create_virtual<_MIXTYPE_>(std::forward<_Args_>(args)...);
    }
};

template<>
class MixNew<true,true> {
public:
    template<typename _Type_,typename ... _Args_>
    static auto create(_Args_&&...args) {
        using _MIXTYPE_=typename MixType<_Type_,true,true>::type;
        /*create mix type*/
        return DirectNew::template create_virtual<_MIXTYPE_>(std::forward<_Args_>(args)...);
    }
};

template<>
class MixNew<true,false> {
public:
    template<typename _Type_,typename ... _Args_>
    static auto create(_Args_&&...args) {
        using _MIXTYPE_=typename MixType<_Type_,true,false>::type;
        /*create mix type*/
        return DirectNew::template create_virtual<_MIXTYPE_>(std::forward<_Args_>(args)...);
    }
};

template<>
class MixNew<false,true> {
public:
    template<typename _Type_,typename ... _Args_>
    static auto create(_Args_&&...args) {
        using _MIXTYPE_=typename MixType<_Type_,false,true>::type;
        /*create mix type*/
        return DirectNew::template create_virtual<_MIXTYPE_>(std::forward<_Args_>(args)...);
    }
};

}

}

/*
using memory::template new_class    replace new
using memory::template delete_class replace delete
*/
class memory {
public:

    template<typename _Type_>
    class new_type {
        static_assert(std::is_reference<_Type_>::value==false,
            "_Type_ should not be a ref");
    public:
        using type=std::conditional_t<
            std::has_virtual_destructor<_Type_>::value,
            std::conditional_t<
            std::is_base_of<cpp_virtual_base::VirtualClass,_Type_>::value,
            _Type_/*if is virtualclass*/,
            typename cpp_virtual_base::__private::MixType<
            _Type_,
            std::is_move_constructible<_Type_>::value,
            std::is_constructible<_Type_>::value
            >::type/*if is virtual but not virtualclass*/
            >,
            _Type_/*if is not virtual class*/
        >;
    };

    template<typename _Type_>
    using new_type_t=typename new_type<_Type_>::type;

    template<typename _Type_>
    using new_t=new_type_t<_Type_>;

    template<typename _Type_,typename ..._Args_>
    static inline auto new_class(_Args_&&...args)->_Type_ * {
        static_assert(std::is_reference<_Type_>::value==false,
            "_Type_ should not be a ref");
        using _VARNEWTYPE_=std::conditional_t<
            std::has_virtual_destructor<_Type_>::value,
            std::conditional_t<
            std::is_base_of<cpp_virtual_base::VirtualClass,_Type_>::value,
            cpp_virtual_base::__private::DirectMixNew/*if is VirtualClass*/,
            cpp_virtual_base::__private::MixNew<
            std::is_move_constructible<_Type_>::value,
            std::is_constructible<_Type_>::value
            >/*if is virtual class but not VirtualClass*/
            >,
            cpp_virtual_base::__private::DirectNew/*if is not abstract class*/
        >;

        return _VARNEWTYPE_::template create<_Type_>(std::forward<_Args_>(args)...);
    }

    template<typename _Type_>
    static inline void delete_class(_Type_&&arg) {

        using _TYPE_=std::remove_cv_t<
            std::remove_pointer_t<
            std::remove_reference_t<_Type_>>>;

        using _VARDELETECLASS_=std::conditional_t<
            std::has_virtual_destructor<_TYPE_>::value,
            cpp_virtual_base::__private::MixDelete,
            cpp_virtual_base::__private::DirectDelete
        >;

        return _VARDELETECLASS_::template free(std::forward<_Type_>(arg));
    }
};

#endif

