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
  double xWeightedMass = 0;
  double yWeightedMass = 0;
  double zWeightedMass = 0;

  for (int i = 0; i < model->LinkCount(); i++) {
    auto currentLinkInertial = model->LinkByIndex(i)->Inertial();
    totalInertial += currentLinkInertial;

    ignition::math::Pose3d pose;
    if (model->LinkByIndex(i)->SemanticPose().Resolve(pose, "__model__").empty()) {
      xWeightedMass += pose.Pos().X() * currentLinkInertial.MassMatrix().Mass();
      yWeightedMass += pose.Pos().Y() * currentLinkInertial.MassMatrix().Mass();
      zWeightedMass += pose.Pos().Z() * currentLinkInertial.MassMatrix().Mass();
    }
  }

  auto totalMass = totalInertial.MassMatrix().Mass();
  auto xCentreOfMass = xWeightedMass/totalMass;
  auto yCentreOfMass = yWeightedMass/totalMass;
  auto zCentreOfMass = zWeightedMass/totalMass;

  std::cout << "Total mass: " << totalMass << std::endl;

  std::cout << "Centre of mass: " << std::endl;
  std::cout << "X: " << xCentreOfMass << std::endl;
  std::cout << "Y: " << yCentreOfMass << std::endl;
  std::cout << "Z: " << zCentreOfMass << std::endl;

  return 0;
}
