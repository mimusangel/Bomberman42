#ifndef BE_CORE_ASCENE_HPP
#define BE_CORE_ASCENE_HPP 1

#include "Core.hpp"

namespace BeerEngine
{
    class GameObject;

    class AScene
    {
    private:
        static int                  uniqueID;
        std::map<int, GameObject *> _gameObjects;
        std::mutex                  updateMutex;

        
    public:
        std::string                 filePath;

        AScene(void);
        virtual ~AScene(void);

        virtual void    init(void) = 0;

        void    mutexLock(bool lock);

        void    start(void);
        void    fixedUpdate(void);
        void    update(void);
        void    renderUpdate(void);
        void    render(void);
        void    physicUpdate(void);

        template<typename T, typename std::enable_if<std::is_base_of<GameObject, T>::value>::type* = nullptr>
		T	*instantiate(void)
		{
             std::cout << "GameObject added : " << uniqueID << std::endl;
			T *c = new T(uniqueID++);
			_gameObjects.insert(std::pair<int, GameObject *>(uniqueID, c));
            c->start();
			return (c);
		}

        void debugTest(void)
        {
            std::cout << "GameObject List Size : " << _gameObjects.size() << std::endl;
        }

        std::vector<GameObject *> getGameObjects()
        {
            std::vector<GameObject *> res;

            // populate map somehow
            for(auto it = _gameObjects.begin(); it != _gameObjects.end(); ++it) {
                res.push_back( it->second );
            }
            return (res);
        }

        // void load(std::string filePath)
        // {
        //     std::string content = BeerEngine::IO::FileUtils::LoadFile(filePath);
        //     auto j = nlohmann::json::parse(content);
        //     // Game::SettingsContainer c;
        //     // this->settingsContainer = j;
        // }

        void save(std::string filePath);

    };
}

#endif