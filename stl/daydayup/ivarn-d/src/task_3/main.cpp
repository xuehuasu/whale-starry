#include <iostream>
#include <set>

// 关于红黑树的一些接口测试
class Student {
 public:
  Student(std::string name, double score) : name(name), score(score) {}

  bool operator<(const Student& student) const {
    return this->score < student.score;
  }

  std::string GetName() { return name; }
  double GetScore() { return score; }
  void PrintInfo() {
    std::cout << "name: " << name << " score: " << score << std::endl;
  }

 private:
  std::string name;
  double score;
};

void PrintTree(auto p) {
  for (auto it = p.begin(); it != p.end(); it++) {
    it->PrintInfo();
  }
}

int main() {
  // 插入
  std::cout << "--------Instert----------" << std::endl;
  // equal不会去重
  std::_Rb_tree<Student, Student, std::_Identity<Student>, std::less<Student>>
      rb_tree;
  rb_tree._M_insert_equal(Student("xs1", 88.1));
  rb_tree._M_insert_equal(Student("xs2", 90.9));
  rb_tree._M_insert_equal(Student("xs3", 89.2));
  rb_tree._M_insert_equal(Student("xs1", 88.1));
  PrintTree(rb_tree);
  std::cout << rb_tree.size() << std::endl;

  std::cout << " " << std::endl;
  // unique 会自动去重
  std::_Rb_tree<Student, Student, std::_Identity<Student>, std::less<Student>>
      rb_tree2;
  rb_tree2._M_insert_unique(Student("xs1", 88.1));
  rb_tree2._M_insert_unique(Student("xs2", 90.9));
  rb_tree2._M_insert_unique(Student("xs3", 89.2));
  rb_tree2._M_insert_unique(Student("xs1", 88.1));
  PrintTree(rb_tree2);
  std::cout << rb_tree2.size() << std::endl;

  std::cout << "--------Get----------" << std::endl;
  for (auto e : rb_tree) {
    std::cout << e.GetName() << " " << e.GetScore() << std::endl;
  }
  std::cout << " " << std::endl;
  for (auto e : rb_tree2) {
    std::cout << e.GetName() << " " << e.GetScore() << std::endl;
  }

  return 0;
}