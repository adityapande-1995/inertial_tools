#include <cstring>
#include <iostream>
#include <memory>
#include <string>

#include "sdf/sdf_config.h"
#include "sdf/Filesystem.hh"
#include "sdf/Root.hh"
#include "sdf/parser.hh"
#include "sdf/PrintConfig.hh"
#include "sdf/system_util.hh"
#include "sdf/Link.hh"

#include "ignition/math/Inertial.hh"

int main(int argc, char *argv[]) {
 // check arguments
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0]
              << " <sdf-path>" << std::endl;
    return -1;
  }
  const std::string sdfPath(argv[1]);

  // load and check sdf file
  sdf::SDFPtr sdfElement(new sdf::SDF());
  sdf::init(sdfElement);
  if (!sdf::readFile(sdfPath, sdfElement))
  {
    std::cerr << sdfPath << " is not a valid SDF file!" << std::endl;
    return -2;
  }

  // start parsing model
  const sdf::ElementPtr rootElement = sdfElement->Root();
  if (!rootElement->HasElement("model"))
  {
    std::cerr << sdfPath << " is not a model SDF file!" << std::endl;
    return -3;
  }
  const sdf::ElementPtr modelElement = rootElement->GetElement("model");
  const std::string modelName = modelElement->Get<std::string>("name");
  std::cout << "Found " << modelName << " model!\n" << std::endl;

  auto totalInertial = ignition::math::Inertiald();

  // parse model links
  sdf::ElementPtr linkElement = modelElement->GetElement("link");
  while (linkElement)
  {
    const std::string linkName = linkElement->Get<std::string>("name");

    sdf::Link current_link;
    current_link.Load(linkElement);
    totalInertial += current_link.Inertial();

    linkElement = linkElement->GetNextElement("link");
  }

  std::cout << "Total mass: "  << totalInertial.MassMatrix().Mass() << std::endl;

  return 0;
}
