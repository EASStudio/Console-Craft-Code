#pragma once
#ifndef GAME_H
#define GAME_H

class Game 
{
public:
	Game();
	~Game();

	void Init();
	void Run();
	void Shutdown();

private:
	bool isRunning;
};

#endif // !GAME_H
