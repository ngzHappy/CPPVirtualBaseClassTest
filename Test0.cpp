#include "Test0.hpp"
#include <QtCore/qdebug.h>
#include <QtCore/qcoreapplication.h>

Test0::Test0():thisThread_(new ThisThread){
    moveToThread(thisThread_);

    {/*设置线程自删除*/
        connect(thisThread_,&ThisThread::finished,
                qApp,[thisThread_=thisThread_](){delete thisThread_;});
    }

    {/*绑定线程信号槽*/
        using T=Test0;
        connect(this,&T::foo,this,&T::_p_foo,Qt::QueuedConnection);
        connect(this,&T::call,this,&T::_p_call,Qt::QueuedConnection);
    }

    thisThread_->start();
}

Test0::~Test0(){
    thisThread_->exit();
}

void Test0::ThisThread::run(){
    exec();
}

Test0::ThisThread::~ThisThread(){
    qDebug().noquote()<<__func__;
}

void Test0::_p_foo(){
    qDebug().noquote()<<__func__;
}

void Test0::_p_call(Callable arg){
    return arg();
}

void Test0::xxxx() {}

