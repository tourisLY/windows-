#ifndef MAP_H
#define MAP_H

class Map {
	public:
		int rows, cols;
		int mapIndex[30 * 50];
		Map(int _rows, int _cols);
		void MapFirst(int *mapIn, int _rows, int _cols);
		~Map();
	protected:
};

#endif