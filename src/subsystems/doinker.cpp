#include "./subsystems/intake.h"
#include "main.h"
#include "devices.h"
#include "globals.h"
#include "initialize.h"

namespace Doinker{
  int state = RETRACTED;
  void toggle(){
    if(state == RETRACTED){
      doinker.set_value(true);
      state = EXTENDED;
    }else{
      doinker.set_value(false);
      state = RETRACTED;
    }
  }
  int get_state(){
    return state;
  }
}