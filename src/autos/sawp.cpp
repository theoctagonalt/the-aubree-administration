#include "main.h"
#include "globals.h"
#include "autonomous.h"
#include "initialize.h"
#include "devices.h"
#include "./subsystems/intake.h"
#include "./subsystems/arm.h"
#include "./subsystems/mogo.h"
#include "./subsystems/doinker.h"

void sawp(){
  int colour = get_colour();
  int n = colour == RED ? 1 : 1;
  int match = get_match();

  //alliance stake
  chassis.setPose(0, 0, 180);
  chassis.moveToPoint(n*-9, -11, 1000);
  chassis.waitUntilDone();
  Arm::set_state(SCORING);
  pros::delay(1000);
  int x = chassis.getPose().x;
  int y = chassis.getPose().y;
  int heading = chassis.getPose().theta;
  int alliance_heading = colour == RED ? 270 : 270;
  chassis.turnToHeading(alliance_heading, 1000);
  // chassis.moveToPoint(n*-11, -11, 250);
  chassis.waitUntilDone();
  // chassis.setPose(x, y, heading);

  //goal 
  chassis.moveToPoint(n*28, 7, 1000, {.forwards=false});
  pros::delay(100);
  Arm::set_state(REST);
  chassis.waitUntilDone();
  pros::delay(250);
  Mogo::toggle();
  pros::delay(500);
  Intake::toggle();

  //ring
  chassis.moveToPoint(n*28, 50, 1000);
  chassis.waitUntilDone();
  pros::delay(1000);

  // //drop goal
  // chassis.moveToPoint(n*4, 9, 1000, {.forwards=false});
  // chassis.waitUntilDone();
  // Mogo::toggle();
  // pros::delay(100);

  // -------------------+// //ring stakc
  chassis.moveToPoint(n*9, -45, 1500);
  // Intake::set_target_colour(-1);
  chassis.waitUntilDone();
  // pros::delay(400);
  // Intake::toggle();
  // Intake::set_target_colour(colour);

  // //second mogo
  // chassis.moveToPoint(n*37, -37, 1000, {.forwards=false, .maxSpeed=75});
  // chassis.waitUntilDone();
  // pros::delay(500);
  // Mogo::toggle();
  // pros::delay(500);

  // //third ring
  // Intake::toggle();
  // chassis.moveToPoint(n*41, -65, 1000);
  // chassis.waitUntilDone();
  // pros::delay(1000);

  // ladder
  chassis.moveToPoint(n*35, -20, 1500);
  Arm::set_state(SCORING);
}