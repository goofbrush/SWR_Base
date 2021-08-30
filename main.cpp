#include "SWEP1R.h"
#include <unistd.h>

//
// struct DataPoint
// {
//   friend std::ifstream& operator >> (std::ifstream& in, DataPoint &D) {
//     in << D.D.Timer >> D.Completion;
//     in << D.D.X; in << D.D.Y; in << D.D.Z;
//     in << D.D.Yaw; in << D.D.Pitch; in << D.D.Roll;
//     return in;
//   }
//   friend std::ofstream& operator << (std::ofstream& in, DataPoint &D) {
//     in << D.Timer << " " << D.Completion << " ";
//     in << D.X << " " << D.Y << " " << D.Z << " ";
//     in << D.Yaw << " " << D.Pitch << " " << D.Roll;
//     return in;
//   }
//
//   in << D.Timer;
//   in << D.Completion;
//   in << D.X, Y, Z;
//   in << D.Yaw, Pitch, Roll;
// };
//
// void save() {
//   DataPoint D{ 1.2f,2.0f, 3,4,5, 6,7,8 };
//
//   std::ofstream myfile;
//   myfile.open("hey.txt");
//
//   myfile << D;
//
//   myfile.close();
// }
// void save2() {
//   DataPoint D{ 0,0, 3,4,5, 6,7,8 };
//
//   std::ifstream myfile;
//   myfile.open("hey.txt");
//
//   while(myfile && myfile.peek() != EOF)
//   {
//     myfile >> D;
//   }
//
//
//   myfile.close();
//
//   std::cout << D.Completion;
// }
// std::string getBestTime() {
//   DIR *dir = opendir("/..");
//   readdir(dir);readdir(dir);
//
//   std::string best = readdir(dir)->d_name;
//
//   closedir(dir);
//   return best;
// }


int main()
{
  SW sw;
  sw.setRecordState(1,0);
  sw.start();

  // getBestTime();


}


// Time Spent of Fast Terrain
// Time Spent on Slow Terrain
// Underheat & Overheat Time
//
