/**
 * simple implementation like std::bind()
 * TODO: doesn't support placeholder
 */

#include <type_traits>
#include <utility>
#include <iostream>
#include <tuple>
#include <functional>

template <typename T, bool Enable, typename ...Args>
class Closure;

// for function
template <typename Fn, typename ...Args>
class Closure<Fn, false, Args...> {
public:
    Closure(Fn &&func, Args &&...arguments)
        : f(std::forward<Fn>(func)), args(std::forward<Args>(arguments)...) {}

    decltype(auto) operator()() {
        return call(std::make_index_sequence<sizeof...(Args)>{});
    }

private:
    Fn f;
    std::tuple<Args...> args;

    template <std::size_t ...Seq>
    decltype(auto) call(std::index_sequence<Seq...>) {
        f(std::get<Seq>(args)...);
    }
};

// for class member function
template <typename MemFunc, typename Cls, typename ...Args>
class Closure<MemFunc, true, Cls, Args...> {
public:
    Closure(MemFunc &&func, Cls &&o, Args &&...arguments)
        : f(std::forward<MemFunc>(func)),
          obj(std::forward<Cls>(o)),
          args(std::forward<Args>(arguments)...) {}

    decltype(auto) operator()() {
        return call(std::make_index_sequence<sizeof...(Args)>{});
    }

private:
    MemFunc f;
    Cls obj;
    std::tuple<Args...> args;

    template <std::size_t ...Seq>
    decltype(auto) call(std::index_sequence<Seq...>) {
        (obj->*f)(std::get<Seq>(args)...);
    }

};

template <typename Fn, typename ...Args>
decltype(auto) simple_bind(Fn &&func, Args &&...args) {
    const bool isMemFunc = std::is_member_function_pointer<Fn>::value;
    return Closure<Fn, isMemFunc, Args...>{std::forward<Fn>(func), std::forward<Args>(args)...};
}

struct A {
    void sum(int a, int b) {
        std::cout << "A::sum(" << a << ", " << b << ") = " << a + b << std::endl;
    }
};

int main() {
    auto f = simple_bind([](int a, int b) {
                std::cout << a << " + " << b << " = " << a + b << std::endl;
            }, 100, 200);
    f();

    A a;
    auto ff = simple_bind(&A::sum, &a, 1, 2);
    ff();
}