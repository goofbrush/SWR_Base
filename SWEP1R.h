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
      int lastLap = 0;


      waitForCountdown(); // Blocks until the race coundown starts

      while(inRace()) {

        if(load) { // Loading info that wont change during the race
          updateRaceInfo(); // Updates the track and number of laps
          loadLevel(); // Creates a record and prints race info
          load = false;
        }

        updateRaceData(); // Updates lap, timer and comp

        printProgress(&lastLap); // Prints progress bars

        waitForTimer(); // Blocks until timer changes

      }
      if(!load && (CurrentLap>TotalLaps)) { // If race was completed, print final results
        updateRaceData(true); // Get accurate last lap time and final lap time
        printFinalLap(); // Print finalised last lap and cumlative timer
      }

    }


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

protected:
  void waitForTimer() { float newTime; // Blocks until timer updates
    do { newTime = mem.readValue<float>(Values::LapTotal);
    } while(TotalTimer == newTime && inRace());
  }
  void waitForCountdown() { // Blocks until the coundown starts or the race has already begun
    while(mem.readValueFromPointer<float>(Values::TimerPointer, false, Values::Timer) < 0){}
  }

  void updateRaceInfo() { // Collects static race data
    CurrentTrack = mem.readValueFromPointer<BYTE>(Values::TrackPointer, true, Values::Track);
    TotalLaps = mem.readValueFromPointer<BYTE>(Values::RaceStuffPointer, true, Values::LapNum) - 1;
  }
  void updateRaceData(bool raceFinished = false) { // Collects updating race data
    CurrentLap = mem.readValue<BYTE>(Values::CurrentLap - raceFinished, true); // If race finished, then get last lap time
    CurrentLapTimer = mem.readValue<float>(Values::Laps[CurrentLap]);
    TotalTimer = mem.readValue<float>(Values::LapTotal);
    MaxProgress = mem.readValueFromPointer<float>(Values::RaceInfoPointer, true, Values::MaxProgress);
  }

  bool inRace() { // Returns true if in race
    return mem.readValue<BYTE>(Values::RaceStatus, true);
  }

private:
  Memory mem = Memory("Episode I Racer", "SWEP1RCR.EXE");

  Record rec,play;

  bool Recording: 1;
  bool PlayBack : 1;
  const char* TF[2] = { "False", "True" };

  BYTE CurrentTrack;
  BYTE CurrentLap, TotalLaps;
  float CurrentLapTimer, TotalTimer;
  float MaxProgress;

  uintptr_t Pointer;
  uintptr_t LapProgress, PodX, PodY, PodZ;

  void loadLevel() {
    rec = Record(CurrentTrack, TotalLaps); // Creates a new record
    if(PlayBack) { play = Record(); play.load(); }
    Pointer = mem.readPointer(Values::RaceInfoPointer, true);
      LapProgress = Pointer+Values::LapProgress;
      PodX        = Pointer+Values::PodX;
      PodY        = Pointer+Values::PodY;
      PodZ        = Pointer+Values::PodZ;

      std::cout << std::endl << "________________________" << std::endl;
      std::cout << "Track: " << Values::TrackNames[CurrentTrack] << std::endl;
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
    std::cout << "] " << int(progress * 100.0) << " % " << lapTime << "         ";
  }

  void printProgress(int* lastLap) {
    bool nextLap = (*lastLap!=CurrentLap);

    if((CurrentLap>=0) && (CurrentLap <= TotalLaps)) {

      float pBar, lapTime;
      if(nextLap){
        lapTime = mem.readValue<float>(Values::Laps[CurrentLap-1]);
        pBar = 1;
      }
      else {
        lapTime = CurrentLapTimer;
        pBar = MaxProgress;
      }

      printBar(pBar, lapTime);

      if (nextLap)
        { *lastLap = CurrentLap; std::cout << std::endl; }
    }
  }

  void printFinalLap() {
    printBar(1, CurrentLapTimer);
    std::cout << std::endl << "Total: " << TotalTimer;
  }

};
