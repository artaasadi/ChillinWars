#ifndef AI_H
#define AI_H

#include<map>

#include <ChillinClient>

#include "ks/models.h"
#include "ks/commands.h"


class AI : public koala::chillin::client::RealtimeAI<ks::models::World*>
{
public:
    AI(ks::models::World *world);
    ~AI();

    void initialize();
    void decide();

    void warehouseAgentMove(bool forward);
    void warehouseAgentPickMaterial();
    void warehouseAgentPutMaterial();
    void warehouseAgentPickAmmo(std::map<ks::models::AmmoType, int> ammos);
    void warehouseAgentPutAmmo();

    void factoryAgentMove(bool forward);
    void factoryAgentPickMaterial(std::map<ks::models::MaterialType, int> materials);
    void factoryAgentPutMaterial(ks::models::AmmoType desiredAmmo);
    void factoryAgentPickAmmo();
    void factoryAgentPutAmmo();

private:
    int stage = 0;
};

#endif // AI_H
