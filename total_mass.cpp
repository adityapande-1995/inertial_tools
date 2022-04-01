#include <iostream>

#include "sdf/Root.hh"
#include "sdf/Link.hh"
#include "sdf/Model.hh"

#include "ignition/math/Inertial.hh"

int main(int argc, char *argv[]) {

  sdf::Root root;
  if (!root.Load(argv[1]).empty()) {
    return -1;
  }

  const sdf::Model * model = root.Model();
  if (!model){ 
    return -1;
  }

  auto totalInertial = ignition::math::Inertiald();
  for (int i = 0; i < model->LinkCount(); i++) {
    totalInertial += model->LinkByIndex(i)->Inertial();  
  }

  std::cout << "Total mass: " << totalInertial.MassMatrix().Mass() << std::endl;

  return 0;
}
