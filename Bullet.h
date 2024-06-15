#ifndef BULLET_H
#define BULLET_H

class Bullet {
	public:
		int xPos, yPos;
		int xFont, yFont;
		int alive;
		int damage;
		Bullet();
		void Alive(int _xPos, int _yPos, int xFont, int yFont, int _damage);
		int Move(int *mapIndex, int *popMap);
		void Dead();
		int mapNew[1000];
		void MapNewChange(int _xPos, int _yPos);
		~Bullet();
	protected:
};

#endif