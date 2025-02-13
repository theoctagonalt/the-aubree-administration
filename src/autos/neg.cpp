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
  int starting_y = colour == RED ? 0 : -3.5;
  chassis.setPose(n*0, starting_y, 180);
  chassis.moveToPoint(n*0, 25, 1000, {.forwards=false});
  chassis.waitUntilDone();
  chassis.moveToPoint(n*0, 17.5, 1000);
  chassis.waitUntilDone();
  int alliance_stake_heading = colour == RED ? 265 : 88;
  chassis.turnToHeading(alliance_stake_heading, 1000);
  chassis.waitUntilDone();
  int alliance_stake_y = colour == RED ? 15 : 16;
  chassis.moveToPoint(n*10, alliance_stake_y, 3000, {.forwards=false, .maxSpeed=25});
  float dis = colour == RED ? 175: 194;
  while(mogo_distance.get_distance() > dis){
    int distance = mogo_distance.get_distance();
    pros::lcd::clear_line(5);
    pros::lcd::print(5, "%i", distance);
    pros::delay(3);
  }
  chassis.cancelMotion();
  pros::delay(1000);
  Intake::toggle();
  pros::delay(1000);
  chassis.moveToPoint(n*-10, -20, 500);
  chassis.waitUntilDone();
  chassis.moveToPoint(n*-35, -33, 1000);
  chassis.waitUntilDone();
  int mogo_x = colour == RED ? -28 : 33;
  int mogo_y = colour == RED ? -8 : -5;
  chassis.moveToPoint(mogo_x, mogo_y, 1000, {.forwards=false});
  pros::delay(650);
  Intake::toggle();
  chassis.waitUntilDone();
  pros::delay(1100);
  Mogo::toggle(); // mogo clamped
  pros::delay(500);
  Intake::toggle();
  int second_ring_x = colour == RED ? -48 : 49;
  int second_ring_y = colour == RED ? -30 : -27;
  chassis.moveToPoint(second_ring_x, second_ring_y, 1000);
  chassis.waitUntilDone();
  pros::delay(500);
  chassis.moveToPoint(n*-35, -40, 1000, {.forwards=false});
  chassis.waitUntilDone();
  int third_ring_x = colour == RED ? -50 : 52;
  int third_ring_y = colour == RED ? -40 : -37;
  chassis.moveToPoint(third_ring_x, third_ring_y, 1000);
  chassis.waitUntilDone();
  pros::delay(500);
  if (colour == RED){
    chassis.moveToPoint(n*-35, -35, 2000, {.forwards=false});
    chassis.waitUntilDone();
    chassis.moveToPoint(n*-43, 6, 2000);
  }else{
    chassis.moveToPoint(25, -35, 2000, {.forwards=false});
    chassis.waitUntilDone();
    chassis.moveToPoint(n*-42, 9, 2000);
  
  }
}