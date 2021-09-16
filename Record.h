#pragma once

#include <iostream>

#include <fstream>
#include <dirent.h>

#include <list>

using BYTE = unsigned char;


static struct
{
//Offset Addresses
    uintptr_t RaceStatus = 0x000EB1E0; // Byte
    uintptr_t PlayerPosition = 0x00A29C1C; // Byte

    uintptr_t Paused = 0x0010C5F0; // Byte
    uintptr_t RaceMenuIndex = 0x0010C078; // Byte

    uintptr_t TimerPointer = 0x004BFDE0; // Pointer
      uintptr_t Timer = 0x0000000C; // Float

    uintptr_t RaceInfoPointer = 0x000D78A8; // Pointer
      uintptr_t LapProgress = 0x000000E0; // Float
      uintptr_t MaxProgress = 0x000000E8; // Float
      uintptr_t PodX = 0x00000050; // Float
      uintptr_t PodY = 0x00000054; // Float
      uintptr_t PodZ = 0x00000058; // Float
      uintptr_t OOB = 0x000002C8; // Float


    uintptr_t CurrentLap = 0x00A29C38; // Byte
    uintptr_t RaceStuffPointer = 0x000BFDB8; // Pointer
      uintptr_t LapNum = 0x8F; // Byte
      uintptr_t Racer = 0x73; // Byte

    uintptr_t PodHeatPointer = 0xA29C44; // Pointer
      uintptr_t PodHeat = 0x00000218; // Float


//13C IS POINTER
//60-67 8BIT
//2A0-2B4 4BIT
      uintptr_t PodInfo[184] { 0x0, 0x4, 0x8, 0xC, 0x10, 0x14, 0x18, 0x1C, 0x20, 0x24, 0x28, 0x30, 0x34, 0x38, 0x40, 0x44, 0x48, 0x50, 0x54, 0x58,
        0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
        0x68, 0x6C, 0x70, 0x74, 0x78, 0x7C, 0x80, 0x84, 0x88, 0x8C, 0x90, 0x94, 0x98, 0x9C,
        0xA0, 0xA4, 0xA8, 0xAC, 0xB0, 0xB4, 0xB8, 0xBC, 0xC0, 0xC4, 0xC8, 0xCC, 0xD0, 0xD4, 0xD8, 0xDC, 0xE0, 0xE4, 0xE8, 0xEC, 0xF0, 0xF4, 0xF8,
        0xFC, 0x100, 0x104, 0x108, 0x10C, 0x110, 0x114, 0x13C, 0x140, 0x144, 0x148, 0x14C, 0x150, 0x154, 0x158, 0x15C, 0x160, 0x164, 0x168, 0x16C,
        0x170, 0x174, 0x178, 0x17C, 0x184, 0x188, 0x18C, 0x190, 0x194, 0x198, 0x19C, 0x1A0, 0x1A4, 0x1A8, 0x1AC, 0x1B0, 0x1B4, 0x1B8, 0x1BC,
        0x1C0, 0x1C4, 0x1C8, 0x1CC, 0x1D0, 0x1D4, 0x1D8, 0x1DC, 0x1E0, 0x1E4, 0x1E8, 0x1EC, 0x1F0, 0x1F4, 0x1F8, 0x1FC, 0x200, 0x204, 0x208, 0x20C,
        0x210, 0x214, 0x218, 0x21C, 0x220, 0x224, 0x228, 0x22C, 0x230, 0x234, 0x238, 0x23C, 0x240, 0x244, 0x248, 0x24C, 0x250, 0x254, 0x258, 0x25C,
        0x260, 0x264, 0x268, 0x26C, 0x270, 0x274, 0x278, 0x27C, 0x280, 0x284, 0x288, 0x28C, 0x290, 0x294, 0x298, 0x29C, 0x250,
        0x2A0, 0x2A4, 0x2A8, 0x2AC, 0x2B0, 0x2B4, 0x2B8, 0x2BC, 0x2C0, 0x2C4, 0x2C8, 0x2CC,
        0x2D0, 0x2D4, 0x2E4, 0x2E8, 0x2EC, 0x2FC, 0x30C, 0x5D0, 0x1998, 0x1E70, 0x1EC8 };

    uintptr_t TrackPointer = 0x000BFDB8; // Pointer
      uintptr_t Track = 0x0000005D; // Byte

  // End


  // Static Addresses
    uintptr_t ProgressPointer = 0x00E29C44; // Pointer

    uintptr_t Lap1 = 0x00E29C20; // Float
    uintptr_t Lap2 = 0x00E29C24; // Float
    uintptr_t Lap3 = 0x00E29C28; // Float
    uintptr_t Lap4 = 0x00E29C2C; // Float
    uintptr_t Lap5 = 0x00E29C30; // Float
    uintptr_t LapTotal = 0x00E29C34; // Float
    uintptr_t Laps[5] { Lap1,Lap2,Lap3,Lap4,Lap5 }; // Lookup



    uintptr_t Track2 = 0xEA02B0; // Byte
    std::string TrackNames[25]{ // Lookup Table
      "BTC","BEC",
      "BWR","HG","AMR","APC",
      "AQC","SC","BB",
      "SR","DR","ABY",
      "BC","GVG","FMR","INF",
      "MGS","SMR","ZC",
      "VEN","EXE","TGT",
      "M100","DD","SL"
    };

    std::string RacerNames[23]{ // Lookup Table
        "Anakin", "Teempto", "Sebulba", "Ratts", "Aldar", "Mawhonic", "Ark",
        "Wan", "Mars", "Ebe", "Dud", "Gasgano", "Clegg", "Elan", "Neva", "Bozzie",
        "Boles", "Ody", "Fud", "Ben", "Slide", "Toy", "Bullseye"
    };
//End

} Values;


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
  Record(BYTE InputTrack, BYTE LapCount) { Track = InputTrack; Laps = LapCount; }

  void addPoint(DataPoint D) {
    Data.push_back(D);
  }

  void save() {
    FinalTime = Data.back().Timer;

    std::ofstream myfile;
    myfile.open(Values.TrackNames[Track]+"/"+std::to_string(FinalTime)+".txt");
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
  BYTE Laps;



  std::string getBestTime() {
    DIR *dir = opendir( (Values.TrackNames[Track]+"/").c_str() );
    readdir(dir);readdir(dir);

    std::string best = Values.TrackNames[Track]+"/"+readdir(dir)->d_name;

    closedir(dir);
    return best;
  }

};






