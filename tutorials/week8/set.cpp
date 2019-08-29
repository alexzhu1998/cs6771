#include <iostream>
#include <set>


// Default typename declared here
template <typename T, typename CONT = std::set<T>>
class SillySet {
 public:
  void insert(T t);
  bool erase(T t);

	// Ostream friend
	friend std::ostream& operator<<(std::ostream& os, SillySet s) {
		for (const auto& i : s.set_) {
			os << i << " ";
		}
		return os;
	}
	
 private:
  CONT set_;
};

template <typename T, typename CONT>
void SillySet<T, CONT>::insert(T t) {
	set_.insert(t);
}

template <typename T, typename CONT>
bool SillySet<T, CONT>::erase(T t) {
	auto it = set_.find(t);
	if (it != set_.end()) {
		set_.erase(it);
		return true;
	}

	return false;
}

int main() {

  SillySet<float> s;
  SillySet<int> us;

  s.insert(5.4);
  s.insert(6.2);
  s.erase(5.4);
  std::cout << s << "\n";

  us.insert(5);
  us.insert(6);
  us.erase(5);

  std::cout << us << "\n";

}
