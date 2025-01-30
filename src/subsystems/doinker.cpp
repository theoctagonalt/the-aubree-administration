#include "./subsystems/intake.h"
#include "main.h"
#include "devices.h"
#include "globals.h"
#include "initialize.h"

namespace Doinker{
  int state = RETRACTED;
  void toggle(){
    doinker.set_value(!state);
    state = !state;
  }
  int get_state(){
    return state;
  }
}