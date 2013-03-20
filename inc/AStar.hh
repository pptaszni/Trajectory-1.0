
#include "DataStructures.hh"


class AStar{

  unsigned char ** Map;
  SHeap< ExtendedPoint > OpenList;
  int Rows;
  int Cols;
  ExtendedPoint StartPoint;
  ExtendedPoint Goal;


  static bool min(ExtendedPoint* p1, ExtendedPoint* p2);

public:

  AStar();
  AStar( string DataFileName );
  ~AStar();
  void ShowMap();
  int DetermineDir( int i, int j );
  Point ReverseDir( int x );
  double Heuristic( ExtendedPoint p );
  void AddNeighbours( ExtendedPoint p);
  void Run();

};
