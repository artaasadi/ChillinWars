using System;
using System.Linq;
using System.Collections.Generic;

namespace KS.Commands
{
	public enum CommandMaterialType
	{
		Powder = 0,
		Iron = 1,
		Carbon = 2,
		Gold = 3,
		Shell = 4,
	}
	
	public enum CommandAmmoType
	{
		RifleBullet = 0,
		TankShell = 1,
		HMGBullet = 2,
		MortarShell = 3,
		GoldenTankShell = 4,
	}
	
	public enum CommandAgentType
	{
		Warehouse = 0,
		Factory = 1,
	}
	
	public partial class BaseCommand : KSObject
	{
		public CommandAgentType? AgentType { get; set; }
		

		public BaseCommand()
		{
		}
		
		public new const string NameStatic = "BaseCommand";
		
		public override string Name() => "BaseCommand";
		
		public override byte[] Serialize()
		{
			List<byte> s = new List<byte>();
			
			// serialize AgentType
			s.Add((byte)((AgentType == null) ? 0 : 1));
			if (AgentType != null)
			{
				s.Add((byte)((sbyte)AgentType));
			}
			
			return s.ToArray();
		}
		
		public override uint Deserialize(byte[] s, uint offset = 0)
		{
			// deserialize AgentType
			byte tmp0;
			tmp0 = (byte)s[(int)offset];
			offset += sizeof(byte);
			if (tmp0 == 1)
			{
				sbyte tmp1;
				tmp1 = (sbyte)s[(int)offset];
				offset += sizeof(sbyte);
				AgentType = (CommandAgentType)tmp1;
			}
			else
				AgentType = null;
			
			return offset;
		}
	}
	
	public partial class Move : BaseCommand
	{
		public bool? Forward { get; set; }
		

		public Move()
		{
		}
		
		public new const string NameStatic = "Move";
		
		public override string Name() => "Move";
		
		public override byte[] Serialize()
		{
			List<byte> s = new List<byte>();
			
			// serialize parents
			s.AddRange(base.Serialize());
			
			// serialize Forward
			s.Add((byte)((Forward == null) ? 0 : 1));
			if (Forward != null)
			{
				s.AddRange(BitConverter.GetBytes((bool)Forward));
			}
			
			return s.ToArray();
		}
		
		public override uint Deserialize(byte[] s, uint offset = 0)
		{
			// deserialize parents
			offset = base.Deserialize(s, offset);
			
			// deserialize Forward
			byte tmp2;
			tmp2 = (byte)s[(int)offset];
			offset += sizeof(byte);
			if (tmp2 == 1)
			{
				Forward = BitConverter.ToBoolean(s, (int)offset);
				offset += sizeof(bool);
			}
			else
				Forward = null;
			
			return offset;
		}
	}
	
	public partial class PickMaterial : BaseCommand
	{
		public Dictionary<CommandMaterialType?, int?> Materials { get; set; }
		

		public PickMaterial()
		{
		}
		
		public new const string NameStatic = "PickMaterial";
		
		public override string Name() => "PickMaterial";
		
		public override byte[] Serialize()
		{
			List<byte> s = new List<byte>();
			
			// serialize parents
			s.AddRange(base.Serialize());
			
			// serialize Materials
			s.Add((byte)((Materials == null) ? 0 : 1));
			if (Materials != null)
			{
				List<byte> tmp3 = new List<byte>();
				tmp3.AddRange(BitConverter.GetBytes((uint)Materials.Count()));
				while (tmp3.Count > 0 && tmp3.Last() == 0)
					tmp3.RemoveAt(tmp3.Count - 1);
				s.Add((byte)tmp3.Count);
				s.AddRange(tmp3);
				
				foreach (var tmp4 in Materials)
				{
					s.Add((byte)((tmp4.Key == null) ? 0 : 1));
					if (tmp4.Key != null)
					{
						s.Add((byte)((sbyte)tmp4.Key));
					}
					
					s.Add((byte)((tmp4.Value == null) ? 0 : 1));
					if (tmp4.Value != null)
					{
						s.AddRange(BitConverter.GetBytes((int)tmp4.Value));
					}
				}
			}
			
			return s.ToArray();
		}
		
		public override uint Deserialize(byte[] s, uint offset = 0)
		{
			// deserialize parents
			offset = base.Deserialize(s, offset);
			
			// deserialize Materials
			byte tmp5;
			tmp5 = (byte)s[(int)offset];
			offset += sizeof(byte);
			if (tmp5 == 1)
			{
				byte tmp6;
				tmp6 = (byte)s[(int)offset];
				offset += sizeof(byte);
				byte[] tmp7 = new byte[sizeof(uint)];
				Array.Copy(s, offset, tmp7, 0, tmp6);
				offset += tmp6;
				uint tmp8;
				tmp8 = BitConverter.ToUInt32(tmp7, (int)0);
				
				Materials = new Dictionary<CommandMaterialType?, int?>();
				for (uint tmp9 = 0; tmp9 < tmp8; tmp9++)
				{
					CommandMaterialType? tmp10;
					byte tmp12;
					tmp12 = (byte)s[(int)offset];
					offset += sizeof(byte);
					if (tmp12 == 1)
					{
						sbyte tmp13;
						tmp13 = (sbyte)s[(int)offset];
						offset += sizeof(sbyte);
						tmp10 = (CommandMaterialType)tmp13;
					}
					else
						tmp10 = null;
					
					int? tmp11;
					byte tmp14;
					tmp14 = (byte)s[(int)offset];
					offset += sizeof(byte);
					if (tmp14 == 1)
					{
						tmp11 = BitConverter.ToInt32(s, (int)offset);
						offset += sizeof(int);
					}
					else
						tmp11 = null;
					
					Materials[tmp10] = tmp11;
				}
			}
			else
				Materials = null;
			
			return offset;
		}
	}
	
	public partial class PutMaterial : BaseCommand
	{
		public CommandAmmoType? DesiredAmmo { get; set; }
		

		public PutMaterial()
		{
		}
		
		public new const string NameStatic = "PutMaterial";
		
		public override string Name() => "PutMaterial";
		
		public override byte[] Serialize()
		{
			List<byte> s = new List<byte>();
			
			// serialize parents
			s.AddRange(base.Serialize());
			
			// serialize DesiredAmmo
			s.Add((byte)((DesiredAmmo == null) ? 0 : 1));
			if (DesiredAmmo != null)
			{
				s.Add((byte)((sbyte)DesiredAmmo));
			}
			
			return s.ToArray();
		}
		
		public override uint Deserialize(byte[] s, uint offset = 0)
		{
			// deserialize parents
			offset = base.Deserialize(s, offset);
			
			// deserialize DesiredAmmo
			byte tmp15;
			tmp15 = (byte)s[(int)offset];
			offset += sizeof(byte);
			if (tmp15 == 1)
			{
				sbyte tmp16;
				tmp16 = (sbyte)s[(int)offset];
				offset += sizeof(sbyte);
				DesiredAmmo = (CommandAmmoType)tmp16;
			}
			else
				DesiredAmmo = null;
			
			return offset;
		}
	}
	
	public partial class PickAmmo : BaseCommand
	{
		public Dictionary<CommandAmmoType?, int?> Ammos { get; set; }
		

		public PickAmmo()
		{
		}
		
		public new const string NameStatic = "PickAmmo";
		
		public override string Name() => "PickAmmo";
		
		public override byte[] Serialize()
		{
			List<byte> s = new List<byte>();
			
			// serialize parents
			s.AddRange(base.Serialize());
			
			// serialize Ammos
			s.Add((byte)((Ammos == null) ? 0 : 1));
			if (Ammos != null)
			{
				List<byte> tmp17 = new List<byte>();
				tmp17.AddRange(BitConverter.GetBytes((uint)Ammos.Count()));
				while (tmp17.Count > 0 && tmp17.Last() == 0)
					tmp17.RemoveAt(tmp17.Count - 1);
				s.Add((byte)tmp17.Count);
				s.AddRange(tmp17);
				
				foreach (var tmp18 in Ammos)
				{
					s.Add((byte)((tmp18.Key == null) ? 0 : 1));
					if (tmp18.Key != null)
					{
						s.Add((byte)((sbyte)tmp18.Key));
					}
					
					s.Add((byte)((tmp18.Value == null) ? 0 : 1));
					if (tmp18.Value != null)
					{
						s.AddRange(BitConverter.GetBytes((int)tmp18.Value));
					}
				}
			}
			
			return s.ToArray();
		}
		
		public override uint Deserialize(byte[] s, uint offset = 0)
		{
			// deserialize parents
			offset = base.Deserialize(s, offset);
			
			// deserialize Ammos
			byte tmp19;
			tmp19 = (byte)s[(int)offset];
			offset += sizeof(byte);
			if (tmp19 == 1)
			{
				byte tmp20;
				tmp20 = (byte)s[(int)offset];
				offset += sizeof(byte);
				byte[] tmp21 = new byte[sizeof(uint)];
				Array.Copy(s, offset, tmp21, 0, tmp20);
				offset += tmp20;
				uint tmp22;
				tmp22 = BitConverter.ToUInt32(tmp21, (int)0);
				
				Ammos = new Dictionary<CommandAmmoType?, int?>();
				for (uint tmp23 = 0; tmp23 < tmp22; tmp23++)
				{
					CommandAmmoType? tmp24;
					byte tmp26;
					tmp26 = (byte)s[(int)offset];
					offset += sizeof(byte);
					if (tmp26 == 1)
					{
						sbyte tmp27;
						tmp27 = (sbyte)s[(int)offset];
						offset += sizeof(sbyte);
						tmp24 = (CommandAmmoType)tmp27;
					}
					else
						tmp24 = null;
					
					int? tmp25;
					byte tmp28;
					tmp28 = (byte)s[(int)offset];
					offset += sizeof(byte);
					if (tmp28 == 1)
					{
						tmp25 = BitConverter.ToInt32(s, (int)offset);
						offset += sizeof(int);
					}
					else
						tmp25 = null;
					
					Ammos[tmp24] = tmp25;
				}
			}
			else
				Ammos = null;
			
			return offset;
		}
	}
	
	public partial class PutAmmo : BaseCommand
	{
		

		public PutAmmo()
		{
		}
		
		public new const string NameStatic = "PutAmmo";
		
		public override string Name() => "PutAmmo";
		
		public override byte[] Serialize()
		{
			List<byte> s = new List<byte>();
			
			// serialize parents
			s.AddRange(base.Serialize());
			
			return s.ToArray();
		}
		
		public override uint Deserialize(byte[] s, uint offset = 0)
		{
			// deserialize parents
			offset = base.Deserialize(s, offset);
			
			return offset;
		}
	}
} // namespace KS.Commands
