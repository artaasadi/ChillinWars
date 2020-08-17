# -*- coding: utf-8 -*-

# python imports
import random

# chillin imports
import time
from collections import Counter

from chillin_client import RealtimeAI

# project imports
from ks.models import ECell, MaterialType, AmmoType, AgentType, MachineStatus
from ks.commands import (Move, PickMaterial, PutMaterial, PickAmmo, PutAmmo,
                         CommandMaterialType, CommandAmmoType, CommandAgentType)


class AI(RealtimeAI):

    def __init__(self, world):
        super(AI, self).__init__(world)
        self.stage = 0

    def initialize(self):
        print('initialize')

    def decide(self):
        print('decide')

        world = self.world
        base = world.bases[self.my_side]
        wagent = base.agents[AgentType.Warehouse]
        fagent = base.agents[AgentType.Factory]

        # Inja dictionary haro mirizam too moteghayerash
        goldenTank = Counter(self.world.bases[self.my_side].factory.c_mixture_formulas[AmmoType.GoldenTankShell])
        rifleBullet = Counter(self.world.bases[self.my_side].factory.c_mixture_formulas[AmmoType.RifleBullet])
        mortarShell = Counter(self.world.bases[self.my_side].factory.c_mixture_formulas[AmmoType.MortarShell])
        hmgBullet = Counter(self.world.bases[self.my_side].factory.c_mixture_formulas[AmmoType.HMGBullet])
        tankShell = Counter(self.world.bases[self.my_side].factory.c_mixture_formulas[AmmoType.TankShell])

        # inja jam mizanam ke jolo tar azash estefade konim
        required_materials = goldenTank + tankShell

        if self.stage == 0:
            self.warehouse_agent_move(forward=True)
            if base.c_area[wagent.position] == ECell.Material:
                material_type = base.warehouse.materials[wagent.position].type
                if material_type in required_materials and wagent.materials_bag[material_type] != required_materials[
                    material_type]:
                    self.warehouse_agent_pick_material()
            elif base.c_area[wagent.position] == ECell.BacklineDelivery:
                self.warehouse_agent_put_material()
                self.stage += 1

        elif self.stage == 1:
            if base.c_area[fagent.position] == ECell.BacklineDelivery:
                self.factory_agent_pick_material(materials=required_materials)
                self.stage += 1
            else:
                self.factory_agent_move(forward=False)

        elif self.stage == 2:
            if (base.c_area[fagent.position] == ECell.Machine and
                    base.factory.machines[fagent.position].status == MachineStatus.Idle):
                self.factory_agent_put_material(desired_ammo=AmmoType.TankShell)
                self.stage = 98
            else:
                self.factory_agent_move(forward=True)

        elif self.stage == 98:
            if (base.c_area[fagent.position] == ECell.Machine and
                    base.factory.machines[fagent.position].status == MachineStatus.Idle):
                self.factory_agent_put_material(desired_ammo=AmmoType.GoldenTankShell)
                self.stage = 97
            else:
                self.factory_agent_move(forward=True)

        elif self.stage == 97:
            self.warehouse_agent_move(forward=True)
            if base.c_area[wagent.position] == ECell.Material:
                material_type = base.warehouse.materials[wagent.position].type
                if material_type in required_materials and wagent.materials_bag[material_type] != required_materials[
                    material_type]:
                    self.warehouse_agent_pick_material()
            elif base.c_area[wagent.position] == ECell.BacklineDelivery:
                self.warehouse_agent_put_material()

            if base.c_area[fagent.position] == ECell.Machine and base.factory.machines[
                fagent.position].status != MachineStatus.Idle:
                if base.factory.machines[fagent.position].status == MachineStatus.AmmoReady:
                    self.factory_agent_pick_ammo()
            else:
                self.factory_agent_move(forward=False)
            if base.c_area[fagent.position] == ECell.BacklineDelivery:
                self.factory_agent_put_ammo()

            if base.c_area[wagent.position] == ECell.BacklineDelivery and base.c_area[
                fagent.position] == ECell.BacklineDelivery:
                self.stage = 96

        elif self.stage == 96:
            if base.c_area[wagent.position] == ECell.BacklineDelivery:
                self.warehouse_agent_pick_ammo(ammos={AmmoType.GoldenTankShell: 1, AmmoType.TankShell: 1})
                self.stage = 95

        elif self.stage == 95:
            if base.c_area[wagent.position] == ECell.FrontlineDelivery:
                self.warehouse_agent_put_ammo()
                self.stage = 0
            else:
                self.warehouse_agent_move(forward=False)

    # Warehouse Agent Commands

    def warehouse_agent_move(self, forward):
        self.send_command(Move(agent_type=CommandAgentType.Warehouse, forward=forward))

    def warehouse_agent_pick_material(self):
        self.send_command(PickMaterial(agent_type=CommandAgentType.Warehouse, materials={}))

    def warehouse_agent_put_material(self):
        self.send_command(PutMaterial(agent_type=CommandAgentType.Warehouse, desired_ammo=CommandAmmoType.RifleBullet))

    def warehouse_agent_pick_ammo(self, ammos):
        self.send_command(PickAmmo(agent_type=CommandAgentType.Warehouse, ammos=ammos))

    def warehouse_agent_put_ammo(self):
        self.send_command(PutAmmo(agent_type=CommandAgentType.Warehouse))

    # Factory Agent Commands

    def factory_agent_move(self, forward):
        self.send_command(Move(agent_type=CommandAgentType.Factory, forward=forward))

    def factory_agent_pick_material(self, materials):
        self.send_command(PickMaterial(agent_type=CommandAgentType.Factory, materials=materials))

    def factory_agent_put_material(self, desired_ammo):
        self.send_command(PutMaterial(agent_type=CommandAgentType.Factory, desired_ammo=desired_ammo))

    def factory_agent_pick_ammo(self):
        self.send_command(PickAmmo(agent_type=CommandAgentType.Factory, ammos={}))

    def factory_agent_put_ammo(self):
        self.send_command(PutAmmo(agent_type=CommandAgentType.Factory))
