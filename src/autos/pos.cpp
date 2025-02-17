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
  chassis.setPose(0, 0, 0);
  chassis.moveToPoint(0, -33, 1000, {.forwards=false});
  chassis.waitUntilDone();
  pros::delay(500);
  Mogo::toggle();
  pros::delay(500);
  Intake::toggle();
  pros::delay(1000);
}