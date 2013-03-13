/*!
 * \file main.cpp
 * \author Pawel Ptasznik
 *
 * \mainpage About
 *
 * Last modified : 07.02.2013
 * 
 * \author Pawel Ptasznik
 * \version 1.0
 *
 * This is a partial software for Autonomous Car that provides trajectory
 * reference and calculates the controll outputs for engine and steering
 * wheel.
 *
 *
 * \section _options Options
 *
 * Features:
 *
 * - feature ...
 * 
 *
 */

#include "Controller.hh"
#include "TrajectoryBuilder.hh"


int main(int argc, char** argv){

  string data, save;

  if( argc == 2 ){

    data = argv[ 1 ];
    save = "data/Trajectory.xy";;

  }
  else if( argc == 3 ){

    data = argv[ 1 ];
    save = argv[ 2 ];

  }
  else{

    data = "data/Data2.dat";
    save = "data/Trajectory.xy";

  }


  TrajectoryBuilder TrajBuild( data );
  TrajBuild.Run();
  TrajBuild.Save( save );




  return 0;

}
