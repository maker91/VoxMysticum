#include "Entity.hpp"
#include "SoundEngine.hpp"

class Bat : public Entity
{
public:
	Bat(GameState &, const sf::Vector2f &pos);
	virtual ~Bat();

	void onCollide(Entity &other);
	void onHurt(int d);
	virtual void tick(float dt);

private:
	sf::Sound &flap;
};