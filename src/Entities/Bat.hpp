#include "Hurtable.hpp"
#include "SoundEngine.hpp"

class Bat : public Hurtable
{
public:
	Bat(GameState &, const sf::Vector2f &pos);
	virtual ~Bat()=default;

	void onCollide(Entity &other);
	void onHurt(int d);
	virtual void tick(float dt);

private:
	float nextflap;
};