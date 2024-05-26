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
  if (is.fail()) return false;

  std::getline(is, content, '\0');
  if (is.fail()) return false;

  size_t vectorSize;
  is.read(reinterpret_cast<char*>(&vectorSize), sizeof(vectorSize));
  if (is.fail() || vectorSize > 100000) {
    return false;
  }

  featureVector.clear(); // 기존 벡터를 클리어하고 새로운 크기로 조정
  featureVector.reserve(vectorSize);
  for (size_t i = 0; i < vectorSize; ++i) {
    double feature;
    is.read(reinterpret_cast<char*>(&feature), sizeof(feature));
    if (is.fail()) return false;
    featureVector.push_back(feature);
  }

  return true;
}