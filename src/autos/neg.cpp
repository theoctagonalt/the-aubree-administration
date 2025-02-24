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
  int match = get_match();

  int starting_y = colour == RED ? 20 : 0;
  chassis.setPose(0, starting_y, n*90);
  int rush_x = colour == RED ? 45 : -46;
  int rush_y = colour == RED ? 13 : 6; 
  chassis.moveToPoint(rush_x, rush_y, 1000);
  Doinker::toggle();
  Intake::toggle();
  chassis.waitUntilDone();
  pros::delay(1000);
  Intake::toggle();

  //backing up to the goal
  if(colour == BLUE){
    chassis.moveToPoint(n*35, 5, 500, {.forwards=false});
    chassis.waitUntilDone();
    chassis.moveToPoint(n*30, -10, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Doinker::toggle();
    chassis.moveToPoint(n*30, -20, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Mogo::toggle();
  }else{
    chassis.moveToPoint(10, 15, 1000, {.forwards=false});
    chassis.waitUntilDone();
    chassis.moveToPoint(15, -10, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Doinker::toggle();
    chassis.moveToPoint(30, -20, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Mogo::toggle();
  }

  pros::delay(500);
  Intake::toggle();
  if(colour == BLUE){
    chassis.moveToPoint(-25, 15, 500);
    chassis.waitUntilDone();
    chassis.moveToPoint(-20, 18, 500);
    chassis.waitUntilDone();
  }else{
    chassis.moveToPoint(30, 13, 1000);
    chassis.waitUntilDone();
    pros::delay(500);
  }
  int preload_x = colour == RED ? -10 : 0;
  int preload_y = colour == RED ? 7 : -10;
  chassis.moveToPoint(preload_x, preload_y, 1000);
  chassis.waitUntilDone();
  pros::delay(1500);

  //lader touch/fifth ring
  if(match == QUALS){
    int ladder_x = colour == RED ? 24 : -24;
    int ladder_y = colour == RED ? -40 : -30;
    chassis.moveToPoint(ladder_x, ladder_y, 1000);
  }else{
    int fifth_ring_x = colour == RED ? 10 : -10;
    int fifth_ring_y = colour == RED ? -50 : -50;
    chassis.moveToPoint(fifth_ring_x, fifth_ring_y, 2000, {.maxSpeed=50});
  }
}