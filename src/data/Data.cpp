#include "data/Data.h"
#include <iostream>

Data::Data(std::string id, std::string content, std::vector<double> featureVector)
: id(id), content(content), featureVector(featureVector) {}

std::string Data::getId() const {
  return id;
}

std::string Data::getContent() const {
  return content;
}

std::vector<double> Data::getFeatureVector() const {
  return featureVector;
}

void Data::serialize(std::ostream& os) const {
  os.write(id.c_str(), id.size() + 1);
  os.write(content.c_str(), content.size() + 1);
  size_t vectorSize = featureVector.size();
  os.write(reinterpret_cast<const char*>(&vectorSize), sizeof(vectorSize));
  for (double feature : featureVector) {
      os.write(reinterpret_cast<const char*>(&feature), sizeof(feature));
  }
}

bool Data::deserialize(std::istream& is) {
  std::getline(is, id, '\0');
  std::getline(is, content, '\0');
  size_t vectorSize;
  is.read(reinterpret_cast<char*>(&vectorSize), sizeof(vectorSize));
  featureVector.resize(vectorSize);
  for (double& feature : featureVector) {
      is.read(reinterpret_cast<char*>(&feature), sizeof(feature));
  }
  return !is.fail();
}
