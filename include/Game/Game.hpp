#ifndef GAME_HPP
# define GAME_HPP 1

#define GAME_DEBUG 1

namespace Game
{
	class SceneLoader;

	namespace Component
	{
		enum ItemType {SpeedBoost, AddBomb, ExplosionBoost, Antidote, AntidoteDeco, FireDeco};
		enum ObjectiveType {MoveTo, DropBomb, TakeBonus, KillEnemy};

		class GameManager;

		class Bomb;
        class Breakable;
        class Character;
		class IA;
		class Item;
		class Map;
        class Player;

		class Settings;
		class GameProgression;

		class MainMenu;
		class UIThemeManager;
		class VersusMenu;
		class AdventureMenu;
		class AdventureContinueMenu;
		class SettingsMenu;
		class Credits;
		class InGameMenu;
		class GameOverMenu;
		class VictoryMenu;
		class TimeUI;
		class StartTimerUI;
		class Message;
		class LevelInstructions;

		class AudioManager;
	}
}

#endif
