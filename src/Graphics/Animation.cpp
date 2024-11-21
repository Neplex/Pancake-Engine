//
// Created by nicolas on 25/01/17.
//

#include <Graphics/Animation.hpp>

using namespace PancakeEngine;

void Animation::addFrame(const unsigned i, const unsigned j, const unsigned time, const bool flip) {
  Frame frame{};
  frame.i = i;
  frame.j = j;
  frame.time = time;
  frame.flip = flip;
  frames.push_back(frame);
}
