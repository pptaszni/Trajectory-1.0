
using namespace std;

#ifndef DATASTRUCTURES
#define DATASTRUCTURES

#include <iostream>
#include <cstdio>
#include <string>
#include <list>
#include <vector>
#include <cmath>

/*! \class Point
 *
 * \brief Point in 2D space
 *
 */
class Point{

public:

  double x;
  double y;

  Point( );
  Point( double x, double y );
  Point( const Point& obj );
  ~Point( );
  double Module();
  Point Normalize();

};

Point operator-(Point a, Point b);
Point operator+(Point a, Point b);
Point operator*(Point a, double m);
bool operator==(Point a, Point b);



class ExtendedPoint: public Point{

public:

  double g;
  double f;

  ExtendedPoint( );
  ExtendedPoint( double x, double y, double g, double f );
  ExtendedPoint( const ExtendedPoint& obj );
  ~ExtendedPoint( );
  ExtendedPoint operator=( const ExtendedPoint& b );

};

ostream & operator<< (ostream &out, const ExtendedPoint &p);

/*! \class Obstacle
 *
 * \brief Obstacle in 2D space
 *
 */
class Obstacle{

public:

  double x;
  double y;
  double radius;



  Obstacle( );
  Obstacle( double x, double y, double radius );
  ~Obstacle( );
  Point ToPoint( );

};



template< class Type > class SHeap{

  vector< Type > Tab;
  int Size;
  bool ( *Fnc )( Type *, Type * );
  void Swap( int, int );
  void FixUp( int);
  void FixDown( int );

public:

  SHeap( bool ( * )( Type *, Type * ) );

  void Add( Type );
  int Rmv( int );
  int Length( );
  void Show( );
  Type Root( );
  void Erase( );

};

//////////////////////////////////////////////////////////////////////////


template< class Type >SHeap< Type >::SHeap(bool( *f_Fnc )( Type *, Type * )){

  Size = 0;
  Fnc = f_Fnc;

}

template< class Type > void SHeap< Type >::Add( Type f_Obj ){

  Tab.push_back( f_Obj );
  Size = Tab.size();
  this->FixUp( Size -1 );


}

template< class Type > int SHeap< Type >::Rmv( int f_Pos ){

  if( f_Pos < 0 || f_Pos >= Size )
    return -1;
		
  Tab[ f_Pos ] = Tab[ Size - 1 ];
  Tab.pop_back();
  Size = Tab.size();
  this->FixDown( f_Pos );
  return 0;

}

template< class Type > int SHeap< Type >::Length( ){ return Size; }
template< class Type > Type SHeap< Type >::Root( ){ return Tab[ 0 ]; }
template< class Type > void SHeap< Type >::Swap( int f_P1, int f_P2 ){

  Type Tmp = Tab[ f_P1 ];
  Tab[ f_P1 ] = Tab[ f_P2 ];
  Tab[ f_P2 ] = Tmp;

}

template< class Type > void SHeap< Type >::Show( ){

  int i = 0;

  for( ; i < Size; i++ )
    cout << Tab[ i ];
		
  cout << endl;

}

template< class Type > void SHeap< Type >::FixUp( int f_Pos ){

  int Parent;

  while( f_Pos > 0 ){

    Parent = ((f_Pos+1) >> 1) - 1;
    if( ( *Fnc )( &Tab[ f_Pos ], &Tab[ Parent ] ) )
      this->Swap( Parent, f_Pos );
    else break;

    f_Pos = Parent;

  }
}

template< class Type > void SHeap< Type >::FixDown( int f_Pos ){

  int ChPos;

  while( f_Pos < Size ){

    ChPos = 2 * f_Pos + 1;
    if( ChPos >= Size )
      break;
    else{

      if( ChPos + 1 < Size ){
	if( !( *Fnc )( &Tab[ ChPos ], &Tab[ ChPos + 1 ] ) )
	  ++ChPos;
      }
    }
		
    if( !( *Fnc )( &Tab[ f_Pos ], &Tab[ ChPos ] ) )
      this->Swap( ChPos, f_Pos );
    else
      break;
	
    f_Pos = ChPos;

  }
}

template< class Type > void SHeap< Type >::Erase( ){

  Tab.erase(Tab.begin(),Tab.end());

}


#endif
