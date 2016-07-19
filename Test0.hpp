#ifndef TEST0_HPP
#define TEST0_HPP

#include <QtCore/qobject.h>
#include <QtCore/qthread.h>

#include <memory>
#include <functional>
#include <type_traits>

class Callable {
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
private:
    std::shared_ptr<const std::function<void(void)>> data_;
public:
    Callable()=default;
    ~Callable()=default;

    Callable(const Callable&)=default;
    Callable(Callable&&)=default;

    Callable&operator=(const Callable&)=default;
    Callable&operator=(Callable&&)=default;

    template<typename TypeT,typename TypeTIsNotCallable=is_not_t<TypeT,Callable>
    >Callable(TypeT && arg)
        :data_(new std::function<void(void)>{ std::forward<TypeT>(arg) }) {}

    void operator()()const { if (data_) { const auto & varFunction=*data_; if (varFunction) { varFunction(); } } }
    operator bool()const { if (data_) { if (*data_) { return true; } }return false; }
};

class Test0 :public QObject {
    Q_OBJECT
        class ThisThread :public QThread {
        public:
            void run() override;
            ~ThisThread();
    };
    ThisThread *const thisThread_;
public:
    Test0();
    ~Test0();

    Q_SLOT void xxxx();

signals:
    void foo();
    void call(Callable);



    private slots:
    void _p_foo();
    void _p_call(Callable);
};

Q_DECLARE_METATYPE(Callable)

#endif // TEST0_HPP
