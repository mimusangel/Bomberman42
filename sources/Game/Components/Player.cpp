#include "Game/Components/Player.hpp"
#include "Game/Components/Character.hpp"
#include "Core/Input.hpp"
#include "Core/Component/RigidBody2D.hpp"

namespace Game
{
	namespace Component
	{
        Player::Player(BeerEngine::GameObject *gameObject) :
			Component(gameObject),
            _transform(gameObject->transform)
		{

        }

        void    Player::start(void)
        {
            _character = _gameObject->GetComponent<Game::Component::Character>();
        }

        void    Player::fixedUpdate(void)
        {
            
        }

        void    Player::update(void)
        {
            BeerEngine::Component::RigidBody2D *rb2d = _gameObject->GetComponent<BeerEngine::Component::RigidBody2D>();
            if (rb2d)
            {
                glm::vec2 dir(0.0f);
                if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_8))
                    dir += glm::vec2(0, 1);
                if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_5))
                    dir += glm::vec2(0, -1);
                if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_4))
                    dir += glm::vec2(1, 0);
                if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_6))
                    dir += glm::vec2(-1, 0);
                if (dir != glm::vec2(0.0f))
                    rb2d->velocity = glm::normalize(dir) * _character->_speed;
            }
            

            // if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_8))
            // {
            //     if (rb2d)
            //     {
            //         rb2d->velocity = glm::vec2(0, 5);
            //     }
            // }
				//_character->translate(_transform.forward());
            // if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_5))
			// 	_character->translate(-_transform.forward());
            // if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_4))
			// 	_character->translate(_transform.left());
            // if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::KP_6))
			// 	_character->translate(_transform.right());
            if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::KP_0))
				this->destroy();

            if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::KP_1))
            {
                _gameObject->destroy(this);
            }
        }

        void            Player::renderUI(struct nk_context *ctx)
        {
            if (nk_begin(ctx, "Player", nk_rect(10, 100, 220, 160), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE))
            {
                std::stringstream ss;
                ss << "Speed: " << _character->_speed;
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
                ss.str(std::string());
                ss.clear();
                ss << "Bomb: " << _character->_bombNb;
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
                ss.str(std::string());
                ss.clear();
                ss << "Size: " << _character->_explosionSize;
                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
            }    
            nk_end(ctx);
        }

        nlohmann::json	Player::serialize()
		{
			return nlohmann::json {
				{"componentClass", typeid(Player).name()},
			};
		}

        void Player::deserialize(const nlohmann::json & j)
    	{
            
		}

		REGISTER_COMPONENT_CPP(Player)
    }
}