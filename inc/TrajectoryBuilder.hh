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
  ~Point( );


};

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
  list<Point*> Position;
  list<Obstacle*> Obstacles;
  Point* Target;


public:

  /*! \brief Initiates TrajBuild
   */
  TrajectoryBuilder( );
  /*! \brief Loads data from given file
   */
  TrajectoryBuilder( string pos, string obs, string targ );
  /*! \brief Destructs TrajBuild
   */
  ~TrajectoryBuilder( );

};



#endif
