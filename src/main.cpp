/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftFront            motor         1               
// RightFront           motor         10              
// LeftBack             motor         11              
// RightBack            motor         20              
// Controller1          controller                    
// I1                   motor         9               
// T                    motor         12              
// I2                   motor         4               
// LIFT                 motor         2               
// LEDA                 led           A               
// LEDH                 led           H               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "Robot.h"
#include "Style.h"

using namespace vex;

// A global instance of competition
competition Competition;

// Global Robot
TankDrive robot;
Tray Tray;
Actuator Intake;
Actuator Arm;

turnType autoTurnDirection = right;

void pre_auton(void)
{
  vexcodeInit();
  //Adds Contoller
  robot.ControllerPtr = &Controller1;
  //Adds Drivebase Motors
  robot.LF = LeftFront;
  robot.RF = RightFront;
  robot.LB = LeftBack;
  robot.RB = RightBack;
  //Adds Intake Motors
  Intake.m1 = I1;
  Intake.m2 = I2;
  //Adds Claw Motor
  Tray.m1 = T;
  //Adds Arm Motor
  Arm.m1 = LIFT;
  //Sets the size of the robot and its wheels
  robot.width = 11.5;
  robot.length = 0;
  robot.wheelDiameter = 4;

  print2373R();
}

void autonomous(void)
{
  robot.controllerPrint("Autonomous Started");
  
  turnType turnDirection = right;
  /*
  Arm.calibrate();
  I1.spin(forward, 200, rpm);
  I2.spin(forward, 200, rpm);
  wait(500, msec);
  LIFT.rotateTo(5, degrees);
  wait(500, msec);
  LIFT.rotateTo(-5, degrees);
  wait(1000, msec);
  robot.drive(45, 65);
  robot.turn(195, turnDirection, 40);
  robot.drive(53, 75);
  I1.stop(brake);
  I2.stop(brake);
  T.rotateTo(254, deg, 150, rpm);
  I1.spin(reverse, 50, rpm);
  I2.spin(reverse, 50, rpm);
  wait(500, msec);
  robot.drive(-45, 75);
  
  */

  /*Arm.calibrate();
  I1.spin(forward, 200, rpm);
  I2.spin(forward, 200, rpm);
  wait(500, msec);
  robot.drive(45, 50);
  robot.driveTime(500,reverse,150);
  robot.turn(162, turnDirection, 40);
  wait(500,msec);
  I1.stop(brake);
  I2.stop(brake);
  robot.driveTime(2000,forward,150);
  T.spin(forward,65, rpm);
  wait(1000,msec);
  T.stop(brake);
  I1.spin(reverse, 50, rpm);
  I2.spin(reverse, 50, rpm);
  wait(1000, msec);
  robot.drive(-45, 75);
  I1.stop(brake);
  I2.stop(brake);*/

  
  robot.driveTime(2000, forward, 150);
  robot.driveTime(2000, reverse, 150);
  
  robot.controllerPrint("Autonomous Finished");
}

void usercontrol(void)
{
  Tray.calibrate();
  Arm.calibrate();
  //LIFT.rotateTo(30, degrees, 10, rpm);
  robot.controllerPrint("Good Luck, Ryan!");
  Brain.resetTimer();
  while (true)
  {
    lights();
    if(Controller1.ButtonA.pressing())
      autonomous();
    if(Controller1.ButtonY.pressing())
    {
      Tray.calibrate();
      Arm.calibrate();
    }
    robot.controllerPrint("Tray: %.1f", Tray.m1.position(degrees));

    Tray.spinMechanism(Controller1.ButtonUp, Controller1.ButtonDown, 30);
    Tray.toggleMechanism(Controller1.ButtonX, 30);
    Intake.spinMechanism(Controller1.ButtonR1, Controller1.ButtonR2, 200);
    Arm.spinMechanism(Controller1.ButtonL1, Controller1.ButtonL2, 100);

    //Sets controls to split arcade
    robot.driveBase(Drive::SplitArcade);
    wait(25, msec);
  }
}

int main()
{
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true)
  {
    wait(100, msec);
  }
}