#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <boost/describe.hpp>
#include <string>

class Numbers {
public:
  int one;
  int two;

  BOOST_DESCRIBE_CLASS(Numbers, (), (), (), (one, two));
};

class Letters {
public:
  std::string a;
  std::string b;
  std::string c;

  BOOST_DESCRIBE_CLASS(Letters, (), (), (), (a, b, c));
};

class Example {
public:
  Numbers numbers;
  Letters letters;

  BOOST_DESCRIBE_CLASS(Example, (), (), (), (numbers, letters));
};

#endif
