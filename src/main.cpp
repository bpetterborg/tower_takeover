#include "vex.h"
#include "stdlib.h"
#include <sstream>

using namespace vex;
competition Competition;

// define your global instances of motors and other devices here

// some vars
double intakeMotorsSpeed = 50;
double intakeTiltMotorSpeed = 50;

std::string drivetrainVoltage = std::to_string(Drivetrain.voltage()) + " V";

// pre-autonomous functions
void pre_auton(void) 
{
  vexcodeInit();
  Brain.Screen.clearScreen();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

// autonomous stuff
void autonomous(void) 
{
  Brain.Screen.clearScreen();
  Brain.Screen.print("Begin Autonomous...");
 
  Drivetrain.driveFor(forward, 700, mm);
  IntakeMotors.spin(forward, intakeMotorsSpeed, percent);
  Drivetrain.driveFor(forward, 400, mm);
  IntakeMotors.stop();

  Brain.Screen.print("End Autonomous");  
}



// driver control
void usercontrol(void) 
{
  Brain.Screen.print("Begin Usercontrol");
  Brain.Screen.clearScreen();

  while (1) 
  { 
    Brain.Screen.clearScreen();
    Brain.Screen.print(drivetrainVoltage);
    



    // IntakeMotors
    if (Controller1.ButtonR1.pressing() == true)
    {
      IntakeMotors.spin(forward, intakeMotorsSpeed, percent);
      
    }
    else if (Controller1.ButtonR2.pressing() == true)
    {
      IntakeMotors.spin(forward, -intakeMotorsSpeed, percent);
    }
    else
    {
      IntakeMotors.stop();
    }

    // IntakeElevation
    if (Controller1.ButtonL1.pressing() == true)
    {
      IntakeElevationMotor.spin(forward, intakeTiltMotorSpeed, percent);
    }
    else if (Controller1.ButtonL2.pressing() == true)
    {
      IntakeElevationMotor.spin(forward, -intakeMotorsSpeed, percent);
    }
    else
    {
      IntakeElevationMotor.stop();
    }

    // main exec loop
    wait(20, msec);
  }
}


int main() 
{
  // set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // run the pre-autonomous function.
  pre_auton();

  // prevent main from exiting with an infinite loop.
  while (true) 
  {
    wait(100, msec);
  }
}
