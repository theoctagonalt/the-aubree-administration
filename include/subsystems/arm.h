#ifndef ARM__H__
#define ARM__H__

namespace Arm{
  void set_state(int state);
  int get_state();
  void manual_control(int direction, bool value);
  void arm_pid();
}

#endif
