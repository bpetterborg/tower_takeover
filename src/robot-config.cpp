#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain  Brain;

// VEXcode device constructors
motor LeftDriveSmart = motor(PORT1, ratio18_1, false);
motor RightDriveSmart = motor(PORT10, ratio18_1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 320, 240, mm, 1);

controller Controller1 = controller(primary);

motor IntakeMotorsMotorA = motor(PORT15, ratio18_1, true);
motor IntakeMotorsMotorB = motor(PORT16, ratio18_1, false);

motor_group IntakeMotors = motor_group(IntakeMotorsMotorA, IntakeMotorsMotorB);

motor IntakeElevationMotor = motor(PORT2, ratio18_1, false);

bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;




// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() 
{
  while(true) 
  {
    if (RemoteControlCodeEnabled) 
    {
      int drivetrainLeftSideSpeed = Controller1.Axis3.position();
      int drivetrainRightSideSpeed = Controller1.Axis2.position();
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) 
      {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) 
        {
          LeftDriveSmart.stop();                            // stop the left drive motor
          DrivetrainLNeedsToBeStopped_Controller1 = false;  // tell the code that the left motor has been stopped

        }
      }
      else 
      {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }

      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) 
      {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) 
        {
          RightDriveSmart.stop();                           // stop the right drive motor
          DrivetrainRNeedsToBeStopped_Controller1 = false;  // tell the code that the right motor has been stopped
        }
      } 
      else 
      {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1)
      {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }

      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) 
      {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }


    }

    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

// sets stuff up
void vexcodeInit( void ) 
{
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}