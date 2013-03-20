
#include "DataStructures.hh"

using namespace std;


///////////////////////////////////////////////////////////////////////

Point::Point( ){ x=0; y=0; }
Point::Point( double x, double y ){

  this->x = x;
  this->y = y;

}

Point::Point( const Point& obj ){

  this->x = obj.x;
  this->y = obj.y;

}

Point::~Point( ){ }

double Point::Module(){

  return sqrt(x*x + y*y);

}

Point Point::Normalize(){

  Point a;
  if( this->Module() != 0 ){
    a.x = this->x/this->Module();
    a.y = this->y/this->Module();
  }
  return a;

}


///////////////////////////////////////////////////////////////////////


ExtendedPoint::ExtendedPoint( ): Point() { g=0; f=0; }

ExtendedPoint::ExtendedPoint( double x, double y, double g, double f ): Point(x,y) {

  this->g = g;
  this->f = f;

}

ExtendedPoint::ExtendedPoint( const ExtendedPoint& obj ):
  Point( static_cast<Point>(obj) ) {

  this->g = obj.g;
  this->f = obj.f;

}

ExtendedPoint::~ExtendedPoint( ){ 

}

ExtendedPoint ExtendedPoint::operator=( const ExtendedPoint& obj ){

  this->x = obj.x;
  this->y = obj.y;
  this->g = obj.g;
  this->f = obj.f;

  return *this;

}


Point operator-(Point a, Point b){

  Point c;
  c.x = a.x - b.x;
  c.y = a.y - b.y;
  return c;

}

Point operator+(Point a, Point b){

  Point c;
  c.x = a.x + b.x;
  c.y = a.y + b.y;
  return c;

}

Point operator*(Point a, double m){

  Point b;
  b.x = a.x*m;
  b.y = a.y*m;
  return b;

}

bool operator==(Point a, Point b){

  if( (a.x == b.x) && (a.y == b.y) ) return true;
  else return false;

}


Obstacle::Obstacle( ){ x=0; y=0; radius = 0; }
Obstacle::Obstacle( double x, double y, double radius ){

  this->x = x;
  this->y = y;
  this->radius = radius;

}
Obstacle::~Obstacle( ){ }

Point Obstacle::ToPoint( ){

  Point a;
  a.x = this->x;
  a.y = this->y;
  return a;

}

ostream & operator<< (ostream &out, const ExtendedPoint &p){

  out << "(" << p.x << "," << p.y << "," << p.g << "," << p.f << ") ";
  return out;

}
