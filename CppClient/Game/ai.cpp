#include "ai.h"

#include <iostream>
#include <vector>
#include <map>

#include "effolkronium/random.hpp"

using namespace std;
using Random = effolkronium::random_static;

using namespace koala::chillin::client;
using namespace ks::models;
using namespace ks::commands;


AI::AI(World *world): RealtimeAI<World*>(world)
{
}

AI::~AI()
{
}

void AI::initialize()
{
    cout << "initialize" << endl;
}

void AI::decide()
{
    cout << "decide" << endl;

    auto base = this->world->bases()[this->mySide];
    auto wagent = base.agents()[AgentType::Warehouse];
    auto fagent = base.agents()[AgentType::Factory];

    if (stage == 0)
    {
        warehouseAgentMove(true);

        if (base.cArea()[wagent.position()] == ECell::Material)
        {
            auto materialType = base.warehouse().materials()[wagent.position()].type();
            if (wagent.materialsBag()[materialType] == 0)
                warehouseAgentPickMaterial();
        }
        else if (base.cArea()[wagent.position()] == ECell::BacklineDelivery)
        {
            warehouseAgentPutMaterial();
            stage++;
        }
    }
    else if (stage == 1)
    {
        if (base.cArea()[fagent.position()] == ECell::BacklineDelivery)
        {
			map<MaterialType, int> requiredMaterials = base.factory().cMixtureFormulas()[AmmoType::RifleBullet];
            factoryAgentPickMaterial(requiredMaterials);
            stage++;
        }
        else
            factoryAgentMove(false);
    }
    else if (stage == 2)
    {
        if (base.cArea()[fagent.position()] == ECell::Machine &&
            base.factory().machines()[fagent.position()].status() == MachineStatus::Idle)
        {
            factoryAgentPutMaterial(AmmoType::RifleBullet);
            stage++;
        }
        else
            factoryAgentMove(true);
    }
    else if (stage == 3)
    {
        if (base.factory().machines()[fagent.position()].status() == MachineStatus::AmmoReady)
        {
            factoryAgentPickAmmo();
            stage++;
        }
    }
    else if (stage == 4)
    {
        if (base.cArea()[fagent.position()] == ECell::BacklineDelivery)
        {
            factoryAgentPutAmmo();
            stage++;
        }
        else
            factoryAgentMove(false);
    }
    else if (stage == 5)
    {
        map<AmmoType, int> ammos;
        ammos[AmmoType::RifleBullet] = 1;

        warehouseAgentPickAmmo(ammos);
        stage++;
    }
    else if (stage == 6)
    {
        if (base.cArea()[wagent.position()] == ECell::FrontlineDelivery)
        {
            warehouseAgentPutAmmo();
            stage = 0;
        }
        else
            warehouseAgentMove(false);
    }
}


// Warehouse Agent Commands

void AI::warehouseAgentMove(bool forward)
{
    Move cmd;
    cmd.agentType(CommandAgentType::Warehouse);
    cmd.forward(forward);
    this->sendCommand(&cmd);
}

void AI::warehouseAgentPickMaterial()
{
    PickMaterial cmd;
    cmd.agentType(CommandAgentType::Warehouse);
    cmd.has_materials(true);
    this->sendCommand(&cmd);
}

void AI::warehouseAgentPutMaterial()
{
    PutMaterial cmd;
    cmd.agentType(CommandAgentType::Warehouse);
    cmd.has_desiredAmmo(true);
    this->sendCommand(&cmd);
}

void AI::warehouseAgentPickAmmo(map<AmmoType, int> ammos)
{
    map<CommandAmmoType, int> convertedAmmos;
    for (auto entry : ammos)
        convertedAmmos[CommandAmmoType(entry.first)] = entry.second;

    PickAmmo cmd;
    cmd.agentType(CommandAgentType::Warehouse);
    cmd.ammos(convertedAmmos);
    this->sendCommand(&cmd);
}

void AI::warehouseAgentPutAmmo()
{
    PutAmmo cmd;
    cmd.agentType(CommandAgentType::Warehouse);
    this->sendCommand(&cmd);
}


// Factory Agent Commands

void AI::factoryAgentMove(bool forward)
{
    Move cmd;
    cmd.agentType(CommandAgentType::Factory);
    cmd.forward(forward);
    this->sendCommand(&cmd);
}

void AI::factoryAgentPickMaterial(map<MaterialType, int> materials)
{
    map<CommandMaterialType, int> convertedMaterials;
    for (auto entry : materials)
        convertedMaterials[CommandMaterialType(entry.first)] = entry.second;

    PickMaterial cmd;
    cmd.agentType(CommandAgentType::Factory);
    cmd.materials(convertedMaterials);
    this->sendCommand(&cmd);
}

void AI::factoryAgentPutMaterial(AmmoType desiredAmmo)
{
    PutMaterial cmd;
    cmd.agentType(CommandAgentType::Factory);
    cmd.desiredAmmo(CommandAmmoType(desiredAmmo));
    this->sendCommand(&cmd);
}

void AI::factoryAgentPickAmmo()
{
    PickAmmo cmd;
    cmd.agentType(CommandAgentType::Factory);
    cmd.has_ammos(true);
    this->sendCommand(&cmd);
}

void AI::factoryAgentPutAmmo()
{
    PutAmmo cmd;
    cmd.agentType(CommandAgentType::Factory);
    this->sendCommand(&cmd);
}
