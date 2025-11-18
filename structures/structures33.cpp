// мяу
#include <fstream>
#include <limits>
#include <vector>
#include <set>
#include <map>
#include <optional>
using namespace std;

struct node {
	int p; // prev
	int n; // next
	int q; // quantity
};

int main() {
	ifstream in{ "input.txt" };
	ofstream out{ "output.txt" };

	int n, w, h;
	in >> n >> w >> h;

	if (n == 0) {
		out << w * h << endl;
		return 0;
	}

	// уникальные границы по y
	set<int> ys; ys.emplace(0); ys.emplace(h);
	// уникальные границы по x
	set<int> xs; xs.emplace(0); xs.emplace(w);
	vector<pair<int, int>> trees(n);
	// сколько раз встречается каждая x координата
	map<int, int> xc;
	for (int i = 0; i < n; i++) {
		in >> trees[i].first >> trees[i].second;
		ys.emplace(trees[i].second);
		xs.emplace(trees[i].first);
		xc[trees[i].first]++;
	}

	// сжатые координаты -> оригинальные (x)
	vector<int> ctox(xs.begin(), xs.end());
	// оригинальные координаты -> сжатые (x)
	map<int, int> otcx;
	for (int i = 0; i < ctox.size(); i++) otcx[ctox[i]] = i;

	// сжатые координаты -> оригинальные (y)
	vector<int> ctoy(ys.begin(), ys.end());
	// оригинальные координаты -> сжатые (y)
	map<int, int> otcy;
	for (int i = 0; i < ctoy.size(); i++) otcy[ctoy[i]] = i;

	// хранит какие деревья находится на конкретной y координате (всё сжато)
	vector<vector<int>> cfences(ctoy.size());
	for (int i = 0; i < n; i++) cfences[otcy[trees[i].second]].push_back(otcx[trees[i].first]);

	// двусвязный список деревьев
	vector<optional<node>> trees_copy(xs.size());

	int area = numeric_limits<int>::min();
	// максимальное расстояние между иксами, если учитывать всю область (w, h) и все деревья
	int max_width_all = numeric_limits<int>::min();
	// построение списка
	for (int i = 0; i < ctox.size(); i++) {
		trees_copy[i] = {
			i == 0 ? -1 : i - 1, // prev
			i == ctox.size() - 1 ? -1 : i + 1, // next
			(ctox[i] == 0 || ctox[i] == w) ? numeric_limits<int>::max() : xc[ctox[i]] // quantity
		};
		if (i != 0) max_width_all = max(max_width_all, ctox[i] - ctox[i - 1]);
	}

	// удаление дерева
	auto remove = [&](vector<optional<node>>& trees, int x, int& max_width) {
		auto& tree = trees[x];
		if (!tree.has_value()) return; // уже удалили
		tree->q--;
		// удаляем только если таких деревьев с координатой x больше не осталось
		if (tree->q == 0) {
			// что-то типа двусвязного списка. меняем prev и next
			if (tree->p != -1) trees[tree->p]->n = tree->n;
			if (tree->n != -1) trees[tree->n]->p = tree->p;
			// при удалении дерева, max_width либо не изменится, либо увеличится
			if (tree->p != -1 && tree->n != -1) max_width = max(max_width, ctox[tree->n] - ctox[tree->p]);
			trees[x] = nullopt;
		}
	};

	for (int ymin = 0; ymin < ctoy.size(); ymin++) {
		vector<optional<node>> trees = trees_copy;
		int max_width = max_width_all;
		// удаляем деревья которые шли ДО ymin
		for (int y = 0; y <= ymin; y++) for (int x : cfences[y]) remove(trees, x, max_width);

		for (int ymax = ctoy.size() - 1; ymax > ymin; ymax--) {
			// удаляем деревья которые идут ПОСЛЕ ymax
			for (int x : cfences[ymax]) remove(trees, x, max_width);
			// считаем площадь для оставшейся области и деревьев
			area = max(area, (ctoy[ymax] - ctoy[ymin]) * max_width);
		}
	}

	out << area;
}