#pragma once

namespace Tmpl8 {

int CheckElement();
bool StartRoom();
int ExtraStartingHealth();
int LifeStealAmount();

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp(int button);
	void MouseDown(int button);
	void MouseMove( int x, int y ) { mousex = x, mousey = y; }
	void KeyUp(int key);
	void KeyDown(int key);


private:
	Surface* screen;
	Surface* Menu;
	int mousex, mousey;
	float charx = 0, chary = 0;

	void SetStart();
	void TickMainMenu();
	void TickShop();
	void TickWin();
	void TickLoss();
	void TickGunUpgrade();
	void TickElementSelect();
	void CharacterMovement(float DeltaTime);
	void ClearedRoom();
};

}; // namespace Tmpl8