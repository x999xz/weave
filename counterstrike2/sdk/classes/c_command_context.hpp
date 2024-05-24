#pragma once

#include "../sdk.hpp"

class c_command_context
{
public:
  bool needsprocessing;
  char gap1[7];
  c_user_cmd* cmd;
  char gap10[96];
  void* dword70;
  char gap74[4];
  int command_number;
};