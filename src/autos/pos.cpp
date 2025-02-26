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
  int match = get_match();

  chassis.setPose(0, 0, n*-90);

  chassis.moveToPoint(n*42, 0, 1000, {.forwards=false});
  chassis.waitUntilDone();

  chassis.turnToHeading(n*-115, 500);
  chassis.waitUntilDone();

  int mogo_x = colour == RED ? 49 : -49;
  int mogo_y = colour == RED ? 6 : 9;

  chassis.moveToPoint(mogo_x, mogo_y, 1000, {.forwards=false});
  chassis.waitUntilDone();

  Mogo::toggle();
  pros::delay(250);

  chassis.moveToPoint(n*28, 15, 1000);
  pros::delay(100);
  
  bool won_mogo = mogo_distance.get() < 25;

  if(won_mogo) {
    Intake::toggle();
  }else{
    Intake::set_preroller(FWD);
  }
  chassis.waitUntilDone();
  pros::delay(100);

  if(won_mogo){
    Intake::toggle();
  }else{
    Intake::set_preroller(OFF);
  }
  Mogo::toggle();

  int mogo_2_y = colour == RED ? 37 : 40;

  chassis.moveToPoint(n*33, 40, 1000, {.forwards=false});
  chassis.waitUntilDone();

  Mogo::toggle();
  pros::delay(500);
  Intake::toggle();
  pros::delay(1000);

  chassis.moveToPoint(n*37, 48, 1000);
  chassis.waitUntilDone();
  Arm::set_state(SCORING);
}