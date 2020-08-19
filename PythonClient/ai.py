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
        self.fagent_bag_is_full = False
        self.wagent_ammo_loaded = False
        self.orders = orders()

    def initialize(self):
        print('initialize')
        base = self.world.bases[self.my_side]
        self.orders.add_order(base, [AmmoType.RifleBullet, AmmoType.RifleBullet, AmmoType.MortarShell])

        # Detecting map
        if base.units[UnitType.GoldenTank].health == 0:
            if base.units[UnitType.Tank].health == 0:
                my_map = 'WhoNeedsTank'
            else:
                my_map = 'Artileryyyy'
        elif base.units[UnitType.HeavyMachineGunner].health == 0:
            my_map = 'PanzerStorm'
        elif self.world.max_cycles == 150:
            my_map = 'NoTime'
        else:
            my_map = 'Allin'

    def decide(self):
        print('decide')
        base = self.world.bases[self.my_side]
        other_base = self.world.bases[self.other_side]

        # _________________________ Warehouse Agent Move Decision _________________________
        wagent = self.world.bases[self.my_side].agents[AgentType.Warehouse]
        current_wagent_position = base.c_area[wagent.position]

        # age order nadasht ezafe kone
        if current_wagent_position == ECell.FrontlineDelivery or wagent.position.index == 1:
            if AmmoType.RifleBullet not in self.orders.orders_list and AmmoType.MortarShell not in self.orders.orders_list and AmmoType.TankShell not in self.orders.orders_list and AmmoType.HMGBullet not in self.orders.orders_list and AmmoType.GoldenTankShell in self.orders.orders_list:
                if base.warehouse.materials[Position(4)].count == 0:
                    if (other_base.units[UnitType.Soldier].health + other_base.units[
                        UnitType.HeavyMachineGunner].health + other_base.units[UnitType.Mortar].health) > 1800:
                        if base.units[UnitType.Soldier].health > 800:
                            self.orders.add_order(base, [AmmoType.RifleBullet, AmmoType.MortarShell])
                        else:
                            self.orders.add_order(base, [AmmoType.HMGBullet, AmmoType.MortarShell])
                    else:
                        self.orders.add_order(base, [AmmoType.TankShell, AmmoType.MortarShell])

        # ------ Frontline Delivery
        if current_wagent_position == ECell.FrontlineDelivery:

            if self.wagent_ammo_loaded == True and sum(wagent.ammos_bag.values()) != 0:
                self.warehouse_agent_put_ammo()
                self.wagent_ammo_loaded = False
            else:
                self.warehouse_agent_move(forward=True)
                self.wagent_ammo_loaded = False


        # ------ Material
        elif current_wagent_position == ECell.Material:

            # age tiraro bardashti boro samte khune saritar
            if (self.wagent_ammo_loaded == True) and (
                    (sum(wagent.ammos_bag.values()) == 0 and wagent.position.index != 1) or (
                    sum(wagent.ammos_bag.values()) != 0)):
                self.warehouse_agent_move(forward=False)

            elif (self.wagent_ammo_loaded == True) and sum(
                    wagent.ammos_bag.values()) == 0 and wagent.position.index == 1:
                self.wagent_ammo_loaded = False
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


            # dar qeyre in surat vasayelo bardaro boro jolo
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

        if wagent.position == Position(5) and sum(wagent.materials_bag.values()) == 0 and self.wagent_ammo_loaded:
            if sum(self.orders.required_materials_list.values()) == 0:

                # Inja amir ezafe karde
                # vase mohasebe ghodrate tirha. shayad bedard khord

                amir_ammo = []
                if base.units[UnitType.GoldenTank].health == 0 or self.current_cycle + 20 >= self.world.max_cycles:
                    golden_tank_damage = 0
                else:
                    golden_tank_damage = min(other_base.units[UnitType.GoldenTank].health, 1200) + \
                                         min(other_base.units[UnitType.Tank].health, 1200) + \
                                         min(other_base.units[UnitType.Soldier].health, 400) + \
                                         min(other_base.units[UnitType.Mortar].health, 800) + \
                                         min(other_base.units[UnitType.HeavyMachineGunner].health, 400)

                if base.units[UnitType.Mortar].health == 0:
                    mortar_damage = 0
                else:
                    mortar_damage = min(other_base.units[UnitType.GoldenTank].health, 80) + \
                                    min(other_base.units[UnitType.Tank].health, 240) + \
                                    min(other_base.units[UnitType.Soldier].health, 160) + \
                                    min(other_base.units[UnitType.Mortar].health, 160) + \
                                    min(other_base.units[UnitType.HeavyMachineGunner].health, 160)

                if base.units[UnitType.HeavyMachineGunner].health == 0:
                    hmg_damage = 0
                else:
                    hmg_damage = min(other_base.units[UnitType.Soldier].health, 8 * 150) + \
                                 min(other_base.units[UnitType.Mortar].health, 8 * 150) + \
                                 min(other_base.units[UnitType.HeavyMachineGunner].health, 4 * 150)

                if base.units[UnitType.Tank].health == 0:
                    tank_damage = 0
                else:
                    tank_damage = min(other_base.units[UnitType.GoldenTank].health, 1200) + \
                                  min(other_base.units[UnitType.Tank].health, 1200) + \
                                  min(other_base.units[UnitType.Soldier].health, 400) + \
                                  min(other_base.units[UnitType.Mortar].health, 800) + \
                                  min(other_base.units[UnitType.HeavyMachineGunner].health, 400)

                if base.units[UnitType.Soldier].health == 0:
                    soldier_damage = 0
                else:
                    soldier_damage = min(other_base.units[UnitType.Soldier].health, 12 * 75) + \
                                     min(other_base.units[UnitType.Mortar].health, 6 * 75) + \
                                     min(other_base.units[UnitType.HeavyMachineGunner].health, 2 * 75)

                ammo_quality = [[AmmoType.GoldenTankShell, golden_tank_damage],
                                [AmmoType.MortarShell, mortar_damage], [AmmoType.HMGBullet, hmg_damage],
                                [AmmoType.TankShell, tank_damage], [AmmoType.RifleBullet, soldier_damage]]

                ammo_quality = sorted(ammo_quality, key=lambda l: l[1], reverse=True)
                amir_ammo.append(ammo_quality[0][0])
                amir_ammo.append(ammo_quality[1][0])
                amir_ammo.append(ammo_quality[2][0])

                # Ta inja (codi ke amir ezafe karde)
                if (other_base.units[UnitType.Soldier].health + other_base.units[UnitType.HeavyMachineGunner].health +
                    other_base.units[UnitType.Mortar].health) > 1800:
                    if base.units[UnitType.Soldier].health > 1200:
                        self.orders.add_order(base,
                                              [AmmoType.GoldenTankShell, AmmoType.RifleBullet, AmmoType.MortarShell])
                    else:
                        self.orders.add_order(base,
                                              [AmmoType.GoldenTankShell, AmmoType.HMGBullet, AmmoType.MortarShell])
                else:
                    self.orders.add_order(base, [AmmoType.GoldenTankShell, AmmoType.TankShell, AmmoType.MortarShell])

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

                # ye list k material haye morede niazio hesab kone hamaro baham bardare k vaqt talaf nashe
                if 'temp_materials_list' not in globals():
                    temp_materials_list = Counter({})
                # fazaye eshqal shodeye farzie kif
                bag_capacity = sum(fagent.materials_bag.values())
                # b (mokhafafe boolean) check mikone k aya tu in marhale materiali bardashte shod ya kheir ?
                b = False
                # serfan ye indexe
                i = 0

                # dune dune halataye momkene ordero check mikone k bbine vasayele marbut b kudum order ro mitune bardare
                while self.orders.orders_list != [] and i < len(self.orders.orders_list):

                    # in dict vas in sakhte shode chon baraye barresie inke aya mavade ye ammo dakhele anbar hast ya na az moqayeseye yek b yeke do list estefade mikonam
                    o = base.factory.c_mixture_formulas[self.orders.orders_list[i]]
                    temp_dict = {MaterialType.Powder: 0 if MaterialType.Powder not in o else o[MaterialType.Powder],
                                 MaterialType.Iron: 0 if MaterialType.Iron not in o else o[MaterialType.Iron],
                                 MaterialType.Carbon: 0 if MaterialType.Carbon not in o else o[MaterialType.Carbon],
                                 MaterialType.Gold: 0 if MaterialType.Gold not in o else o[MaterialType.Gold],
                                 MaterialType.Shell: 0 if MaterialType.Shell not in o else o[MaterialType.Shell]}

                    # check mikone age ja dare bardare
                    if sum(base.factory.c_mixture_formulas[
                               self.orders.orders_list[i]].values()) + bag_capacity <= 15 and list(
                        temp_dict.values()) <= list(base.backline_delivery.materials.values()):
                        bag_capacity += sum(base.factory.c_mixture_formulas[self.orders.orders_list[i]].values())
                        temp_materials_list += Counter(temp_dict)
                        b = True
                        self.orders.fagent_orders.append(self.orders.orders_list[i])
                        del self.orders.orders_list[i]
                        continue
                    else:
                        i += 1
                        continue

                if b:
                    self.factory_agent_pick_material(temp_materials_list)
                    temp_materials_list = Counter({})
                    b = False

                # in vas ine k age did hichi nmitune bardare va daliliam vas raftan dare pashe bere
                elif (MachineStatus.AmmoReady in list(machine.status for machine in base.factory.machines.values()) or (
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
                if self.orders.fagent_orders:
                    self.factory_agent_put_material(self.orders.fagent_orders.pop(0))

                # age order nadare ...
                elif not self.orders.fagent_orders:

                    # age kifesh pore bere samte khune
                    if sum(fagent.ammos_bag.values()) == 5:
                        self.factory_agent_move(forward=False)

                        # inja k bikare pas age did jaye dg tir amade hast bere bardare
                    elif (MachineStatus.AmmoReady in list(
                            machine.status for machine in base.factory.machines.values())) or base.factory.machines[
                        Position(7)].construction_rem_time == 1 or base.factory.machines[
                        Position(8)].construction_rem_time == 1 or base.factory.machines[
                        Position(9)].construction_rem_time == 1:

                        if fagent.position.index == 7:
                            self.factory_agent_move(forward=True)
                        elif fagent.position.index == 9:
                            self.factory_agent_move(forward=False)
                        elif fagent.position.index == 8:
                            if base.factory.machines[Position(7)].status == MachineStatus.AmmoReady:
                                self.factory_agent_move(forward=False)
                            elif base.factory.machines[Position(9)].status == MachineStatus.AmmoReady:
                                self.factory_agent_move(forward=True)
                            elif base.factory.machines[Position(7)].construction_rem_time == 1:
                                self.factory_agent_move(forward=False)
                            elif base.factory.machines[Position(9)].construction_rem_time == 1:
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

                # age mibini dg dare amade mishe bemun
                elif base.factory.machines[Position(7)].construction_rem_time == 1:
                    pass

                # age tire amade atraf hast bere samtesh
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
