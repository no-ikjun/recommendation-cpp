class Database {
public:
  virtual void add(void* item) = 0;
  virtual void update(void* item) = 0;
  virtual ~Database() {}
};