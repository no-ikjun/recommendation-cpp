#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>

// Abstract class for any data type
class Data {
protected:
  Data(std::string id, std::string content, std::vector<double> featureVector);
  std::string getId();
  virtual std::string getContent() = 0;
  virtual std::vector<double> getFeatureVector() = 0;
  void setContent(std::string content);
  void setFeatureVector(std::vector<double> featureVector);
private:
  std::string id;
  std::string content;
  std::vector<double> featureVector;
};

#endif