#ifndef PRAGMA_IN_CPP_FILE_ONCE_VIRTUAL_CLASS_
#define PRAGMA_IN_CPP_FILE_ONCE_VIRTUAL_CLASS_

/*
此文件只能被cpp文件包含
此文件必须被最后包含
此文件在不同cpp文件中编译结果不同
*/

#include "QuickCast.hpp"
#include "VirtualClass.hpp"

namespace {
/*强制编译器为每一个cpp文件生成不同的函数*/
template<typename Type>
Type _cppfile_VirtualClass_getData(const VirtualClass * arg)  {
    switch (arg->type()) {
        case VirtualClass::Type::IndexVoid:return nullptr; break;
        case VirtualClass::Type::IndexConstVoid:return nullptr; break;
        case VirtualClass::Type::IndexQObject:return quickCast<Type>(reinterpret_cast<QObject*>(arg->data())); break;
        case VirtualClass::Type::IndexConstQObject:return quickCast<Type>(reinterpret_cast<const QObject *>(arg->data())); break;
        default:return nullptr; break;
    }
}
}/*~namespace*/

template<typename Type>
Type VirtualClass::getData() const{
    static_assert(std::is_pointer<Type>::value,"Type must be pointer");
    if (_data_void_==nullptr) { return nullptr; }
    return _cppfile_VirtualClass_getData<Type>(this);
}


#endif


