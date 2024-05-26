#ifndef NEWS_H
#define NEWS_H

#include <string>
#include <vector>
#include "data/Category.h"
#include "data/Data.h"

class News : public Data {
public:
    News();
    News(const std::string& id, const std::string& title, const std::string& content, Category category, const std::vector<double>& featureVector);

    std::string getTitle() const;
    Category getCategory() const;

    void serialize(std::ostream& os) const;
    bool deserialize(std::istream& is);

private:
    std::string title;
    Category category;
};

#endif // NEWS_H
