//
// Created by Darenn on 09/02/2017.
//

#ifndef PANCAKE_CIRCLECOLLIDER_HPP
#define PANCAKE_CIRCLECOLLIDER_HPP

#include <GameLogic/Components/Collider.hpp>

namespace PancakeEngine {
class CircleCollider : public Collider {
 public:
  float radius;
};
}  // namespace PancakeEngine

#endif  // PANCAKE_CIRCLECOLLIDER_HPP
