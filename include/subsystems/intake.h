#ifndef INTAKE__H__
#define INTAKE__H__

namespace Intake{
  void toggle();
  void set_preroller(int state);
  void set_hooks(int state);
  int get_hooks();
  int get_preroller();
  void update_intake();
  void set_target_colour(int colour);
  void toggle_position_tracking();
  int get_target_colour();
}

#endif