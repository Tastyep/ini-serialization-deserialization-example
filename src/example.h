#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <boost/describe.hpp>
#include <string>

class Numbers
{
  public:

  int   one;
  int   two;
  float three;

  BOOST_DESCRIBE_CLASS(Numbers, (), (), (), (one, two, three));
};

class Letters
{
  public:

  std::string a;
  std::string b;
  std::string c;

  BOOST_DESCRIBE_CLASS(Letters, (), (), (), (a, b, c));
};

class Bools
{
  public:

  bool yes;
  bool no;

  BOOST_DESCRIBE_CLASS(Bools, (), (), (), (yes, no));
};

class Example

{
  public:

  Numbers numbers;
  Letters letters;
  Bools   bools;

  BOOST_DESCRIBE_CLASS(Example, (), (), (), (numbers, letters, bools));
};

#endif
