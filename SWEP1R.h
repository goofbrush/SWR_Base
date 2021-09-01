#include "WinMem/Memory.h"
#include "Record.h"

#include <dirent.h>
#include <vector>
#include <list>


using PTR = uintptr_t;
using BYTE = unsigned char;




class SW
{
public:

  SW() { Recording = false; PlayBack = false; }

// Record2 R = Record2();



  void start() {

    while(true) {

      bool load = true;
      float p = 0;

      int lap = 0;
      BYTE lapCount = 0;

      while(mem.readValue<float>(Values::LapTotal) != 0) {  }

      while(inRace()) {

        if(load) {
          BYTE track = mem.readValueFromPointer<BYTE>(Values::TrackPointer, true, Values::Track);
          lapCount = mem.readValueFromPointer<BYTE>(Values::RaceStuffPointer, true, Values::LapNum);
          loadLevel(track, lapCount); load = false;
        }

        lap = mem.readValue<int>(Values::CurrentLap, true);

        if((lap>=0) && (lap <= lapCount-1)) {
          printProgress(&p, lap);
        }

      }
      if(!load) {
        float lapTime = mem.readValue<float>(Values::Laps[lapCount-1]);
        float totalTime = mem.readValue<float>(Values::LapTotal);
        printBar(1, lapTime); std::cout << std::endl << "Total: " << totalTime;
      }

    }
    return;

    // Record::DataPoint2 D = {
    //
    // };


//     while(true) {
//       bool load = true;
//       if(!mem.checkValidity()) { return; }
//
//       BYTE Track = mem.readValueFromPointer<BYTE>(Values::TrackPointer, true, Values::Track);
//       // std::cout << Values::TrackNames[Track] << std::endl;
// // float temp;
//       while(mem.readValue<BYTE>(Values::RaceStatus,true)) { // Checks if in race
//         if(load) { loadLevel(Track); load = false; }
//         if(!mem.checkValidity()) { return; }
//
//         float timer = mem.readValue<float>(Values::LapTotal);
//
//
//         if(Recording && (timer >= 0)) {
//           Record::DataPoint D = {
//             timer, mem.readValue<float>(LapProgress),
//             mem.readValue<float>(PodX),mem.readValue<float>(PodY),mem.readValue<float>(PodZ),
//             5,6,7
//           };
//           rec.addPoint(D);
//         }
//
//         if(PlayBack) {
//           // Write Data
//         }
//
//         while(mem.readValue<float>(Values::LapTotal) == timer) { // Waits for the timer to tick
//           if(!mem.readValue<BYTE>(Values::RaceStatus,true)) { break; } // Breaks if no longer in race
//         }
//       }
//
//       if(!load) {
//         rec.print();
//         if(Recording) { rec.save(); }
//       }
//
//     }
  }

  void setRecordState(bool record, bool playback) { Recording = record; PlayBack = playback; }

  bool inRace() { // If RaceStatus is 1 then in race, but it initalises as 1 so also need to check PlayerPosition
    // PlayerPosition is only ever 0 upon initilisation, and is set when in race
    return mem.readValue<BYTE>(Values::RaceStatus, true) && mem.readValue<BYTE>(Values::PlayerPosition, true);
  }

private:
  Memory mem = Memory("Episode I Racer", "SWEP1RCR.EXE");

  Record rec,play;

  bool Recording: 1;
  bool PlayBack : 1;
  const char* TF[2] = { "False", "True" };

  uintptr_t Pointer;
  uintptr_t LapProgress, PodX, PodY, PodZ;

  void loadLevel(BYTE Track, BYTE LapCount) {
    rec = Record(Track, LapCount); // Creates a new record
    if(PlayBack) { play = Record(); play.load(); }
    Pointer = mem.readPointer(Values::RaceInfoPointer, true);
      LapProgress = Pointer+Values::LapProgress;
      PodX        = Pointer+Values::PodX;
      PodY        = Pointer+Values::PodY;
      PodZ        = Pointer+Values::PodZ;

      std::cout << std::endl << "________________________" << std::endl;
      std::cout << "Track: " << Values::TrackNames[Track] << std::endl;
      std::cout << "Recording: " << TF[Recording] << std::endl;
      std::cout << "Playback: " << TF[PlayBack] << std::endl;
  }

  void printBar(float progress, float lapTime) {
    std::cout << "\r";
    std::cout.flush();

    std::cout << "[";
    for (int i = 0; i < 10; ++i) {
        if (i <= progress*10) std::cout << "|";
        else std::cout << "-";
    }
    std::cout << "] " << int(progress * 100.0) << " % " << lapTime << "                     ";
  }

  void printProgress(float* lastProgress, int lap) {

    float progress = mem.readValueFromPointer<float>(Values::RaceInfoPointer, true, Values::MaxProgress);
    bool lapPassed = (*lastProgress>progress);
    float pBar = lapPassed? 1 : progress;

    float lapTime = mem.readValue<float>(Values::Laps[lap-lapPassed]);

    printBar(pBar, lapTime);

    if(lapPassed) { std::cout << std::endl; }
    *lastProgress = progress;
  }
};
