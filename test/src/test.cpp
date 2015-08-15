#include <ndsp.h>
#include <ndspComplex.h>
#include <bandit/bandit.h>

using namespace bandit;

const ndsp::Real cAcceptableDelta = 0.06;

go_bandit( []()
{
  describe( "Complex class", []()
  {
    it( "should compare equality correctly", [&]()
    {
      ndsp::Complex a( 385.138, 468.001 );
      ndsp::Complex b( 385.138, 468.001 );
      bool r = ( a == b );
      AssertThat( r, Is().True() );

      a.real = -122.041;
      a.imaginary = -481.001;
      b.real = -122.041;
      b.imaginary = -481.001;
      r = ( a == b );
      AssertThat( r, Is().True() );

      a.real = -122.041;
      a.imaginary = -481.001;
      b.real = -122.042;
      b.imaginary = -481.001;
      r = ( a == b );
      AssertThat( r, Is().False() );
    } );
    it( "should do addition correctly", [&]()
    {
      ndsp::Complex a( 1.24, 5.76 );
      ndsp::Complex b( 8.43, 9.11 );
      auto c = a + b;
      AssertThat( c.real, Is().EqualToWithDelta( 9.67, cAcceptableDelta ) );
      AssertThat( c.imaginary, Is().EqualToWithDelta( 14.87, cAcceptableDelta ) );

      a.real = -5.71;
      a.imaginary = 43.11;
      b.real = 573.11;
      b.imaginary = -0.851;
      c = a + b;
      AssertThat( c.real, Is().EqualToWithDelta( 567.4, cAcceptableDelta ) );
      AssertThat( c.imaginary, Is().EqualToWithDelta( 42.259, cAcceptableDelta ) );
    } );
    it( "should do subtraction correctly", [&]()
    {
      ndsp::Complex a( 546.153, 93.133 );
      ndsp::Complex b( 999.999, 21.3466 );
      auto c = a - b;
      AssertThat( c.real, Is().EqualToWithDelta( -453.846, cAcceptableDelta ) );
      AssertThat( c.imaginary, Is().EqualToWithDelta( 71.7864, cAcceptableDelta ) );

      a.real = -4544.001;
      a.imaginary = 34763.44;
      b.real = 43634.1101;
      b.imaginary = -3455.1919;
      c = a - b;
      AssertThat( c.real, Is().EqualToWithDelta( -48178.1, cAcceptableDelta ) );
      AssertThat( c.imaginary, Is().EqualToWithDelta( 38218.6, cAcceptableDelta ) );
    } );
    it( "should do multiplication correctly", [&]()
    {
      ndsp::Complex a( 1.34, 3.01 );
      ndsp::Complex b( 0.63, 1.31 );
      auto c = a * b;
      AssertThat( c.real, Is().EqualToWithDelta( -3.0989, cAcceptableDelta ) );
      AssertThat( c.imaginary, Is().EqualToWithDelta( 3.6517, cAcceptableDelta ) );

      a.real = -3.11;
      a.imaginary = -1.01;
      b.real = 1.99;
      b.imaginary = -0.77;
      c = a * b;
      AssertThat( c.real, Is().EqualToWithDelta( -6.9666, cAcceptableDelta ) );
      AssertThat( c.imaginary, Is().EqualToWithDelta( 0.3848, cAcceptableDelta ) );
    } );
    it( "should do division correctly", [&]()
    {
      ndsp::Complex a( 6.34, 1.54 );
      ndsp::Complex b( 2.22, 2.00 );
      auto c = a / b;
      AssertThat( c.real, Is().EqualToWithDelta( 1.92137, cAcceptableDelta ) );
      AssertThat( c.imaginary, Is().EqualToWithDelta( -1.03727, cAcceptableDelta ) );
    } );
    it( "should negate correctly", [&]()
    {
      ndsp::Complex a( 6.23, 1.39 );
      auto b = -a;
      AssertThat( b.real, Is().EqualTo( -6.23 ) );
      AssertThat( b.imaginary, Is().EqualTo( -1.39 ) );
    } );
    it( "should get conjugate correctly", [&]()
    {
      ndsp::Complex a( 4.41, 9.51 );
      auto b = a.conjugate();
      AssertThat( b.real, Is().EqualTo( 4.41 ) );
      AssertThat( b.imaginary, Is().EqualTo( -9.51 ) );
    } );
    it( "should calculate magnitude correctly", [&]()
    {
      ndsp::Complex a( 1.242, 1.22 );
      auto b = a.magnitude();
      AssertThat( b, Is().EqualToWithDelta( 1.74097, cAcceptableDelta ) );
    } );
    it( "should calculate phase correctly", [&]()
    {
      ndsp::Complex a( 1.242, 1.41 );
      auto b = a.phase();
      AssertThat( b, Is().EqualToWithDelta( 0.848662, cAcceptableDelta ) );
    } );
  } );
} );

int main( int argc, char** argv )
{
  return bandit::run( argc, argv );
}