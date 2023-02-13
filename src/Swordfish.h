#include "Agent.h"
#include "Enemy.h"

class Swordfish final : public Enemy, public Agent
{
public:
    Swordfish();
    void Draw() override;
    void Update() override;
    void Clean() override;

private:
};