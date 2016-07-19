
#ifndef _PRAGMA_ONCE_VIRTUAL_CLASS__HPP_
#define _PRAGMA_ONCE_VIRTUAL_CLASS__HPP_

#include <utility>
#include <cstddef>
#include <cstdint>
#include <cstdbool>
#include <type_traits>

namespace/**/xxx { class QObject;/**/ }
namespace/**/jjj { class xxxxd;/**/ }


class VirtualClass {
    using _Type=std::intptr_t;
public:

    enum class Type :_Type {
        IndexVoid,
        IndexConstVoid,
        /*Index...*/
        Index_XXX_QObject,
        IndexConst_XXX_QObject,
        Index_JJJ_xxxxd,
        IndexConst_JJJ_xxxxd,

    }_type_;

private:
    union {
        void * _data_void_;
        /*data...*/
        xxx::QObject * _data_XXX_QObject_;
        jjj::xxxxd * _data_JJJ_xxxxd_;

    };

public:

    VirtualClass():_type_(Type::IndexVoid),_data_void_(nullptr) {}
    VirtualClass(decltype(nullptr)):VirtualClass() {}
    VirtualClass(xxx::QObject *arg):_type_(Type::Index_XXX_QObject),_data_XXX_QObject_(arg) {}
    VirtualClass(const xxx::QObject *arg):_type_(Type::IndexConst_XXX_QObject),_data_XXX_QObject_(const_cast<xxx::QObject *>(arg)) {}

    VirtualClass(jjj::xxxxd *arg):_type_(Type::Index_JJJ_xxxxd),_data_JJJ_xxxxd_(arg) {}
    VirtualClass(const jjj::xxxxd *arg):_type_(Type::IndexConst_JJJ_xxxxd),_data_JJJ_xxxxd_(const_cast<jjj::xxxxd *>(arg)) {}


    bool isConstPointer() const { return static_cast<_Type>(_type_)&1; }
    Type type() const { return _type_; }
    void * data() const { return _data_void_; }

    /*defined in JustInCppFileVirtualClass.hpp*/
    template<typename Type>Type getData() const;

};

#endif

