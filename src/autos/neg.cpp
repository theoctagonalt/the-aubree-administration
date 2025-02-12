#include "main.h"
#include "globals.h"
#include "autonomous.h"
#include "initialize.h"
#include "devices.h"
#include "./subsystems/intake.h"
#include "./subsystems/arm.h"
#include "./subsystems/mogo.h"
#include "./subsystems/doinker.h"

void neg_route(){
  int colour = get_colour();
  int n = colour == RED ? 1 : -1;
  int starting_y = colour == RED ? 0 : 0;
  chassis.setPose(0, starting_y, 180);
  chassis.moveToPoint(0, 25, 1000, {.forwards=false});
  chassis.waitUntilDone();
  chassis.moveToPoint(0, 17.5, 1000);
  chassis.waitUntilDone();
  chassis.turnToHeading(265, 1000);
  chassis.waitUntilDone();
  chassis.moveToPoint(n*10, 15, 2000, {.forwards=false, .maxSpeed=35});
  while(mogo_distance.get_distance() > 170){
    int distance = mogo_distance.get_distance();
    pros::lcd::clear_line(5);
    pros::lcd::print(5, "%i", distance);
    pros::delay(3);
  }
  chassis.cancelMotion();
  pros::delay(1000);
  Intake::toggle();
  pros::delay(1000);
  chassis.moveToPoint(-10, -20, 500);
  chassis.waitUntilDone();
  chassis.moveToPoint(-35, -33, 1000);
  chassis.waitUntilDone();
  chassis.moveToPoint(-28, -8, 1000, {.forwards=false});
  pros::delay(500);
  Intake::toggle();
  chassis.waitUntilDone();
  pros::delay(500);
  Mogo::toggle();
  pros::delay(500);
  Intake::toggle();
  chassis.moveToPoint(-48, -30, 1000);
  chassis.waitUntilDone();
  pros::delay(500);
  chassis.moveToPoint(-35, -40, 1000, {.forwards=false});
  chassis.waitUntilDone();
  chassis.moveToPoint(-48, -43, 1000);
}