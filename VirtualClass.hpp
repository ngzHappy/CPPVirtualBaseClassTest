
#ifndef _PRAGMA_ONCE_VIRTUAL_CLASS__HPP_
#define _PRAGMA_ONCE_VIRTUAL_CLASS__HPP_

#include <utility>
#include <cstddef>
#include <cstdint>
#include <cstdbool>
#include <type_traits>

class QObject;
class VirtualClass {
    using _Type=std::intptr_t;
public:

    enum class Type:_Type{
        IndexVoid,
        IndexConstVoid,
        IndexQObject,
        IndexConstQObject,
    }_type_;

private:
    union  {
        void * _data_void_;
        QObject * _data_QObject_;
    };

public:

    VirtualClass() :_type_(Type::IndexVoid),_data_void_(nullptr){}
    VirtualClass(decltype(nullptr)):VirtualClass() {}
    VirtualClass(QObject *arg):_type_(Type::IndexQObject),_data_QObject_(arg) {}
    VirtualClass(const QObject *arg):_type_(Type::IndexConstQObject),_data_QObject_( const_cast<QObject *>(arg)) {}

    bool isConstPointer() const { return static_cast<_Type>(_type_)&1; }
    Type type() const{ return _type_; }
    void * data() const { return _data_void_; }

    /*defined in JustInCppFileVirtualClass.hpp*/
    template<typename Type>Type getData() const;

};

#endif


