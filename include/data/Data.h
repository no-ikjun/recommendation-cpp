#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include <ostream>
#include <istream>

class Data {
public:
  Data(std::string id, std::string content, std::vector<double> featureVector);
  virtual ~Data() = default;

  std::string getId() const;
  virtual std::string getContent() const;
  virtual std::vector<double> getFeatureVector() const;

  virtual void serialize(std::ostream& os) const;
  virtual bool deserialize(std::istream& is);

protected:
  std::string id;
  std::string content;
  std::vector<double> featureVector;
};

#endif
