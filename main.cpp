#include "MainWindow.hpp"
#include <QApplication>
#include "Test0.hpp"
#include <QtCore/qdebug.h>
#include <QtCore/qtimer.h>
#include <atomic>
#include "NewClass.hpp"

class TestEvent :public QEvent {
    Callable call_;
    static std::atomic<unsigned int> value_;
public:
    TestEvent():QEvent(QEvent::MaxUser) { ++value_; }
    TestEvent(const Callable &arg):TestEvent() { call_=arg; }
    TestEvent(Callable &&arg):TestEvent() { call_=std::move(arg); }

    void operator()()const { call_(); }
    void call() const { call_(); }

    ~TestEvent() { --value_; }
};

std::atomic<unsigned int> TestEvent::value_{ 0 };

class Application :public QApplication {
public:

    Application(int argc,char ** argv):QApplication(argc,argv) {

    }

    bool event(QEvent * argEvent)override {

        {
            auto * varEvent=dynamic_cast<TestEvent*>(argEvent);
            if (varEvent) {
                varEvent->call();
                return true;
            }
        }

        return QApplication::event(argEvent);
    }

};

class MMM {
public:
    MMM() {}

    MMM(const MMM &) {}
    MMM(MMM &&) {}
    MMM(const MMM &&arg):MMM(static_cast<const MMM &>(arg)) {}
    MMM(MMM &arg):MMM(static_cast<const MMM &>(arg)) {}

    template<typename TypeT>
    MMM(TypeT&&) { qDebug().noquote()<<"create template &&"; }

    void foo() const & { qDebug().noquote()<<"const &"; }
    void foo() const && { qDebug().noquote()<<"const &&"; }
    void foo() & { qDebug().noquote()<<"&"; }
    void foo()&&{ qDebug().noquote()<<"&&"; }
};


class TestMMOO {};

class TestR {
    /*C++14*/
    template<typename _P_Type_0_,typename _P_Type_1_>
    class IsNot final :public std::enable_if<false==std::is_same<
        std::remove_cv_t<std::remove_reference_t<_P_Type_0_>>,
        std::remove_cv_t<std::remove_reference_t<_P_Type_1_>>>::value> {
    };

    template<typename _P_Type_0_,typename _P_Type_1_>
    using is_not=IsNot<_P_Type_0_,_P_Type_1_>;

    template<typename _P_Type_0_,typename _P_Type_1_>
    using is_not_t=typename IsNot<_P_Type_0_,_P_Type_1_>::type;
public:

    void call(const TestMMOO &) {
    }
    void call(TestMMOO &&) {
    }

    template<
        typename Type,
        typename TypeLimit_0=std::enable_if_t<
        std::is_convertible<Type,const TestMMOO>::value==false>
    >
        void call(Type &&) {
    }

};


void foox(MMM && m) { m.foo(); }
void foox(const MMM & m) { m.foo(); }
void foox(const MMM && m) { m.foo(); }
void foox(MMM & m) { m.foo(); }

#include <string>

class III {
    std::string value_;
public:
    void setValue(const std::string& /*value*/);
    void setValue(std::string&& /*value*/);
    void setValue(std::string& /*value*/arg) { setValue(static_cast<const std::string&>(arg)); }
    void setValue(const std::string&& /*value*/arg) { setValue(static_cast<const std::string&>(arg)); }
    const std::string & getValue() const;
    decltype(auto) value() const { return getValue(); }
private: template<typename _t_VALUE_t__>
    void _p_setValue(_t_VALUE_t__ && /*value*/);
};

const std::string & III::getValue() const {
    return value_;
}

template<typename _t_VALUE_t__>
void III::_p_setValue(_t_VALUE_t__ &&) {

}

void III::setValue(const std::string&_value_) {
    _p_setValue(_value_);
}

void III::setValue(std::string&&_value_) {
    _p_setValue(std::move(_value_));
}

#include <QtGlobal>

struct Foo {
    void overloadedFunction(int,QString) {}
    void overloadedFunction(int,QString) const {}
};

#include "QuickCast.hpp"


class A { public:virtual ~A() {} };
class B :public A {};


class VirtualBase {public:
    virtual ~VirtualBase()=default;
};

class V1 :public VirtualBase{};
class V2 :public VirtualBase {};

class V3 :public V1,public V2 {
public:
    operator VirtualBase&() { return (V1&)(*this); }
    operator const VirtualBase&() const{ return (V1&)(*this); }
};

class VirtualClassBase {
public:
    virtual ~VirtualClassBase()=default;
};

template<typename Type>
class CastToVirtualClassBase {
    using type=std::remove_cv_t<std::remove_pointer_t<std::remove_reference_t<Type>>>;
public:
    static VirtualClassBase * cast(type *arg) { return arg; }
    static const VirtualClassBase * cast(const type *arg) { return arg; }
    static VirtualClassBase & cast(type &arg) { return arg; }
    static VirtualClassBase && cast(type &&arg) { return arg; }
    static const VirtualClassBase & cast(const type &arg) { return arg; }
};


#include "VirtualClass.hpp"
#include "JustInCppFileVirtualClass.hpp"

class M11;
class M22;

class Test_0 {};
class Test_1 :public cpp_virtual_base::VirtualClass {
public:
    virtual std::type_index concept_type_index() const override {
        return typeid(Test_1);
    }
};

class Test_2 {
public:
    virtual~Test_2()=default;
};

namespace cpp_virtual_base {
template<>
class LogicalClass<Test_2> {
public:
    using type=Test_2;
};
}

class Test_3 :public cpp_virtual_base::VirtualClass{
public:
    virtual std::type_index concept_type_index() const override {
        return typeid(Test_3);
    }
};

class Test_4 :
    public Test_3,
    public Test_1{
public:
    virtual std::type_index concept_type_index() const override {
        return typeid(Test_4);
    }
};

int main(int argc,char *argv[]) {
    Application app(argc,argv);

    {
        memory::template delete_class(
        memory::template new_class<int>(13)
                    );
    }

    {
        static_assert(std::is_same<memory::new_type_t<int>,int>::value,"?");
        static_assert(std::is_same<memory::new_type_t<Test_1>,Test_1>::value,"?");
        static_assert(std::is_same<memory::new_type_t<Test_2>,Test_2>::value==false,"?");
        Test_2 * value = new memory::new_type_t<Test_2>{};
        delete value;
    }

    {
            auto * t0=memory::template new_class<const Test_0>();
            auto * t1=memory::template new_class<const Test_1>();
            auto * t2=memory::template new_class<const Test_2>();
            auto * t4=memory::template new_class<const Test_4>();
            auto * xt2=dynamic_cast<const cpp_virtual_base::VirtualClass*>(t2);
            (void)xt2;

            check_cpp_virtual_base(t2);
            check_cpp_virtual_base(nullptr);

            memory::template delete_class(t0);
            memory::template delete_class(t1);
            memory::template delete_class(t2);
            memory::template delete_class(t4);

        }


    {
        VirtualClass vc;
        vc.getData<QObject*>();
    }

    {
        M11 * m1;
        quickCast<M22*>(m1);
    }

    {
        V3 v3;

        V1 & v1=v3;
        VirtualBase & vb=v1;

        quickCast<V3&>(vb);

    }

    {
        B b{};
        A & test_0=b;

        //decltype(static_cast<B&>(std::declval<A&>())) sfd;

        //dynamic_cast<B&>(test_0);

        quickCast<B&>(test_0);
        //static_cast<B&>(test_0);

        enum {
            ttt=
            QuickCast<A&,B&>::value
        };

        qDebug()<<QuickCast<A*,B*>::value;
        //test_is_static_cast<B&,A&>(test_0 );
    }

    QVariant v(123.0f);
    QString str=v.value<QString>();
    double d=v.value<double>();

    TestMMOO trrr;
    TestR r;
    r.call(trrr);

    QTimer * timer=new QTimer;
    timer->connect(timer,&QTimer::timeout,
        [&app]() {
        Application::postEvent(&app,new TestEvent([]() {qDebug()<<"6666"; }));
    });
    timer->start(100);

    foox(MMM{});

    MMM m;
    MMM m11{ m };

    Test0 * test0=new Test0;

    MainWindow window;
    window.show();

    test0->foo();
    test0->call([]() {qDebug().noquote()<<"1111"; });
    test0->deleteLater();

    return app.exec();
}
