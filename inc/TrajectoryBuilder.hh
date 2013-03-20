/*! \file TrajectoryBuilder.hh
 *
 * \brief Deklaracja klasy TrajectoryBuilder
 *
 */

using namespace std;

#ifndef TRAJECTORYBUILDER
#define TRAJECTORYBUILDER


#include "DataStructures.hh"



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
