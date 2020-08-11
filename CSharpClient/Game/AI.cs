using System;
using System.Collections.Generic;

using KoalaTeam.Chillin.Client;
using KS;
using KS.Commands;
using KS.Models;

using KSObject = KS.KSObject;

namespace Game
{
	public class AI : RealtimeAI<World, KSObject>
	{
		private readonly Random random = new Random();
		private int stage = 0;

		public AI(World world) : base(world)
		{
		}

		public override void Initialize()
		{
			Console.WriteLine("initialize");
		}

		public override void Decide()
		{
			Console.WriteLine("decide");

			var @base = World.Bases[this.MySide];
			var wagent = @base.Agents[AgentType.Warehouse];
			var fagent = @base.Agents[AgentType.Factory];

			if (stage == 0)
			{
				WarehouseAgentMove(forward: true);

				if (@base.CArea[wagent.Position] == ECell.Material)
				{
					var materialType = @base.Warehouse.Materials[wagent.Position].Type;
					if (wagent.MaterialsBag[materialType] == 0)
						WarehouseAgentPickMaterial();
				}
				else if (@base.CArea[wagent.Position] == ECell.BacklineDelivery)
				{
					WarehouseAgentPutMaterial();
					stage++;
				}
			}
			else if (stage == 1)
			{
				if (@base.CArea[fagent.Position] == ECell.BacklineDelivery)
				{
					var requiredMaterials = @base.Factory.CMixtureFormulas[AmmoType.RifleBullet];
					FactoryAgentPickMaterial(materials: requiredMaterials);
					stage++;
				}
				else
					FactoryAgentMove(forward: false);
			}
			else if (stage == 2)
			{
				if (@base.CArea[fagent.Position] == ECell.Machine &&
					@base.Factory.Machines[fagent.Position].Status == MachineStatus.Idle)
				{
					FactoryAgentPutMaterial(desiredAmmo: AmmoType.RifleBullet);
					stage++;
				}
				else
					FactoryAgentMove(forward: true);
			}
			else if (stage == 3)
			{
				if (@base.Factory.Machines[fagent.Position].Status == MachineStatus.AmmoReady)
				{
					FactoryAgentPickAmmo();
					stage++;
				}
			}
			else if (stage == 4)
			{
				if (@base.CArea[fagent.Position] == ECell.BacklineDelivery)
				{
					FactoryAgentPutAmmo();
					stage++;
				}
				else
					FactoryAgentMove(forward: false);
			}
			else if (stage == 5)
			{
				var ammos = new Dictionary<AmmoType, int>
				{
					{ AmmoType.RifleBullet, 1 }
				};
				WarehouseAgentPickAmmo(ammos: ammos);
				stage++;
			}
			else if (stage == 6)
			{
				if (@base.CArea[wagent.Position] == ECell.FrontlineDelivery)
				{
					WarehouseAgentPutAmmo();
					stage = 0;
				}
				else
					WarehouseAgentMove(forward: false);
			}
		}


		#region Warehouse Agent Commands

		public void WarehouseAgentMove(bool forward)
		{
			this.SendCommand(new Move() { AgentType = CommandAgentType.Warehouse, Forward = forward });
		}

		public void WarehouseAgentPickMaterial()
		{
			var materials = new Dictionary<CommandMaterialType?, int?>();
			this.SendCommand(new PickMaterial() { AgentType = CommandAgentType.Warehouse, Materials = materials });
		}

		public void WarehouseAgentPutMaterial()
		{
			this.SendCommand(new PutMaterial() { AgentType = CommandAgentType.Warehouse, DesiredAmmo = CommandAmmoType.RifleBullet });
		}

		public void WarehouseAgentPickAmmo(Dictionary<AmmoType, int> ammos)
		{
			var convertedAmmos = new Dictionary<CommandAmmoType?, int?>();
			foreach (var entry in ammos)
				convertedAmmos[(CommandAmmoType)entry.Key] = entry.Value;
			this.SendCommand(new PickAmmo() { AgentType = CommandAgentType.Warehouse, Ammos = convertedAmmos });
		}

		public void WarehouseAgentPutAmmo()
		{
			this.SendCommand(new PutAmmo() { AgentType = CommandAgentType.Warehouse });
		}

		#endregion

		#region Factory Agent Commands

		public void FactoryAgentMove(bool forward)
		{
			this.SendCommand(new Move() { AgentType = CommandAgentType.Factory, Forward = forward });
		}

		public void FactoryAgentPickMaterial(Dictionary<MaterialType?, int?> materials)
		{
			var convertedMaterials = new Dictionary<CommandMaterialType?, int?>();
			foreach (var entry in materials)
				convertedMaterials[(CommandMaterialType)entry.Key] = entry.Value;
			this.SendCommand(new PickMaterial() { AgentType = CommandAgentType.Factory, Materials = convertedMaterials });
		}

		public void FactoryAgentPutMaterial(AmmoType desiredAmmo)
		{
			this.SendCommand(new PutMaterial() { AgentType = CommandAgentType.Factory, DesiredAmmo = (CommandAmmoType)desiredAmmo });
		}

		public void FactoryAgentPickAmmo()
		{
			var ammos = new Dictionary<CommandAmmoType?, int?>();
			this.SendCommand(new PickAmmo() { AgentType = CommandAgentType.Factory, Ammos = ammos });
		}

		public void FactoryAgentPutAmmo()
		{
			this.SendCommand(new PutAmmo() { AgentType = CommandAgentType.Factory });
		}

		#endregion
	}
}
