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
  int starting_y = colour == RED ? 3 : 4;
  chassis.setPose(n*0, starting_y, 0);

  chassis.moveToPoint(0, 13, 3000);
  chassis.waitUntilDone();
  int heading = colour == RED ? 48 : 318;
  chassis.turnToHeading(heading, 1000);
  chassis.waitUntilDone();
  pros::delay(250);
  Arm::set_state(SCORING);
  pros::delay(1000);
  Arm::set_state(REST);

  chassis.moveToPoint(n*-5, -15, 1000, {.forwards=false});
  chassis.waitUntilDone();

  chassis.moveToPoint(n*-11, -21, 500);
  Intake::toggle();
  chassis.waitUntilDone();
  //FIRST RING??
  int first_ring_x = colour == RED ? -35 : 39;
  int first_ring_y = colour == RED ? -33 : -36;
  chassis.moveToPoint(first_ring_x, first_ring_y, 1000);
  chassis.waitUntilDone();
  int mogo_x = colour == RED ? -28 : 33;
  int mogo_y = colour == RED ? -3 : -5;
  chassis.moveToPoint(mogo_x, mogo_y, 1000, {.forwards=false});
  Intake::toggle();
  chassis.waitUntilDone();
  pros::delay(1100);
  Mogo::toggle(); // mogo clamped
  pros::delay(500);
  Intake::toggle();


  int second_ring_x = colour == RED ?  -47: 49;
  int second_ring_y = colour == RED ? -28 : -31;
  //SECOND RING
  chassis.moveToPoint(second_ring_x, second_ring_y, 1000);
  chassis.waitUntilDone();
  pros::delay(500);

  //MOVING BACK
  chassis.moveToPoint(n*-25, -25, 1000, {.forwards=false});
  chassis.waitUntilDone();
  
  int third_ring_x = colour == RED ?  -48 : 54;
  int third_ring_y = colour == RED ? -33 : -38;
  //THIRD RING
  chassis.moveToPoint(third_ring_x, third_ring_y, 1000);
  chassis.waitUntilDone();
  pros::delay(1000);
  // back up
  chassis.moveToPoint(n*-20, -22, 1000, {.forwards=false});
  chassis.waitUntilDone();
  // ladder
  chassis.moveToPoint(n*-30, 8, 2000);
  // chassis.moveToPoint(mogo_x, -8, 1000);
  // int second_ring_x = colour == RED ? -45 : 46;
  // int second_ring_y = colour == RED ? -32 : -27;
  // chassis.moveToPoint(second_ring_x, second_ring_y, 1000);
  // chassis.waitUntilDone();
  // pros::delay(500);
  // chassis.moveToPoint(n*-35, -40, 1000, {.forwards=false});
  // chassis.waitUntilDone();
  // int third_ring_x = colour == RED ? -47 : 47;
  // int third_ring_y = colour == RED ? -40 : -37;
  // chassis.moveToPoint(third_ring_x, third_ring_y, 1000);
  // chassis.waitUntilDone();
  // pros::delay(500);
  // if (colour == RED){
  //   chassis.moveToPoint(n*-35, -35, 2000, {.forwards=false});
  //   chassis.waitUntilDone();
  //   chassis.moveToPoint(n*-43, 6, 2000);
  // }else{
  //   chassis.moveToPoint(25, -35, 2000, {.forwards=false});
  //   chassis.waitUntilDone();
  //   chassis.moveToPoint(n*-42, 9, 2000);
  
  // }
}