#ifndef ARM__H__
#define ARM__H__

namespace Arm{
  void set_state(int state);
  int get_state();
  void set_pid(int state);
  void arm_pid();
}

#endif
