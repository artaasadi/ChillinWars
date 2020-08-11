using System;

namespace KS.Models
{
	public partial class Position
	{
		public override bool Equals(object obj)
		{
			if (obj is Position)
				return this.Index == ((Position)obj).Index;
			return base.Equals(obj);
		}

		public override int GetHashCode()
		{
			return Index.Value;
		}

		public override string ToString()
		{
			return $"<Index: {Index}>";
		}

		public static bool operator ==(Position p1, Position p2)
		{
			if (p1 == null)
				return p2 == null;
			return p1.Equals(p2);
		}

		public static bool operator !=(Position p1, Position p2)
		{
			return !(p1 == p2);
		}

		public static Position operator +(Position p1, Position p2)
		{
			return new Position() { Index = p1.Index + p2.Index };
		}

		public static Position operator -(Position p1, Position p2)
		{
			return new Position() { Index = p1.Index - p2.Index };
		}
	}
}
