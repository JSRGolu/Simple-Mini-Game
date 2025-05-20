#include "../../include/Components/PlayerStateComponent.h"
#include "../../include/components/SpriteSheetGraphicsComponent.h"
#include "../../include/components/SpriteGraphicsComponent.h"
#include "../../include/Components/GraphicsComponent.h"
#include "../../include/graphics/AnimBase.h"
#include <memory>

void PlayerState::update(Entity* entity, Game* game, float elapsed)
{
	Player* player = dynamic_cast<Player*>(entity);
	if (!player) return;

	auto velocityComp = player->getVelocity();

	if (shootCooldown > 0) {
		shootCooldown -= elapsed;
		if (shootCooldown < 0) {
			shootCooldown = 0;
		}
	}

}

void PlayerState::addWood(int w)
{
    wood += w;
    if (wood < 0) wood = 0;
    else if (wood > maxWood) wood = maxWood;
}