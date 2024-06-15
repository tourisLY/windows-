#include "Map.h"

Map::Map(int _rows, int _cols) {
	rows = _rows;
	cols = _cols;
}

Map::~Map() {
}

void Map::MapFirst(int *mapIn, int _rows, int _cols) {
	for (int i = 0; i < _rows * _cols; i++) {
		mapIndex[i] = mapIn[i];
	}
}