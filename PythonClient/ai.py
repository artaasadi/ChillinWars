# -*- coding: utf-8 -*-

# python imports
import random

# chillin imports
import time
from collections import Counter

from chillin_client import RealtimeAI

# project imports
from ks.models import ECell, MaterialType, AmmoType, AgentType, MachineStatus, Position, UnitType
from ks.commands import (Move, PickMaterial, PutMaterial, PickAmmo, PutAmmo,
                         CommandMaterialType, CommandAmmoType, CommandAgentType)


class orders:

    def __init__(self):
        self.orders_list = []
        self.required_materials_list = Counter({})
        self.fagent_orders = []

    # order az tariqe in tabe dade mishe k ham b liste ordera ezafe mikone ham materialaye morede niazesho ezafe mikone
    def add_order(self, base, order):
        self.orders_list += order
        self.compute_materials(base, order)

    # mohasebe mikone vase orderi k behesh dade shode b ch material haii niaz dare
    def compute_materials(self, base, order):
        gTank = Counter(base.factory.c_mixture_formulas[AmmoType.GoldenTankShell])
        rifBullet = Counter(base.factory.c_mixture_formulas[AmmoType.RifleBullet])
        mortShell = Counter(base.factory.c_mixture_formulas[AmmoType.MortarShell])
        hmgBull = Counter(base.factory.c_mixture_formulas[AmmoType.HMGBullet])
        tShell = Counter(base.factory.c_mixture_formulas[AmmoType.TankShell])
        goldenTank = Counter({})
        rifleBullet = Counter({})
        mortarShell = Counter({})
        hmgBullet = Counter({})
        tankShell = Counter({})
        for _ in range(order.count(AmmoType.GoldenTankShell)):
            goldenTank += gTank
        for _ in range(order.count(AmmoType.RifleBullet)):
            rifleBullet += rifBullet
        for _ in range(order.count(AmmoType.MortarShell)):
            mortarShell += mortShell
        for _ in range(order.count(AmmoType.HMGBullet)):
            hmgBullet += hmgBull
        for _ in range(order.count(AmmoType.TankShell)):
            tankShell += tShell
        sum = goldenTank + rifleBullet + mortarShell + hmgBullet + tankShell
        self.required_materials_list += sum
        return sum


class AI(RealtimeAI):

    def __init__(self, world):
        super(AI, self).__init__(world)
        self.orders = orders()
        self.wagent_ammo_loaded = False
        self.fagent_bag_is_full = False

    def initialize(self):
        print('initialize')
        base = self.world.bases[self.my_side]
        self.orders.add_order(base, [AmmoType.RifleBullet, AmmoType.RifleBullet, AmmoType.MortarShell])

    def decide(self):
        print('decide')
        base = self.world.bases[self.my_side]
        other_base = self.world.bases[self.other_side]
        print(base.units[UnitType.Soldier].health)
        # _________________________ Warehouse Agent Move Decision _________________________
        wagent = self.world.bases[self.my_side].agents[AgentType.Warehouse]
        current_wagent_position = base.c_area[wagent.position]

        # ------ Frontline Delivery
        if current_wagent_position == ECell.FrontlineDelivery:

            if self.wagent_ammo_loaded and sum(wagent.ammos_bag.values()) != 0:
                self.warehouse_agent_put_ammo()
                self.wagent_ammo_loaded = False
            else:
                self.warehouse_agent_move(forward=True)
                self.wagent_ammo_loaded = False

        # ------ Material
        elif current_wagent_position == ECell.Material:

            # age tiraro bardashti boro samte khune saritar
            if self.wagent_ammo_loaded:
                self.warehouse_agent_move(forward=False)

            # dar qheyre in surat vasayelo bardaro boro jolo
            else:
                material = base.warehouse.materials[wagent.position]
                if material.type in self.orders.required_materials_list and self.orders.required_materials_list[
                    material.type] != 0:
                    if material.count != 0:
                        self.warehouse_agent_pick_material()
                        self.orders.required_materials_list[material.type] -= 1
                    else:
                        self.warehouse_agent_move(forward=True)
                else:
                    self.warehouse_agent_move(forward=True)

        # ------ Backline Delivery
        elif current_wagent_position == ECell.BacklineDelivery:

            # materialaro bezar
            self.warehouse_agent_put_material()

            # age tiri hast bardar
            if sum(base.backline_delivery.ammos.values()) != 0:
                self.warehouse_agent_pick_ammo(ammos=base.backline_delivery.ammos)
                self.wagent_ammo_loaded = True

            # age nis faqat bargard
            elif sum(wagent.materials_bag.values()) == 0:
                self.wagent_ammo_loaded = True
                self.warehouse_agent_move(forward=False)
                if sum(self.orders.required_materials_list.values()) == 0:
                    print(other_base.units[UnitType.Soldier].health,
                          other_base.units[UnitType.HeavyMachineGunner].health,
                          other_base.units[UnitType.Mortar].health)
                    if (other_base.units[UnitType.Soldier].health + other_base.units[
                        UnitType.HeavyMachineGunner].health + other_base.units[UnitType.Mortar].health) > 1800:
                        if base.units[UnitType.Soldier].health > 800:
                            self.orders.add_order(base, [AmmoType.RifleBullet, AmmoType.MortarShell,
                                                         AmmoType.GoldenTankShell])
                        else:
                            self.orders.add_order(base,
                                                  [AmmoType.HMGBullet, AmmoType.MortarShell, AmmoType.GoldenTankShell])
                    else:
                        self.orders.add_order(base,
                                              [AmmoType.TankShell, AmmoType.MortarShell, AmmoType.GoldenTankShell])

        # _________________________ Factory Agent Move Decision _________________________
        fagent = self.world.bases[self.my_side].agents[AgentType.Factory]
        current_fagent_position = base.c_area[fagent.position]

        # ------ Backline Delivery
        if current_fagent_position == ECell.BacklineDelivery:

            # factory agent tiraii k sakhtaro bezare
            if sum(fagent.ammos_bag.values()) != 0:
                self.factory_agent_put_ammo()

            # factory agent vasayele vas sakhte order ro bardare ta jaii k mitune
            elif sum(fagent.ammos_bag.values()) == 0 and sum(base.backline_delivery.materials.values()) != 0:
                b = False
                i = 0

                # dune dune halataye momkene ordero check mikone k bbine vasayele marbut b kudum order ro mitune bardare
                while self.orders.orders_list != [] and i < len(self.orders.orders_list):

                    # in dict vas in sakhte shode chon baraye barresie inke aya mavad ye ammo dakhele anbar hast ya
                    # na az moqayeseye yek b yeke do list estefade mikonam
                    o = base.factory.c_mixture_formulas[self.orders.orders_list[i]]
                    temp_dict = {MaterialType.Powder: 0 if MaterialType.Powder not in o else o[MaterialType.Powder],
                                 MaterialType.Iron: 0 if MaterialType.Iron not in o else o[MaterialType.Iron],
                                 MaterialType.Carbon: 0 if MaterialType.Carbon not in o else o[MaterialType.Carbon],
                                 MaterialType.Gold: 0 if MaterialType.Gold not in o else o[MaterialType.Gold],
                                 MaterialType.Shell: 0 if MaterialType.Shell not in o else o[MaterialType.Shell]}

                    # check mikone age ja dare bardare
                    if sum(base.factory.c_mixture_formulas[self.orders.orders_list[i]].values()) + sum(
                            fagent.materials_bag.values()) <= 15 and list(temp_dict.values()) <= list(
                        base.backline_delivery.materials.values()):
                        self.factory_agent_pick_material(base.factory.c_mixture_formulas[self.orders.orders_list[i]])
                        b = True
                        self.orders.fagent_orders.append(self.orders.orders_list[i])
                        del self.orders.orders_list[i]
                        break
                    else:
                        i += 1
                        continue
                # in vas ine k age did hichi nmitune bardare va daliliam vas raftan dare pashe bere
                if not b and (MachineStatus.AmmoReady in list(
                        machine.status for machine in base.factory.machines.values()) or (
                                      self.orders.fagent_orders != [] and MachineStatus.Idle in list(
                                  machine.status for machine in base.factory.machines.values()))):
                    self.factory_agent_move(forward=True)

            # age kif por shod ya vasayele backline delivery tamum shod boro bezareshun tu karkhune
            elif (sum(base.backline_delivery.materials.values()) == 0 or self.fagent_bag_is_full == True) and ((
                                                                                                                       self.orders.fagent_orders != [] and MachineStatus.Idle in list(
                                                                                                                   machine.status
                                                                                                                   for
                                                                                                                   machine
                                                                                                                   in
                                                                                                                   base.factory.machines.values())) or MachineStatus.AmmoReady in list(
                machine.status for machine in base.factory.machines.values())):
                self.factory_agent_move(forward=True)

                # ------ Factory
        elif current_fagent_position == ECell.Machine:

            # Idle
            if base.factory.machines[fagent.position].status == MachineStatus.Idle:

                # age order dare bezare
                if self.orders.fagent_orders != []:
                    self.factory_agent_put_material(self.orders.fagent_orders.pop(0))

                # age order nadare ...
                elif self.orders.fagent_orders == []:

                    # age kifesh pore bere samte khune
                    if sum(fagent.ammos_bag.values()) == 5:
                        self.factory_agent_move(forward=False)

                        # inja k bikare pas age did jaye dg tir amade hast bere bardare
                    elif MachineStatus.AmmoReady in list(machine.status for machine in base.factory.machines.values()):
                        if fagent.position.index == 7:
                            self.factory_agent_move(forward=True)
                        elif fagent.position.index == 9:
                            self.factory_agent_move(forward=False)
                        elif fagent.position.index == 8:
                            if base.factory.machines[Position(7)].status == MachineStatus.AmmoReady:
                                self.factory_agent_move(forward=False)
                            elif base.factory.machines[Position(9)].status == MachineStatus.AmmoReady:
                                self.factory_agent_move(forward=True)

                    else:
                        self.factory_agent_move(forward=False)

            # Ammo Ready
            elif base.factory.machines[fagent.position].status == MachineStatus.AmmoReady:

                # age ja dare bardare
                if sum(fagent.ammos_bag.values()) < 5:
                    self.factory_agent_pick_ammo()

                # age ja nadare bere samte khune
                elif sum(fagent.ammos_bag.values()) == 5:
                    self.factory_agent_move(forward=False)

                    # Working
            elif base.factory.machines[fagent.position].status == MachineStatus.Working:

                # age kifesh pore bere samte khune
                if sum(fagent.ammos_bag.values()) == 5:
                    self.factory_agent_move(forward=False)

                # age tire amade atraf hast bere samtesh
                elif MachineStatus.AmmoReady in list(machine.status for machine in base.factory.machines.values()):
                    print('1')
                    if fagent.position.index == 7:
                        self.factory_agent_move(forward=True)
                    elif fagent.position.index == 9:
                        self.factory_agent_move(forward=False)
                    elif fagent.position.index == 8:
                        print('2')
                        if base.factory.machines[Position(7)].status == MachineStatus.AmmoReady:
                            print('3')
                            self.factory_agent_move(forward=False)
                        elif base.factory.machines[Position(9)].status == MachineStatus.AmmoReady:
                            print('4')
                            self.factory_agent_move(forward=True)

                # age order dareo jaii hast ordero bezare bere samtesh
                elif self.orders.fagent_orders != [] and MachineStatus.Idle in list(
                        machine.status for machine in base.factory.machines.values()):

                    if fagent.position.index == 7:
                        self.factory_agent_move(forward=True)
                    elif fagent.position.index == 9:
                        self.factory_agent_move(forward=False)
                    else:
                        if base.factory.machines[Position(7)].status == MachineStatus.Idle:
                            self.factory_agent_move(forward=False)
                        elif base.factory.machines[Position(9)].status == MachineStatus.Idle:
                            self.factory_agent_move(forward=True)

                # age hich kari nabudo tir dasht vas khali kardan bere samte khune
                elif sum(fagent.ammos_bag.values()) != 0:
                    self.factory_agent_move(forward=False)

                # age hich kari nabudo vasile umade bud tu khune bere samte khune
                elif sum(base.backline_delivery.materials.values()) != 0:
                    self.factory_agent_move(forward=False)

            elif self.orders.fagent_orders == [] and (
                    MachineStatus.Idle not in base.factory.machines.status or sum(fagent.ammos_bag.values()) == 5):
                self.factory_agent_move(forward=False)

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
