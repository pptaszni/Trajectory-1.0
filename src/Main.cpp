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


int main(){

  string n1, n2, n3;
  n1 = "data/Position.xy";
  n2 = "data/Obstacles.xyr";
  n3 = "data/Target.xy";
  TrajectoryBuilder TrajBuild( n1, n2, n3);





  return 0;

}
