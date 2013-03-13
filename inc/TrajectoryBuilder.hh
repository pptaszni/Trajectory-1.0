/*! \file TrajectoryBuilder.hh
 *
 * \brief Deklaracja klasy TrajectoryBuilder
 *
 */

using namespace std;

#ifndef TRAJECTORYBUILDER
#define TRAJECTORYBUILDER

#include <iostream>
#include <cstdio>
#include <string>
#include <list>
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

/*! \class TrajectoryBuilder TrajectoryBuilder.hh "inc/TrajectoryBuilder.hh"
 * \brief TrajBuild brief desc
 *
 * More ....
 *
 *
 */
class TrajectoryBuilder{

  list<Point*> TrajectoryReference;
  list<Obstacle*> Obstacles;
  Point* Target;
  list<Point*> Trajectory;
  bool State;
  double StepSize;
  double Speed;


public:

  /*! \brief Initiates TrajBuild
   */
  TrajectoryBuilder( );
  /*! \brief Loads data from given file
   */
  TrajectoryBuilder( string data );
  TrajectoryBuilder( string pos, string obs, string targ );
  void Run();
  void RunStreet();
  void RunParking();
  void Save( string DataFileName );
  /*! \brief Destructs TrajBuild
   */
  ~TrajectoryBuilder( );


};



#endif
