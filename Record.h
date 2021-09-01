
#include <iostream>

#include <fstream>
#include <dirent.h>

#include <list>

using BYTE = unsigned char;


namespace Values
{
  // Offset Addresses
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
      uintptr_t LapNum = 0x0000008F; // Byte


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



    //uintptr_t Track = 0x00EA02B; // Byte
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
  //End

};


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
  BYTE Laps;



  std::string getBestTime() {
    DIR *dir = opendir( (Values::TrackNames[Track]+"/").c_str() );
    readdir(dir);readdir(dir);

    std::string best = Values::TrackNames[Track]+"/"+readdir(dir)->d_name;

    closedir(dir);
    return best;
  }

};










struct DataPoint2
{

  friend std::ifstream& operator >> (std::ifstream& in, DataPoint2 &D) {
    in >> D.Four[4];

    in >> D.SpawnPointX;
    in >> D.SpawnPointY;
    in >> D.SpawnPointZ;

    in >> D.Fourteen;
    in >> D.Eightteen;
    in >> D.OneC;

    in >> D.RightVectorX;
    in >> D.RightVectorY;
    in >> D.RightVectorZ;
    in >> D.ForwardVectorX;
    in >> D.ForwardVectorY;
    in >> D.ForwardVectorZ;
    in >> D.UpVectorX;
    in >> D.UpVectorY;
    in >> D.UpVectorZ;
    in >> D.XPosition;
    in >> D.YPosition;
    in >> D.ZPosition;

    in >> D.Sixty;     // Bit Fields
    in >> D.SixtyOne;
    in >> D.SixtyTwo;
    in >> D.SixtyThree;
    in >> D.SixtyFour;
    in >> D.SixtyFive;
    in >> D.SixtySix;
    in >> D.SixtySeven;

    in >> D.SixtyEight[4];
    in >> D.antiskid;
    in >> D.turnResponse;
    in >> D.maxTurnRate;
    in >> D.acceleration;
    in >> D.maxSpeed;
    in >> D.airBreakInterval;
    in >> D.decelInterval;
    in >> D.boostThrust;
    in >> D.heatRate;
    in >> D.coolRate;
    in >> D.hoverHeight;
    in >> D.repairRate;
    in >> D.bumpMass;
    in >> D.damageImmunity;
    in >> D.isectRadius;

    in >> D.AEight;
    in >> D.AC[4];
    in >> D.B0[4];
    in >> D.ProgressAB;
    in >> D.BEight;
    in >> D.ProgressPointA[4];
    in >> D.ProgressPointB[4];
    in >> D.CFour[4];
    in >> D.CEight[4];
    in >> D.CC[4];
    in >> D.DZero[4];
    in >> D.DFour[4];
    in >> D.DEight[4];
    in >> D.DC[4];

    in >> D.LapProgress;
    in >> D.LapProgressLastFrame;
    in >> D.LapProgressMaxReached;

    in >> D.EC[4];
    in >> D.FZero[4];

    in >> D.FFour;
    in >> D.FEight;
    in >> D.FC;
    in >> D.OneZeroZero;
    in >> D.OneZeroFour;
    in >> D.OneZeroEight;
    in >> D.OneZeroC[4];
    in >> D.OneOneZero;
    in >> D.OneOneFour[4];

    in >> D.CollisionPointer[4]; // Pointerrrrr!!!!!!!

    in >> D.OneFourZero[4];  //
    in >> D.OneFourFour[4];  //
    in >> D.OneFourEight[4]; //
    in >> D.OneFourC[4];     //
    in >> D.OneFiveZero[4];  //
    in >> D.OneFiveFour;    //
    in >> D.OneFiveEight;   //
    in >> D.OneFiveC;       //

    in >> D.UpX;
    in >> D.UpY;
    in >> D.UpZ;
    in >> D.X;
    in >> D.Y;
    in >> D.Z;

    in >> D.OneSevenEight;//
    in >> D.OneSevenC;    //

    in >> D.GroundToPodInv;
    in >> D.GroundAltitude;
    in >> D.Thrust;
    in >> D.OneNineZero;
    in >> D.DownX;
    in >> D.DownY;
    in >> D.DownZ;
    in >> D.Speed;
    in >> D.SpeedValue;
    in >> D.BoostValue;
    in >> D.SpeedMultiplier;
    in >> D.GravityTotalSpeed;
    in >> D.GravityValue;

    in >> D.SpeedForceX;
    in >> D.SpeedForceY;
    in >> D.SpeedForceZ;
    in >> D.SlopeForceX;
    in >> D.SlopeForceY;
    in >> D.SlopeForceZ;
    in >> D.CollisionForceX;
    in >> D.CollisionForceY;
    in >> D.CollisionForceZ;
    in >> D.OpponentCollisionForceX;
    in >> D.OpponentCollisionForceY;
    in >> D.OpponentCollisionForceZ;

    in >> D.CameraLeadWhenSliding;
    in >> D.TurnRate;
    in >> D.ProjectedTurnRate;
    in >> D.TurningModifier;

    in >> D.OneFEight;
    in >> D.OneFC;

    in >> D.EnginesRoll;
    in >> D.IndividualEngineRoll;
    in >> D.Tilt;

    in >> D.TwoZeroC;

    in >> D.BoostIndicatorStatus[4];
    in >> D.BoostChargeProgress;
    in >> D.EngineTemperature;

    in >> D.TwoOneC;
    in >> D.TwoTwoZero;
    in >> D.TwoTwoFour;
    in >> D.TwoTwoEight;

    in >> D.PodStatMultiplier;

    in >> D.TwoThreeZero;
    in >> D.TwoThreeFour;
    in >> D.TwoThreeEight;
    in >> D.TwoThreeC;

    in >> D.FastTerrainOffset;
    in >> D.SlowTerrainMultiplier;
    in >> D.SlipTerrainSkidModifier;
    in >> D.SlideVariable;

    in >> D.TwoFiveZero;
    in >> D.TwoFiveFour[4];
    in >> D.TwoFiveEight;
    in >> D.TwoFiveC;
    in >> D.TwoSixZero;
    in >> D.TwoSixFour;
    in >> D.TwoSixEight;

    in >> D.LevelCollisionToggles[4];

    in >> D.LeftTopMostDamage;
    in >> D.LeftMidMostDamage;
    in >> D.LeftBotMostDamage;
    in >> D.RightTopMostDamage;
    in >> D.RightMidMostDamage;
    in >> D.RightBotMostDamage;

    in >> D.LeftTopEngineDamage;
    in >> D.LeftMidEngineDamage;
    in >> D.LeftBotEngineDamage;
    in >> D.RightTopEngineDamage;
    in >> D.RightMidEngineDamage;
    in >> D.RightBotEngineDamage;

    // in >> D.LT : 5; // BitField Engine Flags
    // in >> D.LM : 5;
    // in >> D.LB : 5;
    // in >> D.RT : 5;
    // in >> D.RM : 5;
    // in >> D.RB : 5;

    in >> D.Rumble;
    in >> D.RepairTimer;
    in >> D.DamageWarning;
    in >> D.TotalDamage;
    in >> D.OOBTimer;

    in >> D.TwoCC;
    in >> D.TwoDZero;
    in >> D.TwoDFour;

    in >> D.TurnInput;

    in >> D.TwoEEight;
    in >> D.TwoEC;

    in >> D.Pitch;
    in >> D.RepsawnInvincibility;
    in >> D.SpinOut;

    // Some in >> D.Here?

    in >> D.convertToFloat;
    in >> D.PointerOne[4];
    in >> D.PointeTwo[4];
    return in;
  }
  friend std::ofstream& operator << (std::ofstream& in, DataPoint2 &D) {
    in << D.Four[4];

    in << D.SpawnPointX;
    in << D.SpawnPointY;
    in << D.SpawnPointZ;

    in << D.Fourteen;
    in << D.Eightteen;
    in << D.OneC;

    in << D.RightVectorX;
    in << D.RightVectorY;
    in << D.RightVectorZ;
    in << D.ForwardVectorX;
    in << D.ForwardVectorY;
    in << D.ForwardVectorZ;
    in << D.UpVectorX;
    in << D.UpVectorY;
    in << D.UpVectorZ;
    in << D.XPosition;
    in << D.YPosition;
    in << D.ZPosition;

    in << D.Sixty;     // Bit Fields
    in << D.SixtyOne;
    in << D.SixtyTwo;
    in << D.SixtyThree;
    in << D.SixtyFour;
    in << D.SixtyFive;
    in << D.SixtySix;
    in << D.SixtySeven;

    in << D.SixtyEight[4];
    in << D.antiskid;
    in << D.turnResponse;
    in << D.maxTurnRate;
    in << D.acceleration;
    in << D.maxSpeed;
    in << D.airBreakInterval;
    in << D.decelInterval;
    in << D.boostThrust;
    in << D.heatRate;
    in << D.coolRate;
    in << D.hoverHeight;
    in << D.repairRate;
    in << D.bumpMass;
    in << D.damageImmunity;
    in << D.isectRadius;

    in << D.AEight;
    in << D.AC[4];
    in << D.B0[4];
    in << D.ProgressAB;
    in << D.BEight;
    in << D.ProgressPointA[4];
    in << D.ProgressPointB[4];
    in << D.CFour[4];
    in << D.CEight[4];
    in << D.CC[4];
    in << D.DZero[4];
    in << D.DFour[4];
    in << D.DEight[4];
    in << D.DC[4];

    in << D.LapProgress;
    in << D.LapProgressLastFrame;
    in << D.LapProgressMaxReached;

    in << D.EC[4];
    in << D.FZero[4];

    in << D.FFour;
    in << D.FEight;
    in << D.FC;
    in << D.OneZeroZero;
    in << D.OneZeroFour;
    in << D.OneZeroEight;
    in << D.OneZeroC[4];
    in << D.OneOneZero;
    in << D.OneOneFour[4];

    in << D.CollisionPointer[4]; // Pointerrrrr!!!!!!!

    in << D.OneFourZero[4];  //
    in << D.OneFourFour[4];  //
    in << D.OneFourEight[4]; //
    in << D.OneFourC[4];     //
    in << D.OneFiveZero[4];  //
    in << D.OneFiveFour;    //
    in << D.OneFiveEight;   //
    in << D.OneFiveC;       //

    in << D.UpX;
    in << D.UpY;
    in << D.UpZ;
    in << D.X;
    in << D.Y;
    in << D.Z;

    in << D.OneSevenEight;//
    in << D.OneSevenC;    //

    in << D.GroundToPodInv;
    in << D.GroundAltitude;
    in << D.Thrust;
    in << D.OneNineZero;
    in << D.DownX;
    in << D.DownY;
    in << D.DownZ;
    in << D.Speed;
    in << D.SpeedValue;
    in << D.BoostValue;
    in << D.SpeedMultiplier;
    in << D.GravityTotalSpeed;
    in << D.GravityValue;

    in << D.SpeedForceX;
    in << D.SpeedForceY;
    in << D.SpeedForceZ;
    in << D.SlopeForceX;
    in << D.SlopeForceY;
    in << D.SlopeForceZ;
    in << D.CollisionForceX;
    in << D.CollisionForceY;
    in << D.CollisionForceZ;
    in << D.OpponentCollisionForceX;
    in << D.OpponentCollisionForceY;
    in << D.OpponentCollisionForceZ;

    in << D.CameraLeadWhenSliding;
    in << D.TurnRate;
    in << D.ProjectedTurnRate;
    in << D.TurningModifier;

    in << D.OneFEight;
    in << D.OneFC;

    in << D.EnginesRoll;
    in << D.IndividualEngineRoll;
    in << D.Tilt;

    in << D.TwoZeroC;

    in << D.BoostIndicatorStatus[4];
    in << D.BoostChargeProgress;
    in << D.EngineTemperature;

    in << D.TwoOneC;
    in << D.TwoTwoZero;
    in << D.TwoTwoFour;
    in << D.TwoTwoEight;

    in << D.PodStatMultiplier;

    in << D.TwoThreeZero;
    in << D.TwoThreeFour;
    in << D.TwoThreeEight;
    in << D.TwoThreeC;

    in << D.FastTerrainOffset;
    in << D.SlowTerrainMultiplier;
    in << D.SlipTerrainSkidModifier;
    in << D.SlideVariable;

    in << D.TwoFiveZero;
    in << D.TwoFiveFour[4];
    in << D.TwoFiveEight;
    in << D.TwoFiveC;
    in << D.TwoSixZero;
    in << D.TwoSixFour;
    in << D.TwoSixEight;

    in << D.LevelCollisionToggles[4];

    in << D.LeftTopMostDamage;
    in << D.LeftMidMostDamage;
    in << D.LeftBotMostDamage;
    in << D.RightTopMostDamage;
    in << D.RightMidMostDamage;
    in << D.RightBotMostDamage;

    in << D.LeftTopEngineDamage;
    in << D.LeftMidEngineDamage;
    in << D.LeftBotEngineDamage;
    in << D.RightTopEngineDamage;
    in << D.RightMidEngineDamage;
    in << D.RightBotEngineDamage;

    // in << D.LT : 5; // BitField Engine Flags
    // in << D.LM : 5;
    // in << D.LB : 5;
    // in << D.RT : 5;
    // in << D.RM : 5;
    // in << D.RB : 5;

    in << D.Rumble;
    in << D.RepairTimer;
    in << D.DamageWarning;
    in << D.TotalDamage;
    in << D.OOBTimer;

    in << D.TwoCC;
    in << D.TwoDZero;
    in << D.TwoDFour;

    in << D.TurnInput;

    in << D.TwoEEight;
    in << D.TwoEC;

    in << D.Pitch;
    in << D.RepsawnInvincibility;
    in << D.SpinOut;

    // Some in << D.Here?

    in << D.convertToFloat;
    in << D.PointerOne[4];
    in << D.PointeTwo[4];
    return in;
  }

  float Timer;
  float Completion;
  // float X, Y, Z;
  float Yaw,  Roll; // Pitch,

  BYTE PlayerBase[4];
  BYTE Four[4];

  float SpawnPointX;
  float SpawnPointY;
  float SpawnPointZ;

  float Fourteen;
  float Eightteen;
  float OneC;

  float RightVectorX;
  float RightVectorY;
  float RightVectorZ;
  float ForwardVectorX;
  float ForwardVectorY;
  float ForwardVectorZ;
  float UpVectorX;
  float UpVectorY;
  float UpVectorZ;
  float XPosition;
  float YPosition;
  float ZPosition;

  BYTE Sixty;     // Bit Fields
  BYTE SixtyOne;
  BYTE SixtyTwo;
  BYTE SixtyThree;
  BYTE SixtyFour;
  BYTE SixtyFive;
  BYTE SixtySix;
  BYTE SixtySeven;

  BYTE SixtyEight[4];
  float antiskid;
  float turnResponse;
  float maxTurnRate;
  float acceleration;
  float maxSpeed;
  float airBreakInterval;
  float decelInterval;
  float boostThrust;
  float heatRate;
  float coolRate;
  float hoverHeight;
  float repairRate;
  float bumpMass;
  float damageImmunity;
  float isectRadius;

  float AEight;
  BYTE AC[4];
  BYTE B0[4];
  float ProgressAB;
  float BEight;
  BYTE ProgressPointA[4];
  BYTE ProgressPointB[4];
  BYTE CFour[4];
  BYTE CEight[4];
  BYTE CC[4];
  BYTE DZero[4];
  BYTE DFour[4];
  BYTE DEight[4];
  BYTE DC[4];

  float LapProgress;
  float LapProgressLastFrame;
  float LapProgressMaxReached;

  BYTE EC[4];
  BYTE FZero[4];

  float FFour;
  float FEight;
  float FC;
  float OneZeroZero;
  float OneZeroFour;
  float OneZeroEight;
  BYTE OneZeroC[4];
  float OneOneZero;
  BYTE OneOneFour[4];

  BYTE CollisionPointer[4]; // Pointerrrrr!!!!!!!

  BYTE OneFourZero[4];  //
  BYTE OneFourFour[4];  //
  BYTE OneFourEight[4]; //
  BYTE OneFourC[4];     //
  BYTE OneFiveZero[4];  //
  float OneFiveFour;    //
  float OneFiveEight;   //
  float OneFiveC;       //

  float UpX;
  float UpY;
  float UpZ;
  float X;
  float Y;
  float Z;

  float OneSevenEight;//
  float OneSevenC;    //

  float GroundToPodInv;
  float GroundAltitude;
  float Thrust;
  float OneNineZero;
  float DownX;
  float DownY;
  float DownZ;
  float Speed;
  float SpeedValue;
  float BoostValue;
  float SpeedMultiplier;
  float GravityTotalSpeed;
  float GravityValue;

  float SpeedForceX;
  float SpeedForceY;
  float SpeedForceZ;
  float SlopeForceX;
  float SlopeForceY;
  float SlopeForceZ;
  float CollisionForceX;
  float CollisionForceY;
  float CollisionForceZ;
  float OpponentCollisionForceX;
  float OpponentCollisionForceY;
  float OpponentCollisionForceZ;

  float CameraLeadWhenSliding;
  float TurnRate;
  float ProjectedTurnRate;
  float TurningModifier;

  float OneFEight;
  float OneFC;

  float EnginesRoll;
  float IndividualEngineRoll;
  float Tilt;

  float TwoZeroC;

  BYTE BoostIndicatorStatus[4];
  float BoostChargeProgress;
  float EngineTemperature;

  float TwoOneC;
  float TwoTwoZero;
  float TwoTwoFour;
  float TwoTwoEight;

  float PodStatMultiplier;

  float TwoThreeZero;
  float TwoThreeFour;
  float TwoThreeEight;
  float TwoThreeC;

  float FastTerrainOffset;
  float SlowTerrainMultiplier;
  float SlipTerrainSkidModifier;
  float SlideVariable;

  float TwoFiveZero;
  BYTE TwoFiveFour[4];
  float TwoFiveEight;
  float TwoFiveC;
  float TwoSixZero;
  float TwoSixFour;
  float TwoSixEight;

  BYTE LevelCollisionToggles[4];

  float LeftTopMostDamage;
  float LeftMidMostDamage;
  float LeftBotMostDamage;
  float RightTopMostDamage;
  float RightMidMostDamage;
  float RightBotMostDamage;

  float LeftTopEngineDamage;
  float LeftMidEngineDamage;
  float LeftBotEngineDamage;
  float RightTopEngineDamage;
  float RightMidEngineDamage;
  float RightBotEngineDamage;

  unsigned int LT : 5; // BitField Engine Flags
  unsigned int LM : 5;
  unsigned int LB : 5;
  unsigned int RT : 5;
  unsigned int RM : 5;
  unsigned int RB : 5;

  float Rumble;
  float RepairTimer;
  float DamageWarning;
  float TotalDamage;
  float OOBTimer;

  float TwoCC;
  float TwoDZero;
  float TwoDFour;

  float TurnInput;

  float TwoEEight;
  float TwoEC;

  float Pitch;
  float RepsawnInvincibility;
  float SpinOut;

  // Some Float Here?

  BYTE convertToFloat[4]; // wtf is this
  BYTE PointerOne[4]; // Idk;
  BYTE PointeTwo[4]; // Idk either
};


class Record2
{
public:
  // Record(){}

  void addPoint(DataPoint2 D) {
    Data.push_back(D);
  }


  void print() {
    for (std::list<DataPoint2>::iterator it = Data.begin(); it != Data.end(); ++it){
      std::cout << it->LapProgress << std::endl;
    }
  }

private:
  std::list<DataPoint2> Data;


};
