// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 10           
// Controller1          controller                    
// IntakeMotors         motor_group   15, 16          
// IntakeElevationMotor motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
competition Competition;

// define your global instances of motors and other devices here

// some vars



// pre-autonomous functions
void pre_auton(void) 
{
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

// autonomous stuff
void autonomous(void) 
{
}


// driver control
void usercontrol(void) 
{
  while (1) 
  {
    // IntakeMotors
    if (Controller1.ButtonR1.pressing() == true)
    {
      IntakeMotors.spin(forward, 50, percent);
    }
    else if (Controller1.ButtonR2.pressing() == true)
    {
      IntakeMotors.spin(forward, 50, percent);
    }
    else
    {
      IntakeMotors.stop();
    }

    // IntakeElevation
    if (Controller1.ButtonL1.pressing() == true)
    {
      IntakeElevationMotor.spin(forward, 50, percent);
    }
    else if (Controller1.ButtonL2.pressing() == true)
    {
      IntakeElevationMotor.spin(forward, 50, percent);
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
  // Set up callbacks for autonomous and driver control periods.
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
