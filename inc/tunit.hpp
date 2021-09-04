#pragma once
#ifndef __HEADER_GUARD_TUNIT__
#define __HEADER_GUARD_TUNIT__
#include <type_traits>

#ifdef TUNIT_DEBUG
#include <iostream>
#include <sstream>
#endif

namespace tunit {

namespace pseudo {

// a*1=a,a/1=aを表現する
struct type_one final {
    constexpr type_one() {}
};

// a+0=a,a-0=aを表現する
struct type_zero final {
    constexpr type_zero() {}
};

constexpr static type_one one;
constexpr static type_zero zero;

#define PSEUDO_OP(type, op)                                                    \
    template <class T>                                                         \
    constexpr static inline const T &operator op(type, const T &value) {       \
        return value;                                                          \
    }                                                                          \
    template <class T>                                                         \
    constexpr static inline const T &operator op(const T &value, type) {       \
        return value;                                                          \
    }

PSEUDO_OP(type_one, *);
PSEUDO_OP(type_one, /);
PSEUDO_OP(type_zero, +);
PSEUDO_OP(type_zero, -);
PSEUDO_OP(type_zero, |);

#undef PSEUDO_OP

// reverse 補助単位の変換時にむやみに型変換せずに計算するために使う
// '/'と'*'を入れ替えたもの

struct rint final {
    int value;
    constexpr rint(const int &_value) : value(_value) {}
    constexpr rint(const rint &) = default;
};

template <class T> int operator*(const T &lhs, const rint &rls) {
    return lhs / rls.value;
}

template <class T> int operator*(const rint &lhs, const T &rls) {
    return rls/lhs.value;
}

template <class T> int operator/(const T &lhs, const rint &rls) {
    return lhs * rls.value;
}

template <class T> int operator/(const rint &lhs, const T &rls) {
    return rls*lhs.value;
}

}; // namespace pseudo

namespace ranks {
// 必要に応じてパラメータを増やすこと
template <int _e0 = 0, int _e1 = 0, int _e2 = 0, int _e3 = 0, int _e4 = 0,
          int _e5 = 0, int _e6 = 0, int _e7 = 0, int _e8 = 0, int _e9 = 0>
struct ranked {
    static constexpr int e0 = _e0;
    static constexpr int e1 = _e1;
    static constexpr int e2 = _e2;
    static constexpr int e3 = _e3;
    static constexpr int e4 = _e4;
    static constexpr int e5 = _e5;
    static constexpr int e6 = _e6;
    static constexpr int e7 = _e7;
    static constexpr int e8 = _e8;
    static constexpr int e9 = _e9;

    static constexpr ranked<e0, e1, e2, e3, e4, e5, e6, e7, e8, e9> value();
    using type = ranked<e0, e1, e2, e3, e4, e5, e6, e7, e8, e9>;
};

/* Rankに対して線形性を持つように型演算を定義する
 *
 * z=x+y, a(x+y)=ax+by
 * 0*x=0, 0+x=a
 *
 * x,y,z: Rank
 * a,b: integer
 */

#ifdef TUNIT_DEBUG
template <int e0, int e1, int e2, int e3, int e4, int e5, int e6, int e7,
          int e8, int e9>
static inline std::ostream &
operator<<(std::ostream &os,
           const ranked<e0, e1, e2, e3, e4, e5, e6, e7, e8, e9> &r) {
    os << "(";
    os << e0 << "," << e1 << "," << e2 << "," << e3 << "," << e4;
    os << ",";
    os << e5 << "," << e6 << "," << e7 << "," << e8 << "," << e9;
    os << ")";
    return os;
}
#endif

template <class... Rs> struct sum {
    static constexpr int e0 = 0;
    static constexpr int e1 = 0;
    static constexpr int e2 = 0;
    static constexpr int e3 = 0;
    static constexpr int e4 = 0;
    static constexpr int e5 = 0;
    static constexpr int e6 = 0;
    static constexpr int e7 = 0;
    static constexpr int e8 = 0;
    static constexpr int e9 = 0;

    static constexpr ranked<e0, e1, e2, e3, e4, e5, e6, e7, e8, e9> value();
    using type = ranked<e0, e1, e2, e3, e4, e5, e6, e7, e8, e9>;
};

template <class R1, class... Rs> struct sum<R1, Rs...> {
    using next = sum<Rs...>;
    static constexpr int e0 = R1::e0 + next::e0;
    static constexpr int e1 = R1::e1 + next::e1;
    static constexpr int e2 = R1::e2 + next::e2;
    static constexpr int e3 = R1::e3 + next::e3;
    static constexpr int e4 = R1::e4 + next::e4;
    static constexpr int e5 = R1::e5 + next::e5;
    static constexpr int e6 = R1::e6 + next::e6;
    static constexpr int e7 = R1::e7 + next::e7;
    static constexpr int e8 = R1::e8 + next::e8;
    static constexpr int e9 = R1::e9 + next::e9;

    static constexpr ranked<e0, e1, e2, e3, e4, e5, e6, e7, e8, e9> value();
    using type = ranked<e0, e1, e2, e3, e4, e5, e6, e7, e8, e9>;
};

template <int n, class R> struct mul {
    static constexpr int e0 = n * R::e0;
    static constexpr int e1 = n * R::e1;
    static constexpr int e2 = n * R::e2;
    static constexpr int e3 = n * R::e3;
    static constexpr int e4 = n * R::e4;
    static constexpr int e5 = n * R::e5;
    static constexpr int e6 = n * R::e6;
    static constexpr int e7 = n * R::e7;
    static constexpr int e8 = n * R::e8;
    static constexpr int e9 = n * R::e9;

    static constexpr ranked<e0, e1, e2, e3, e4, e5, e6, e7, e8, e9> value();
    using type = ranked<e0, e1, e2, e3, e4, e5, e6, e7, e8, e9>;
};

template <class R1, class R2> using add = typename sum<R1, R2>::type;
template <class R1, class R2> using sub = typename sum<R1, mul<-1, R2>>::type;
template <class R> using inverse = typename mul<-1, R>::value::type;

//補助単位

using giga = ranked<9>;
using mege = ranked<6>;
using kilo = ranked<3>;
using normal = ranked<0>;
using milli = ranked<-3>;
using micro = ranked<-6>;
using nano = ranked<-9>;

//次元(直行させること)) SI系
template <int n = 1> using m = typename mul<n, ranked<0, 1>>::type;
template <int n = 1>
using kg = typename mul<n, ranked<0, 0, 1>>::type; // kgを基本としているので...
template <int n = 1> using sec = typename mul<n, ranked<0, 0, 0, 1>>::type;
template <int n = 1> using A = typename mul<n, ranked<0, 0, 0, 0, 1>>::type;
template <int n = 1> using K = typename mul<n, ranked<0, 0, 0, 0, 0, 1>>::type;
template <int n = 1>
using mod = typename mul<n, ranked<0, 0, 0, 0, 0, 0, 0, 1>>::type;
template <int n = 1>
using cd = typename mul<n, ranked<0, 0, 0, 0, 0, 0, 0, 0, 1>>::type;
template <int n = 1>
using rad =
    typename mul<n, ranked<0, 0, 0, 0, 0, 0, 0, 0, 0, 1>>::type; //角度用

//組立量
template <int n = 1> using N = typename mul<n, sum<m<1>, kg<1>, sec<-2>>>::type;

template <int n = 1> using Pa = typename mul<n, sum<N<1>, m<-2>>>::type;

template <int n = 1> using J = typename mul<n, sum<N<1>, m<1>>>::type;
template <int n = 1>
using V = typename mul<n, sum<m<2>, kg<1>, sec<-3>, A<-1>>>::type;
template <int n = 1> using ohm = typename mul<n, sum<V<1>, A<-1>>>::type;
template <int n = 1> using S = ohm<-1>;
template <int n = 1> using W = typename mul<n, sum<m<2>, kg<1>, sec<-3>>>::type;
template <int n = 1> using C = typename mul<n, sum<m<2>, kg<1>, sec<-3>>>::type;

// 参考: https://japanknowledge.com/contents/common/si.html
}; // namespace ranks

namespace units {

template <class T, class R = ranks::ranked<>> struct united final {
    T value;
    constexpr united(const T &_value) : value(_value) {}
    constexpr united(T &&_value) : value(_value) {}
    constexpr united(const united &_unit) : value(_unit.value) {}

    template <class T2> constexpr const united &operator=(const T2 &rls) {
        value = rls.value;
        return *this;
    }

    template <class T2>
    constexpr const united &operator=(const united<T2, R> &rls) {
        value = rls.value;
        return *this;
    }
};

// unary operator
template <class T, class R>
constexpr const T &operator*(const united<T, R> &lhs) {
    return lhs.value;
}

#define UNITED_UNARY_OP(op)                                                    \
    template <class T, class R>                                                \
    constexpr const auto &operator op(united<T, R> &lhs) {                     \
        op lhs.value;                                                          \
        return lhs;                                                            \
    }                                                                          \
                                                                               \
    template <class T, class R>                                                \
    constexpr const auto &operator op(united<T, R> &lhs, int) {                \
        lhs.value op;                                                          \
        return lhs;                                                            \
    }

UNITED_UNARY_OP(++);
UNITED_UNARY_OP(--);

#undef UNITED_UNARY_OP

// operator
#define UNITED_BINARY_OP(op)                                                   \
    template <class T1, class T2, class R>                                     \
    constexpr static inline auto operator op(const united<T1, R> &lhs,         \
                                             const united<T2, R> &rhs) {       \
        auto result = lhs.value op rhs.value;                                  \
        return united<decltype(result), R>(result);                            \
    }                                                                          \
                                                                               \
    template <class T1, class T2, class R>                                     \
    constexpr static inline auto operator op(const united<T1, R> &lhs,         \
                                             const T2 &rhs) {                  \
        auto result = lhs.value op rhs;                                        \
        return united<decltype(result), R>(result);                            \
    }                                                                          \
                                                                               \
    template <class T1, class T2, class R>                                     \
    constexpr static inline auto operator op(const T1 &lhs,                    \
                                             const united<T2, R> &rhs) {       \
        auto result = lhs op rhs.value;                                        \
        return united<decltype(result), R>(result);                            \
    }

UNITED_BINARY_OP(+);
UNITED_BINARY_OP(-);
UNITED_BINARY_OP(%);
UNITED_BINARY_OP(|);
UNITED_BINARY_OP(&);
// UNITED_BINARY_OP(<<);
// UNITED_BINARY_OP(>>);

#undef UNITED_BINARY_OP

#define UNITED_BINARY_OP2(op, mode)                                            \
                                                                               \
    template <class T1, class T2, class R>                                     \
    constexpr auto operator op(const united<T1, R> &lhs, const T2 &rhs) {      \
        auto result = lhs.value op rhs;                                        \
        return united<decltype(result), R>(result);                            \
    }                                                                          \
                                                                               \
    template <class T1, class T2, class R>                                     \
    constexpr auto operator op(const T1 &lhs, const united<T2, R> &rhs) {      \
        auto result = lhs op rhs.value;                                        \
        return united<decltype(result), R>(result);                            \
    }                                                                          \
                                                                               \
    template <class T1, class T2, class R1, class R2>                          \
    constexpr auto operator op(const united<T1, R1> &lhs,                      \
                               const united<T2, R2> &rhs) {                    \
        auto result = lhs.value op rhs.value;                                  \
        return united<decltype(result), mode<R1, R2>>(result);                 \
    }

UNITED_BINARY_OP2(*, ranks::add);
UNITED_BINARY_OP2(/, ranks::sub);

#undef UNITED_BINARY_OP2

// operator comparator

#define UNITED_OP_COMPARE(op)                                                  \
    template <class T1, class T2, class R>                                     \
    constexpr static inline bool operator op(const united<T1, R> &lhs,         \
                                             const united<T2, R> &rhs) {       \
        return lhs.value op rhs.value;                                         \
    }                                                                          \
                                                                               \
    template <class T1, class T2, class R>                                     \
    constexpr static inline bool operator op(const T1 &lhs,                    \
                                             const united<T2, R> &rhs) {       \
        return lhs op rhs.value;                                               \
    }                                                                          \
                                                                               \
    template <class T1, class T2, class R>                                     \
    constexpr static inline bool operator op(const united<T1, R> &lhs,         \
                                             const T2 &rhs) {                  \
        return lhs.value op rhs;                                               \
    }

UNITED_OP_COMPARE(==);
UNITED_OP_COMPARE(!=);
UNITED_OP_COMPARE(>);
UNITED_OP_COMPARE(<);
UNITED_OP_COMPARE(>=);
UNITED_OP_COMPARE(<=);
#undef UNITED_OP_COMPARE

#define UNITED_ASSIGN_OP(op)                                                   \
                                                                               \
    template <class T1, class T2, class R>                                     \
    constexpr static inline auto operator op(united<T1, R> &lhs,               \
                                             const T2 &rhs) {                  \
        auto result = lhs.value op rhs;                                        \
        return united<decltype(result), R>(result);                            \
    }                                                                          \
                                                                               \
    template <class T1, class T2, class R>                                     \
    constexpr static inline auto operator op(united<T1, R> &lhs,               \
                                             const united<T2, R> &rhs) {       \
        auto result = lhs.value op rhs.value;                                  \
        return united<decltype(result), R>(result);                            \
    }

UNITED_ASSIGN_OP(+=);
UNITED_ASSIGN_OP(-=);
UNITED_ASSIGN_OP(%=);
UNITED_ASSIGN_OP(|=);
UNITED_ASSIGN_OP(&=);

#undef UNITED_ASSIGN_OP

#ifdef TUNIT_DEBUG
template <class T, class R>
static inline std::ostream &operator<<(std::ostream &os,
                                       const united<T, R> &u) {
    os << u.value << R();
    return os;
}
#endif

// 長さに関する単位
template <class T> using meter = united<T, ranks::m<1>>;
template <class T>
using meter_s = united<T, ranks::sum<ranks::m<1>, ranks::sec<-1>>::type>;

template <class T>
using meter_s2 = united<T, ranks::sum<ranks::m<1>, ranks::sec<-2>>::type>;
template <class T> using meter = united<T, ranks::m<1>>;

// 角度に関する単位
template <class T> using rad = united<T, ranks::rad<1>>;
template <class T>
using rad_s = united<T, ranks::sum<ranks::rad<1>, ranks::sec<-1>>::type>;
template <class T>
using rad_s2 = united<T, ranks::sum<ranks::rad<1>, ranks::sec<-2>>::type>;

// 時間に関する単位
template <class T> using s = united<T, ranks::sec<1>>;
template <class T>
using ms = united<T, ranks::sum<ranks::milli, ranks::sec<1>>::type>;
template <class T>
using us = united<T, ranks::sum<ranks::micro, ranks::sec<1>>::type>;
template <class T>
using ns = united<T, ranks::sum<ranks::nano, ranks::sec<1>>::type>;
template <class T> using Hz = united<T, ranks::sec<-1>>;
template <class T>
using KHz = united<T, ranks::sum<ranks::kilo, ranks::sec<-1>>::type>;
template <class T>
using MHz = united<T, ranks::sum<ranks::mege, ranks::sec<-1>>::type>;
template <class T>
using GHz = united<T, ranks::sum<ranks::giga, ranks::sec<-1>>::type>;

// 電気に関する単位
template <class T> using A = united<T, ranks::A<1>>;
template <class T> using V = united<T, ranks::V<1>>;
template <class T> using ohm = united<T, ranks::ohm<1>>;
template <class T> using W = united<T, ranks::W<1>>;
template <class T> using J = united<T, ranks::J<1>>;
} // namespace units

namespace values {
//単位系
constexpr units::rad<pseudo::type_one> rad(pseudo::one);
constexpr units::s<pseudo::type_one> s(pseudo::one);
constexpr units::Hz<pseudo::type_one> Hz(pseudo::one);
constexpr units::meter<pseudo::type_one> meter(pseudo::one);
constexpr units::A<pseudo::type_one> A(pseudo::one);
constexpr units::V<pseudo::type_one> V(pseudo::one);
constexpr units::ohm<pseudo::type_one> ohm(pseudo::one);
constexpr units::W<pseudo::type_one> W(pseudo::one);
constexpr units::J<pseudo::type_one> J(pseudo::one);

//補助単位
constexpr units::united<int, ranks::ranked<-12>> p(1000'000'000);
constexpr units::united<int, ranks::ranked<-9>> n(1000'000'000);
constexpr units::united<int, ranks::ranked<-6>> u(1000'000);
constexpr units::united<int, ranks::ranked<-3>> m(1000);
constexpr units::united<int, ranks::ranked<0>> id(1);
constexpr units::united<pseudo::rint, ranks::ranked<3>> k(pseudo::rint(1000));
constexpr units::united<pseudo::rint, ranks::ranked<6>> M(pseudo::rint(1000'000));
constexpr units::united<pseudo::rint, ranks::ranked<9>> G(pseudo::rint(1000'000'000));

} // namespace values

} // namespace tunit
#endif