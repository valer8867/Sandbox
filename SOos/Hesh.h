#include <iostream>
#include <unordered_map>

using namespace std;


struct coord {
	int x;
	int y;
};
bool operator==(const coord& a, const coord& b) {
	return a.x == b.x && a.y == b.y;
}
namespace std {
	template<>
	struct hash<coord> {
		using argument_type = coord;
		using result_type = size_t;
		result_type operator()(const argument_type& c) const {
			return static_cast<result_type>(c.x) + static_cast<result_type>(c.y);
		}
	};
}
