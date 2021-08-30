#include "WinMem/Memory.h"
#include "Record.h"

#include <dirent.h>
#include <vector>
#include <list>
#include <fstream>

using PTR = uintptr_t;
using BYTE = unsigned char;
// record mode / playback mode
// get level info
// get/set xyz rpy and timer


class Record
{
public:
  struct DataPoint
  {
    friend std::ifstream& operator >> (std::ifstream& in, DataPoint &D) {
      in >> D.Timer >> D.Completion;
      in >> D.X >> D.Y >> D.Z;
      in >> D.Yaw >> D.Pitch >> D.Roll;
      return in;
    }
    friend std::ofstream& operator << (std::ofstream& in, DataPoint &D) {
      in << D.Timer << " " << D.Completion << " ";
      in << D.X << " " << D.Y << " " << D.Z << " ";
      in << D.Yaw << " " << D.Pitch << " " << D.Roll << " ";
      return in;
    }


    float Timer;
    float Completion;
    float X, Y, Z;
    float Yaw, Pitch, Roll; //
  };

  Record(){}
  Record(BYTE InputTrack) { Track = InputTrack; }

  void addPoint(DataPoint D) {
    Data.push_back(D);
  }

  void save() {
    FinalTime = Data.back().Timer;

    std::ofstream myfile;
    myfile.open(Values::TrackNames[Track]+"/"+std::to_string(FinalTime)+".txt");
    for (std::list<DataPoint>::iterator it = Data.begin(); it != Data.end(); ++it){
      myfile << *it;
    }
    myfile.close();
  }

  void load() {
    Data.clear();

    std::ifstream myfile;
    myfile.open(getBestTime());
    while(myfile && myfile.peek() != EOF) {
      DataPoint* D = new DataPoint();
      myfile >> *D;
      Data.push_back(*D);
    }
    myfile.close();
  }

  float getFinalTime() { return FinalTime; }

  void print() {
    for (std::list<DataPoint>::iterator it = Data.begin(); it != Data.end(); ++it){
      std::cout << it->Timer << " | " << it->Completion << " | " << it->X << "," << it->Y << "," << it->Z << std::endl;
    }
  }

private:
  std::list<DataPoint> Data;
  float FinalTime;
  BYTE Track;



  std::string getBestTime() {
    DIR *dir = opendir( (Values::TrackNames[Track]+"/").c_str() );
    readdir(dir);readdir(dir);

    std::string best = Values::TrackNames[Track]+"/"+readdir(dir)->d_name;

    closedir(dir);
    return best;
  }

};













class SW
{
public:

  SW() { Recording = false; PlayBack = false; }

Record2 R = Record2();
  void start() {
    while(!mem.readValue<BYTE>(Values::RaceStatus,true)) {



      // BYTE Track = mem.readValueFromPointer<BYTE>(Values::TrackPointer, true, Values::Track);
      // uintptr_t P = mem.readPointer<float>(mem.getAddress(Values::RaceInfoPointer+true));
      // BYTE Track = mem.readValue<BYTE>(mem.getAddress(P+Values::Track));

      // uintptr_t Pointer = readPointer<float>(getAddress(Addr, OffsetByBase));
      // return readValue<Type>(getAddress(Pointer+LocalOffset));

      // std::cout << (LPVOID)P << std::endl;
      // mem.writeValueToPointer<float>(Values::RaceInfoPointer, 2.9, true, Values::OOB);
      // mem.writeValueToPointer<float>(Values::RaceInfoPointer, 1200, true, Values::PodZ);
      // float oobTime = mem.readValueFromPointer<float>(Values::RaceInfoPointer, true, Values::OOB);

      // std::cout << oobTime  << std::endl;
    }
    Sleep(4000);
    // Record::DataPoint2 D = {
    //
    // };
    return;

    while(true) {
      bool load = true;
      if(!mem.checkValidity()) { return; }

      BYTE Track = mem.readValueFromPointer<BYTE>(Values::TrackPointer, true, Values::Track);
      // std::cout << Values::TrackNames[Track] << std::endl;
// float temp;
      while(mem.readValue<BYTE>(Values::RaceStatus,true)) { // Checks if in race
        if(load) { loadLevel(Track); load = false; }
        if(!mem.checkValidity()) { return; }

        float timer = mem.readValue<float>(Values::LapTotal);


        if(Recording && (timer >= 0)) {
          Record::DataPoint D = {
            timer, mem.readValue<float>(LapProgress),
            mem.readValue<float>(PodX),mem.readValue<float>(PodY),mem.readValue<float>(PodZ),
            5,6,7
          };
          rec.addPoint(D);
        }

        if(PlayBack) {
          // Write Data
        }

        while(mem.readValue<float>(Values::LapTotal) == timer) { // Waits for the timer to tick
          if(!mem.readValue<BYTE>(Values::RaceStatus,true)) { break; } // Breaks if no longer in race
        }
      }

      if(!load) {
        rec.print();
        if(Recording) { rec.save(); }
      }

    }
  }

  void setRecordState(bool record, bool playback) { Recording = record; PlayBack = playback; }

private:
  Memory mem = Memory("Episode I Racer", "SWEP1RCR.EXE");

  Record rec;
  Record play;

  bool Recording: 1;
  bool PlayBack : 1;
  const char* TF[2] = { "False", "True" };

  uintptr_t Pointer;
  uintptr_t LapProgress, PodX, PodY, PodZ;

  void loadLevel(BYTE Track) {
    rec = Record(Track); // Creates a new record
    if(PlayBack) { play = Record(Track); play.load(); }
    Pointer = mem.readPointer<float>(Values::RaceInfoPointer, true);
      LapProgress = Pointer+Values::LapProgress;
      PodX        = Pointer+Values::PodX;
      PodY        = Pointer+Values::PodY;
      PodZ        = Pointer+Values::PodZ;

      std::cout << "Track: " << Values::TrackNames[Track] << std::endl;
      std::cout << "Recording: " << TF[Recording] << std::endl;
      std::cout << "Playback: " << TF[PlayBack] << std::endl;
  }
};
