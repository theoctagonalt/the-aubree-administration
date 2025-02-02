#include "main.h"
#include "globals.h"
#include "autonomous.h"
#include "initialize.h"
#include "devices.h"
#include "./subsystems/intake.h"
#include "./subsystems/arm.h"
#include "./subsystems/mogo.h"
#include "./subsystems/doinker.h"

void pos_route(){
  int colour = get_colour();
  int n = colour == RED ? 1 : -1;
  chassis.setPose(0, 0, n*90);
  chassis.moveToPoint(n*-36, 2, 1000, {.forwards=false});
  chassis.waitUntilDone();
  Mogo::toggle();
  pros::delay(500);
  chassis.turnToHeading(0, 1000);
  chassis.waitUntilDone();
  Intake::toggle();
  chassis.moveToPoint(n*-33, 33, 1000);
  chassis.waitUntilDone();
  pros::delay(500);
  chassis.moveToPoint(n*-10, 10, 1000, {.forwards=false});
  chassis.waitUntilDone();
  pros::delay(250);
  int target_heading_1 = colour == RED ? 5 : -8;
  chassis.turnToHeading(target_heading_1, 500);
  chassis.waitUntilDone();
  Doinker::toggle();
  pros::delay(250);
  pros::delay(250);
  if(colour == RED){
    chassis.moveToPoint(2, 38, 1000, {.maxSpeed=100});
    chassis.waitUntilDone();
    chassis.turnToHeading(n*-60, 1000, {.minSpeed=150});
    Intake::set_hooks(REV);
    chassis.waitUntilDone();
    Intake::set_hooks(FWD);
    Doinker::toggle();
    chassis.turnToHeading(30, 500);
    chassis.waitUntilDone();
    chassis.moveToPoint(2, 40, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(0, 38, 500, {.forwards=false});
    chassis.waitUntilDone();
    chassis.moveToPoint(2, 40, 500);
    chassis.waitUntilDone();
    chassis.moveToPoint(-30, 35, 1000, {.forwards=false});
    chassis.waitUntilDone();
    chassis.turnToHeading(-90, 500);
    chassis.waitUntilDone();
    Mogo::toggle();
    chassis.turnToHeading(90, 1000);
  }else{
    chassis.moveToPoint(-8, 39, 1000, {.maxSpeed=100});
    chassis.waitUntilDone();
    chassis.turnToHeading(210, 1000, {.minSpeed=150});  
    Intake::set_hooks(REV);
    chassis.waitUntilDone();
    Intake::set_hooks(FWD);
    Doinker::toggle();
    chassis.moveToPoint(20, 39, 500);
    Mogo::toggle();
    chassis.turnToHeading(-90, 500);
  }
}