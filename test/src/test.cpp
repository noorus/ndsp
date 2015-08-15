#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <bandit/bandit.h>

using namespace bandit;

go_bandit( [](){
  describe( "poop:", [](){
    it( "is awesome", [&](){
      AssertThat( 1, Is().EqualTo( 1 ) );
    } );
  } );
} );

int main( int argc, char** argv )
{
  return bandit::run( argc, argv );
}