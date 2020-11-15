#include "pinhole.h"

int main(int argc, char *args[]) {
  if (!pinhole::init()) {
    return 1;
  }

  while (pinhole::update()) {
    pinhole::render_frame();
  }
  return 0;
}
