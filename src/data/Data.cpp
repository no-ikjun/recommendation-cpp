#include <string>
#include <vector>
#include "data/Data.h"

Data::Data(std::string id, std::string content, std::vector<double> featureVector) {
  this->id = id;
  this->content = content;
  this->featureVector = featureVector;
}

std::string Data::getId() {
  return id;
}

std::string Data::getContent() {
  return content;
}

std::vector<double> Data::getFeatureVector() {
  return featureVector;
}

void Data::setContent(std::string content) {
  this->content = content;
}

void Data::setFeatureVector(std::vector<double> featureVector) {
  this->featureVector = featureVector;
}