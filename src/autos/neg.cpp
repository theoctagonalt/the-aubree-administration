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
  int starting_y = colour == RED ? -1 : 0;
  chassis.setPose(0, starting_y, 0);
  chassis.moveToPoint(n*15, 17, 750);
  chassis.waitUntilDone();
  Arm::set_state(SCORING);
  pros::delay(1000);
  chassis.moveToPoint(n*-26, -7, 1000, {.forwards=false});
  Arm::set_state(REST);
  chassis.waitUntilDone();
  pros::delay(500);
  Mogo::toggle();
  pros::delay(500);
  int direction1 = colour == RED ? -135 : 135;
  chassis.turnToHeading(direction1, 1000);
  chassis.waitUntilDone();
  Intake::toggle();
  int ring_x = colour == RED ? -43 : 50;
  chassis.moveToPoint(ring_x, -30, 1000);
  chassis.waitUntilDone();
  pros::delay(1000);
  int ring_x_2 = colour == RED ? -18 : 24;
  int ring_y_2 = colour == RED ? -34 : -36;
  chassis.moveToPoint(n*-24, -36, 1000);
  chassis.waitUntilDone();
  if(colour==RED){
    // chassis.moveToPoint(-10, -36, 2000, {.maxSpeed=100});
    // chassis.waitUntilDone();
    // chassis.moveToPoint(-24, -36, 500);
    // chassis.waitUntilDone();
    // chassis.moveToPoint(-10, -36, 1000, {.maxSpeed=100});
  }else{
    chassis.moveToPoint(15, -40, 1000);
    chassis.waitUntilDone();
  }
  pros::delay(1000);
  if(colour==BLUE){
    chassis.moveToPoint(n*-39, -3, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(n*-39, 1, 1500);
    chassis.waitUntilDone();
    Intake::toggle();
  }else{
    chassis.moveToPoint(5, 35, 5000, {.maxSpeed=75});
  }
}