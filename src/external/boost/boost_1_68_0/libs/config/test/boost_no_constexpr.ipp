//  (C) Copyright Beman Dawes 2008

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/config for more information.

//  MACRO:         BOOST_NO_CXX11_CONSTEXPR
//  TITLE:         C++0x constexpr unavailable
//  DESCRIPTION:   The compiler does not support C++0x constexpr

namespace boost_no_cxx11_constexpr {

void quiet_warning(int){}

constexpr int square(int x) { return x * x; }  // from N2235

// from 5.19:
constexpr const int* addr(const int& ir) { return &ir; }
static const int x = 5;
constexpr const int* xp = addr(x);

struct A
{
   constexpr A(int i) : val(i) { }
   constexpr operator int()const { return val; }
   constexpr operator long()const { return 43; }
private:
   int val;
};

template<int> struct X { };


#if __cplusplus < 201400L
// Some C++14 compilers reject this (clang), some C++11 compilers reject "constexpr const" (GCC-4.6)
constexpr A a = 42;
#else
constexpr const A a = 42;
#endif

X<a> xx; // OK: unique conversion to int

// virtual function
struct B
{
   virtual void vf() {}
};
struct C : B
{
   constexpr C() {}
};

// aggregate initialization
struct D
{
   int val[2];
   constexpr D() : val() {}
};

// virtual base
struct E
{
};
struct F : virtual E
{
};
constexpr F& f(F& out) { return out; }

int test()
{
  int i = square(5);
  quiet_warning(i);

  switch (i)
  {
  case a:
    break;
  }

  return 0;
}

}
