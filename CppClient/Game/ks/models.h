#ifndef _KS_MODELS_H_
#define _KS_MODELS_H_

#include <string>
#include <vector>
#include <map>
#include <array>


namespace ks
{

#ifndef _KS_OBJECT_
#define _KS_OBJECT_

class KSObject
{
public:
	static inline const std::string nameStatic() { return ""; }
	virtual inline const std::string name() const = 0;
	virtual std::string serialize() const = 0;
	virtual unsigned int deserialize(const std::string &, unsigned int = 0) = 0;
};

#endif // _KS_OBJECT_


namespace models
{

enum class ECell
{
	Empty = 0,
	FrontlineDelivery = 1,
	Material = 2,
	BacklineDelivery = 3,
	Machine = 4,
};


enum class MachineStatus
{
	Idle = 0,
	Working = 1,
	AmmoReady = 2,
};


enum class MaterialType
{
	Powder = 0,
	Iron = 1,
	Carbon = 2,
	Gold = 3,
	Shell = 4,
};


enum class AmmoType
{
	RifleBullet = 0,
	TankShell = 1,
	HMGBullet = 2,
	MortarShell = 3,
	GoldenTankShell = 4,
};


enum class UnitType
{
	Soldier = 0,
	Tank = 1,
	HeavyMachineGunner = 2,
	Mortar = 3,
	GoldenTank = 4,
};


enum class AgentType
{
	Warehouse = 0,
	Factory = 1,
};


class Position : public KSObject
{

protected:

	int __index;

	bool __has_index;


public: // getters

	inline int index() const
	{
		return __index;
	}
	

public: // reference getters

	inline int &ref_index() const
	{
		return (int&) __index;
	}
	

public: // setters

	inline void index(const int &index)
	{
		__index = index;
		has_index(true);
	}
	

public: // has_attribute getters

	inline bool has_index() const
	{
		return __has_index;
	}
	

public: // has_attribute setters

	inline void has_index(const bool &has_index)
	{
		__has_index = has_index;
	}
	

public:

	Position()
	{
		has_index(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "Position";
	}
	
	virtual inline const std::string name() const
	{
		return "Position";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize index
		s += __has_index;
		if (__has_index)
		{
			int tmp1 = __index;
			auto tmp2 = reinterpret_cast<char*>(&tmp1);
			s += std::string(tmp2, sizeof(int));
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize index
		__has_index = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_index)
		{
			__index = *((int*) (&s[offset]));
			offset += sizeof(int);
		}
		
		return offset;
	}

public:

    bool operator <(const ks::models::Position &other) const
    {
        return index() < other.index();
    }

	bool operator ==(const Position &other) const
	{
		if (!has_index())
			return !other.has_index();
		return index() == other.index();
	}

	bool operator !=(const Position &other) const
	{
		return !((*this) == other);
	}

	Position operator +(const Position &other) const
	{
		Position p;
		p.index(index() + ((other.has_index()) ? other.index() : 0));
		return p;
	}

	void operator +=(const Position &other)
	{
		index(index() + ((other.has_index()) ? other.index() : 0));
	}

	Position operator -(const Position &other) const
	{
		Position p;
		p.index(index() - ((other.has_index()) ? other.index() : 0));
		return p;
	}

	void operator -=(const Position &other)
	{
		index(index() - ((other.has_index()) ? other.index() : 0));
	}
};


class Material : public KSObject
{

protected:

	MaterialType __type;
	Position __position;
	int __count;
	int __cCapacity;

	bool __has_type;
	bool __has_position;
	bool __has_count;
	bool __has_cCapacity;


public: // getters

	inline MaterialType type() const
	{
		return __type;
	}
	
	inline Position position() const
	{
		return __position;
	}
	
	inline int count() const
	{
		return __count;
	}
	
	inline int cCapacity() const
	{
		return __cCapacity;
	}
	

public: // reference getters

	inline MaterialType &ref_type() const
	{
		return (MaterialType&) __type;
	}
	
	inline Position &ref_position() const
	{
		return (Position&) __position;
	}
	
	inline int &ref_count() const
	{
		return (int&) __count;
	}
	
	inline int &ref_cCapacity() const
	{
		return (int&) __cCapacity;
	}
	

public: // setters

	inline void type(const MaterialType &type)
	{
		__type = type;
		has_type(true);
	}
	
	inline void position(const Position &position)
	{
		__position = position;
		has_position(true);
	}
	
	inline void count(const int &count)
	{
		__count = count;
		has_count(true);
	}
	
	inline void cCapacity(const int &cCapacity)
	{
		__cCapacity = cCapacity;
		has_cCapacity(true);
	}
	

public: // has_attribute getters

	inline bool has_type() const
	{
		return __has_type;
	}
	
	inline bool has_position() const
	{
		return __has_position;
	}
	
	inline bool has_count() const
	{
		return __has_count;
	}
	
	inline bool has_cCapacity() const
	{
		return __has_cCapacity;
	}
	

public: // has_attribute setters

	inline void has_type(const bool &has_type)
	{
		__has_type = has_type;
	}
	
	inline void has_position(const bool &has_position)
	{
		__has_position = has_position;
	}
	
	inline void has_count(const bool &has_count)
	{
		__has_count = has_count;
	}
	
	inline void has_cCapacity(const bool &has_cCapacity)
	{
		__has_cCapacity = has_cCapacity;
	}
	

public:

	Material()
	{
		has_type(false);
		has_position(false);
		has_count(false);
		has_cCapacity(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "Material";
	}
	
	virtual inline const std::string name() const
	{
		return "Material";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize type
		s += __has_type;
		if (__has_type)
		{
			char tmp4 = (char) __type;
			auto tmp5 = reinterpret_cast<char*>(&tmp4);
			s += std::string(tmp5, sizeof(char));
		}
		
		// serialize position
		s += __has_position;
		if (__has_position)
		{
			s += __position.serialize();
		}
		
		// serialize count
		s += __has_count;
		if (__has_count)
		{
			int tmp7 = __count;
			auto tmp8 = reinterpret_cast<char*>(&tmp7);
			s += std::string(tmp8, sizeof(int));
		}
		
		// serialize cCapacity
		s += __has_cCapacity;
		if (__has_cCapacity)
		{
			int tmp10 = __cCapacity;
			auto tmp11 = reinterpret_cast<char*>(&tmp10);
			s += std::string(tmp11, sizeof(int));
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize type
		__has_type = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_type)
		{
			char tmp12;
			tmp12 = *((char*) (&s[offset]));
			offset += sizeof(char);
			__type = (MaterialType) tmp12;
		}
		
		// deserialize position
		__has_position = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_position)
		{
			offset = __position.deserialize(s, offset);
		}
		
		// deserialize count
		__has_count = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_count)
		{
			__count = *((int*) (&s[offset]));
			offset += sizeof(int);
		}
		
		// deserialize cCapacity
		__has_cCapacity = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_cCapacity)
		{
			__cCapacity = *((int*) (&s[offset]));
			offset += sizeof(int);
		}
		
		return offset;
	}
};


class Machine : public KSObject
{

protected:

	Position __position;
	MachineStatus __status;
	AmmoType __currentAmmo;
	int __constructionRemTime;

	bool __has_position;
	bool __has_status;
	bool __has_currentAmmo;
	bool __has_constructionRemTime;


public: // getters

	inline Position position() const
	{
		return __position;
	}
	
	inline MachineStatus status() const
	{
		return __status;
	}
	
	inline AmmoType currentAmmo() const
	{
		return __currentAmmo;
	}
	
	inline int constructionRemTime() const
	{
		return __constructionRemTime;
	}
	

public: // reference getters

	inline Position &ref_position() const
	{
		return (Position&) __position;
	}
	
	inline MachineStatus &ref_status() const
	{
		return (MachineStatus&) __status;
	}
	
	inline AmmoType &ref_currentAmmo() const
	{
		return (AmmoType&) __currentAmmo;
	}
	
	inline int &ref_constructionRemTime() const
	{
		return (int&) __constructionRemTime;
	}
	

public: // setters

	inline void position(const Position &position)
	{
		__position = position;
		has_position(true);
	}
	
	inline void status(const MachineStatus &status)
	{
		__status = status;
		has_status(true);
	}
	
	inline void currentAmmo(const AmmoType &currentAmmo)
	{
		__currentAmmo = currentAmmo;
		has_currentAmmo(true);
	}
	
	inline void constructionRemTime(const int &constructionRemTime)
	{
		__constructionRemTime = constructionRemTime;
		has_constructionRemTime(true);
	}
	

public: // has_attribute getters

	inline bool has_position() const
	{
		return __has_position;
	}
	
	inline bool has_status() const
	{
		return __has_status;
	}
	
	inline bool has_currentAmmo() const
	{
		return __has_currentAmmo;
	}
	
	inline bool has_constructionRemTime() const
	{
		return __has_constructionRemTime;
	}
	

public: // has_attribute setters

	inline void has_position(const bool &has_position)
	{
		__has_position = has_position;
	}
	
	inline void has_status(const bool &has_status)
	{
		__has_status = has_status;
	}
	
	inline void has_currentAmmo(const bool &has_currentAmmo)
	{
		__has_currentAmmo = has_currentAmmo;
	}
	
	inline void has_constructionRemTime(const bool &has_constructionRemTime)
	{
		__has_constructionRemTime = has_constructionRemTime;
	}
	

public:

	Machine()
	{
		has_position(false);
		has_status(false);
		has_currentAmmo(false);
		has_constructionRemTime(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "Machine";
	}
	
	virtual inline const std::string name() const
	{
		return "Machine";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize position
		s += __has_position;
		if (__has_position)
		{
			s += __position.serialize();
		}
		
		// serialize status
		s += __has_status;
		if (__has_status)
		{
			char tmp14 = (char) __status;
			auto tmp15 = reinterpret_cast<char*>(&tmp14);
			s += std::string(tmp15, sizeof(char));
		}
		
		// serialize currentAmmo
		s += __has_currentAmmo;
		if (__has_currentAmmo)
		{
			char tmp17 = (char) __currentAmmo;
			auto tmp18 = reinterpret_cast<char*>(&tmp17);
			s += std::string(tmp18, sizeof(char));
		}
		
		// serialize constructionRemTime
		s += __has_constructionRemTime;
		if (__has_constructionRemTime)
		{
			int tmp20 = __constructionRemTime;
			auto tmp21 = reinterpret_cast<char*>(&tmp20);
			s += std::string(tmp21, sizeof(int));
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize position
		__has_position = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_position)
		{
			offset = __position.deserialize(s, offset);
		}
		
		// deserialize status
		__has_status = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_status)
		{
			char tmp22;
			tmp22 = *((char*) (&s[offset]));
			offset += sizeof(char);
			__status = (MachineStatus) tmp22;
		}
		
		// deserialize currentAmmo
		__has_currentAmmo = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_currentAmmo)
		{
			char tmp23;
			tmp23 = *((char*) (&s[offset]));
			offset += sizeof(char);
			__currentAmmo = (AmmoType) tmp23;
		}
		
		// deserialize constructionRemTime
		__has_constructionRemTime = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_constructionRemTime)
		{
			__constructionRemTime = *((int*) (&s[offset]));
			offset += sizeof(int);
		}
		
		return offset;
	}
};


class FrontlineDelivery : public KSObject
{

protected:

	std::map<AmmoType, int> __ammos;
	int __deliveryRemTime;
	int __cDeliveryDuration;

	bool __has_ammos;
	bool __has_deliveryRemTime;
	bool __has_cDeliveryDuration;


public: // getters

	inline std::map<AmmoType, int> ammos() const
	{
		return __ammos;
	}
	
	inline int deliveryRemTime() const
	{
		return __deliveryRemTime;
	}
	
	inline int cDeliveryDuration() const
	{
		return __cDeliveryDuration;
	}
	

public: // reference getters

	inline std::map<AmmoType, int> &ref_ammos() const
	{
		return (std::map<AmmoType, int>&) __ammos;
	}
	
	inline int &ref_deliveryRemTime() const
	{
		return (int&) __deliveryRemTime;
	}
	
	inline int &ref_cDeliveryDuration() const
	{
		return (int&) __cDeliveryDuration;
	}
	

public: // setters

	inline void ammos(const std::map<AmmoType, int> &ammos)
	{
		__ammos = ammos;
		has_ammos(true);
	}
	
	inline void deliveryRemTime(const int &deliveryRemTime)
	{
		__deliveryRemTime = deliveryRemTime;
		has_deliveryRemTime(true);
	}
	
	inline void cDeliveryDuration(const int &cDeliveryDuration)
	{
		__cDeliveryDuration = cDeliveryDuration;
		has_cDeliveryDuration(true);
	}
	

public: // has_attribute getters

	inline bool has_ammos() const
	{
		return __has_ammos;
	}
	
	inline bool has_deliveryRemTime() const
	{
		return __has_deliveryRemTime;
	}
	
	inline bool has_cDeliveryDuration() const
	{
		return __has_cDeliveryDuration;
	}
	

public: // has_attribute setters

	inline void has_ammos(const bool &has_ammos)
	{
		__has_ammos = has_ammos;
	}
	
	inline void has_deliveryRemTime(const bool &has_deliveryRemTime)
	{
		__has_deliveryRemTime = has_deliveryRemTime;
	}
	
	inline void has_cDeliveryDuration(const bool &has_cDeliveryDuration)
	{
		__has_cDeliveryDuration = has_cDeliveryDuration;
	}
	

public:

	FrontlineDelivery()
	{
		has_ammos(false);
		has_deliveryRemTime(false);
		has_cDeliveryDuration(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "FrontlineDelivery";
	}
	
	virtual inline const std::string name() const
	{
		return "FrontlineDelivery";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize ammos
		s += __has_ammos;
		if (__has_ammos)
		{
			std::string tmp24 = "";
			unsigned int tmp26 = __ammos.size();
			auto tmp27 = reinterpret_cast<char*>(&tmp26);
			tmp24 += std::string(tmp27, sizeof(unsigned int));
			while (tmp24.size() && tmp24.back() == 0)
				tmp24.pop_back();
			unsigned char tmp29 = tmp24.size();
			auto tmp30 = reinterpret_cast<char*>(&tmp29);
			s += std::string(tmp30, sizeof(unsigned char));
			s += tmp24;
			
			for (auto &tmp31 : __ammos)
			{
				s += '\x01';
				char tmp33 = (char) tmp31.first;
				auto tmp34 = reinterpret_cast<char*>(&tmp33);
				s += std::string(tmp34, sizeof(char));
				
				s += '\x01';
				int tmp36 = tmp31.second;
				auto tmp37 = reinterpret_cast<char*>(&tmp36);
				s += std::string(tmp37, sizeof(int));
			}
		}
		
		// serialize deliveryRemTime
		s += __has_deliveryRemTime;
		if (__has_deliveryRemTime)
		{
			int tmp39 = __deliveryRemTime;
			auto tmp40 = reinterpret_cast<char*>(&tmp39);
			s += std::string(tmp40, sizeof(int));
		}
		
		// serialize cDeliveryDuration
		s += __has_cDeliveryDuration;
		if (__has_cDeliveryDuration)
		{
			int tmp42 = __cDeliveryDuration;
			auto tmp43 = reinterpret_cast<char*>(&tmp42);
			s += std::string(tmp43, sizeof(int));
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize ammos
		__has_ammos = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_ammos)
		{
			unsigned char tmp44;
			tmp44 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp45 = std::string(&s[offset], tmp44);
			offset += tmp44;
			while (tmp45.size() < sizeof(unsigned int))
				tmp45 += '\x00';
			unsigned int tmp46;
			tmp46 = *((unsigned int*) (&tmp45[0]));
			
			__ammos.clear();
			for (unsigned int tmp47 = 0; tmp47 < tmp46; tmp47++)
			{
				AmmoType tmp48;
				offset++;
				char tmp50;
				tmp50 = *((char*) (&s[offset]));
				offset += sizeof(char);
				tmp48 = (AmmoType) tmp50;
				
				int tmp49;
				offset++;
				tmp49 = *((int*) (&s[offset]));
				offset += sizeof(int);
				
				__ammos[tmp48] = tmp49;
			}
		}
		
		// deserialize deliveryRemTime
		__has_deliveryRemTime = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_deliveryRemTime)
		{
			__deliveryRemTime = *((int*) (&s[offset]));
			offset += sizeof(int);
		}
		
		// deserialize cDeliveryDuration
		__has_cDeliveryDuration = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_cDeliveryDuration)
		{
			__cDeliveryDuration = *((int*) (&s[offset]));
			offset += sizeof(int);
		}
		
		return offset;
	}
};


class Warehouse : public KSObject
{

protected:

	std::map<Position, Material> __materials;
	int __materialsReloadRemTime;
	int __cMaterialsReloadDuration;

	bool __has_materials;
	bool __has_materialsReloadRemTime;
	bool __has_cMaterialsReloadDuration;


public: // getters

	inline std::map<Position, Material> materials() const
	{
		return __materials;
	}
	
	inline int materialsReloadRemTime() const
	{
		return __materialsReloadRemTime;
	}
	
	inline int cMaterialsReloadDuration() const
	{
		return __cMaterialsReloadDuration;
	}
	

public: // reference getters

	inline std::map<Position, Material> &ref_materials() const
	{
		return (std::map<Position, Material>&) __materials;
	}
	
	inline int &ref_materialsReloadRemTime() const
	{
		return (int&) __materialsReloadRemTime;
	}
	
	inline int &ref_cMaterialsReloadDuration() const
	{
		return (int&) __cMaterialsReloadDuration;
	}
	

public: // setters

	inline void materials(const std::map<Position, Material> &materials)
	{
		__materials = materials;
		has_materials(true);
	}
	
	inline void materialsReloadRemTime(const int &materialsReloadRemTime)
	{
		__materialsReloadRemTime = materialsReloadRemTime;
		has_materialsReloadRemTime(true);
	}
	
	inline void cMaterialsReloadDuration(const int &cMaterialsReloadDuration)
	{
		__cMaterialsReloadDuration = cMaterialsReloadDuration;
		has_cMaterialsReloadDuration(true);
	}
	

public: // has_attribute getters

	inline bool has_materials() const
	{
		return __has_materials;
	}
	
	inline bool has_materialsReloadRemTime() const
	{
		return __has_materialsReloadRemTime;
	}
	
	inline bool has_cMaterialsReloadDuration() const
	{
		return __has_cMaterialsReloadDuration;
	}
	

public: // has_attribute setters

	inline void has_materials(const bool &has_materials)
	{
		__has_materials = has_materials;
	}
	
	inline void has_materialsReloadRemTime(const bool &has_materialsReloadRemTime)
	{
		__has_materialsReloadRemTime = has_materialsReloadRemTime;
	}
	
	inline void has_cMaterialsReloadDuration(const bool &has_cMaterialsReloadDuration)
	{
		__has_cMaterialsReloadDuration = has_cMaterialsReloadDuration;
	}
	

public:

	Warehouse()
	{
		has_materials(false);
		has_materialsReloadRemTime(false);
		has_cMaterialsReloadDuration(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "Warehouse";
	}
	
	virtual inline const std::string name() const
	{
		return "Warehouse";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize materials
		s += __has_materials;
		if (__has_materials)
		{
			std::string tmp51 = "";
			unsigned int tmp53 = __materials.size();
			auto tmp54 = reinterpret_cast<char*>(&tmp53);
			tmp51 += std::string(tmp54, sizeof(unsigned int));
			while (tmp51.size() && tmp51.back() == 0)
				tmp51.pop_back();
			unsigned char tmp56 = tmp51.size();
			auto tmp57 = reinterpret_cast<char*>(&tmp56);
			s += std::string(tmp57, sizeof(unsigned char));
			s += tmp51;
			
			for (auto &tmp58 : __materials)
			{
				s += '\x01';
				s += tmp58.first.serialize();
				
				s += '\x01';
				s += tmp58.second.serialize();
			}
		}
		
		// serialize materialsReloadRemTime
		s += __has_materialsReloadRemTime;
		if (__has_materialsReloadRemTime)
		{
			int tmp60 = __materialsReloadRemTime;
			auto tmp61 = reinterpret_cast<char*>(&tmp60);
			s += std::string(tmp61, sizeof(int));
		}
		
		// serialize cMaterialsReloadDuration
		s += __has_cMaterialsReloadDuration;
		if (__has_cMaterialsReloadDuration)
		{
			int tmp63 = __cMaterialsReloadDuration;
			auto tmp64 = reinterpret_cast<char*>(&tmp63);
			s += std::string(tmp64, sizeof(int));
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize materials
		__has_materials = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_materials)
		{
			unsigned char tmp65;
			tmp65 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp66 = std::string(&s[offset], tmp65);
			offset += tmp65;
			while (tmp66.size() < sizeof(unsigned int))
				tmp66 += '\x00';
			unsigned int tmp67;
			tmp67 = *((unsigned int*) (&tmp66[0]));
			
			__materials.clear();
			for (unsigned int tmp68 = 0; tmp68 < tmp67; tmp68++)
			{
				Position tmp69;
				offset++;
				offset = tmp69.deserialize(s, offset);
				
				Material tmp70;
				offset++;
				offset = tmp70.deserialize(s, offset);
				
				__materials[tmp69] = tmp70;
			}
		}
		
		// deserialize materialsReloadRemTime
		__has_materialsReloadRemTime = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_materialsReloadRemTime)
		{
			__materialsReloadRemTime = *((int*) (&s[offset]));
			offset += sizeof(int);
		}
		
		// deserialize cMaterialsReloadDuration
		__has_cMaterialsReloadDuration = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_cMaterialsReloadDuration)
		{
			__cMaterialsReloadDuration = *((int*) (&s[offset]));
			offset += sizeof(int);
		}
		
		return offset;
	}
};


class BacklineDelivery : public KSObject
{

protected:

	std::map<MaterialType, int> __materials;
	std::map<AmmoType, int> __ammos;

	bool __has_materials;
	bool __has_ammos;


public: // getters

	inline std::map<MaterialType, int> materials() const
	{
		return __materials;
	}
	
	inline std::map<AmmoType, int> ammos() const
	{
		return __ammos;
	}
	

public: // reference getters

	inline std::map<MaterialType, int> &ref_materials() const
	{
		return (std::map<MaterialType, int>&) __materials;
	}
	
	inline std::map<AmmoType, int> &ref_ammos() const
	{
		return (std::map<AmmoType, int>&) __ammos;
	}
	

public: // setters

	inline void materials(const std::map<MaterialType, int> &materials)
	{
		__materials = materials;
		has_materials(true);
	}
	
	inline void ammos(const std::map<AmmoType, int> &ammos)
	{
		__ammos = ammos;
		has_ammos(true);
	}
	

public: // has_attribute getters

	inline bool has_materials() const
	{
		return __has_materials;
	}
	
	inline bool has_ammos() const
	{
		return __has_ammos;
	}
	

public: // has_attribute setters

	inline void has_materials(const bool &has_materials)
	{
		__has_materials = has_materials;
	}
	
	inline void has_ammos(const bool &has_ammos)
	{
		__has_ammos = has_ammos;
	}
	

public:

	BacklineDelivery()
	{
		has_materials(false);
		has_ammos(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "BacklineDelivery";
	}
	
	virtual inline const std::string name() const
	{
		return "BacklineDelivery";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize materials
		s += __has_materials;
		if (__has_materials)
		{
			std::string tmp71 = "";
			unsigned int tmp73 = __materials.size();
			auto tmp74 = reinterpret_cast<char*>(&tmp73);
			tmp71 += std::string(tmp74, sizeof(unsigned int));
			while (tmp71.size() && tmp71.back() == 0)
				tmp71.pop_back();
			unsigned char tmp76 = tmp71.size();
			auto tmp77 = reinterpret_cast<char*>(&tmp76);
			s += std::string(tmp77, sizeof(unsigned char));
			s += tmp71;
			
			for (auto &tmp78 : __materials)
			{
				s += '\x01';
				char tmp80 = (char) tmp78.first;
				auto tmp81 = reinterpret_cast<char*>(&tmp80);
				s += std::string(tmp81, sizeof(char));
				
				s += '\x01';
				int tmp83 = tmp78.second;
				auto tmp84 = reinterpret_cast<char*>(&tmp83);
				s += std::string(tmp84, sizeof(int));
			}
		}
		
		// serialize ammos
		s += __has_ammos;
		if (__has_ammos)
		{
			std::string tmp85 = "";
			unsigned int tmp87 = __ammos.size();
			auto tmp88 = reinterpret_cast<char*>(&tmp87);
			tmp85 += std::string(tmp88, sizeof(unsigned int));
			while (tmp85.size() && tmp85.back() == 0)
				tmp85.pop_back();
			unsigned char tmp90 = tmp85.size();
			auto tmp91 = reinterpret_cast<char*>(&tmp90);
			s += std::string(tmp91, sizeof(unsigned char));
			s += tmp85;
			
			for (auto &tmp92 : __ammos)
			{
				s += '\x01';
				char tmp94 = (char) tmp92.first;
				auto tmp95 = reinterpret_cast<char*>(&tmp94);
				s += std::string(tmp95, sizeof(char));
				
				s += '\x01';
				int tmp97 = tmp92.second;
				auto tmp98 = reinterpret_cast<char*>(&tmp97);
				s += std::string(tmp98, sizeof(int));
			}
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize materials
		__has_materials = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_materials)
		{
			unsigned char tmp99;
			tmp99 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp100 = std::string(&s[offset], tmp99);
			offset += tmp99;
			while (tmp100.size() < sizeof(unsigned int))
				tmp100 += '\x00';
			unsigned int tmp101;
			tmp101 = *((unsigned int*) (&tmp100[0]));
			
			__materials.clear();
			for (unsigned int tmp102 = 0; tmp102 < tmp101; tmp102++)
			{
				MaterialType tmp103;
				offset++;
				char tmp105;
				tmp105 = *((char*) (&s[offset]));
				offset += sizeof(char);
				tmp103 = (MaterialType) tmp105;
				
				int tmp104;
				offset++;
				tmp104 = *((int*) (&s[offset]));
				offset += sizeof(int);
				
				__materials[tmp103] = tmp104;
			}
		}
		
		// deserialize ammos
		__has_ammos = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_ammos)
		{
			unsigned char tmp106;
			tmp106 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp107 = std::string(&s[offset], tmp106);
			offset += tmp106;
			while (tmp107.size() < sizeof(unsigned int))
				tmp107 += '\x00';
			unsigned int tmp108;
			tmp108 = *((unsigned int*) (&tmp107[0]));
			
			__ammos.clear();
			for (unsigned int tmp109 = 0; tmp109 < tmp108; tmp109++)
			{
				AmmoType tmp110;
				offset++;
				char tmp112;
				tmp112 = *((char*) (&s[offset]));
				offset += sizeof(char);
				tmp110 = (AmmoType) tmp112;
				
				int tmp111;
				offset++;
				tmp111 = *((int*) (&s[offset]));
				offset += sizeof(int);
				
				__ammos[tmp110] = tmp111;
			}
		}
		
		return offset;
	}
};


class Factory : public KSObject
{

protected:

	std::map<Position, Machine> __machines;
	std::map<AmmoType, std::map<MaterialType, int>> __cMixtureFormulas;
	std::map<AmmoType, int> __cConstructionDurations;
	std::map<AmmoType, int> __cAmmoBoxSizes;

	bool __has_machines;
	bool __has_cMixtureFormulas;
	bool __has_cConstructionDurations;
	bool __has_cAmmoBoxSizes;


public: // getters

	inline std::map<Position, Machine> machines() const
	{
		return __machines;
	}
	
	inline std::map<AmmoType, std::map<MaterialType, int>> cMixtureFormulas() const
	{
		return __cMixtureFormulas;
	}
	
	inline std::map<AmmoType, int> cConstructionDurations() const
	{
		return __cConstructionDurations;
	}
	
	inline std::map<AmmoType, int> cAmmoBoxSizes() const
	{
		return __cAmmoBoxSizes;
	}
	

public: // reference getters

	inline std::map<Position, Machine> &ref_machines() const
	{
		return (std::map<Position, Machine>&) __machines;
	}
	
	inline std::map<AmmoType, std::map<MaterialType, int>> &ref_cMixtureFormulas() const
	{
		return (std::map<AmmoType, std::map<MaterialType, int>>&) __cMixtureFormulas;
	}
	
	inline std::map<AmmoType, int> &ref_cConstructionDurations() const
	{
		return (std::map<AmmoType, int>&) __cConstructionDurations;
	}
	
	inline std::map<AmmoType, int> &ref_cAmmoBoxSizes() const
	{
		return (std::map<AmmoType, int>&) __cAmmoBoxSizes;
	}
	

public: // setters

	inline void machines(const std::map<Position, Machine> &machines)
	{
		__machines = machines;
		has_machines(true);
	}
	
	inline void cMixtureFormulas(const std::map<AmmoType, std::map<MaterialType, int>> &cMixtureFormulas)
	{
		__cMixtureFormulas = cMixtureFormulas;
		has_cMixtureFormulas(true);
	}
	
	inline void cConstructionDurations(const std::map<AmmoType, int> &cConstructionDurations)
	{
		__cConstructionDurations = cConstructionDurations;
		has_cConstructionDurations(true);
	}
	
	inline void cAmmoBoxSizes(const std::map<AmmoType, int> &cAmmoBoxSizes)
	{
		__cAmmoBoxSizes = cAmmoBoxSizes;
		has_cAmmoBoxSizes(true);
	}
	

public: // has_attribute getters

	inline bool has_machines() const
	{
		return __has_machines;
	}
	
	inline bool has_cMixtureFormulas() const
	{
		return __has_cMixtureFormulas;
	}
	
	inline bool has_cConstructionDurations() const
	{
		return __has_cConstructionDurations;
	}
	
	inline bool has_cAmmoBoxSizes() const
	{
		return __has_cAmmoBoxSizes;
	}
	

public: // has_attribute setters

	inline void has_machines(const bool &has_machines)
	{
		__has_machines = has_machines;
	}
	
	inline void has_cMixtureFormulas(const bool &has_cMixtureFormulas)
	{
		__has_cMixtureFormulas = has_cMixtureFormulas;
	}
	
	inline void has_cConstructionDurations(const bool &has_cConstructionDurations)
	{
		__has_cConstructionDurations = has_cConstructionDurations;
	}
	
	inline void has_cAmmoBoxSizes(const bool &has_cAmmoBoxSizes)
	{
		__has_cAmmoBoxSizes = has_cAmmoBoxSizes;
	}
	

public:

	Factory()
	{
		has_machines(false);
		has_cMixtureFormulas(false);
		has_cConstructionDurations(false);
		has_cAmmoBoxSizes(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "Factory";
	}
	
	virtual inline const std::string name() const
	{
		return "Factory";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize machines
		s += __has_machines;
		if (__has_machines)
		{
			std::string tmp113 = "";
			unsigned int tmp115 = __machines.size();
			auto tmp116 = reinterpret_cast<char*>(&tmp115);
			tmp113 += std::string(tmp116, sizeof(unsigned int));
			while (tmp113.size() && tmp113.back() == 0)
				tmp113.pop_back();
			unsigned char tmp118 = tmp113.size();
			auto tmp119 = reinterpret_cast<char*>(&tmp118);
			s += std::string(tmp119, sizeof(unsigned char));
			s += tmp113;
			
			for (auto &tmp120 : __machines)
			{
				s += '\x01';
				s += tmp120.first.serialize();
				
				s += '\x01';
				s += tmp120.second.serialize();
			}
		}
		
		// serialize cMixtureFormulas
		s += __has_cMixtureFormulas;
		if (__has_cMixtureFormulas)
		{
			std::string tmp121 = "";
			unsigned int tmp123 = __cMixtureFormulas.size();
			auto tmp124 = reinterpret_cast<char*>(&tmp123);
			tmp121 += std::string(tmp124, sizeof(unsigned int));
			while (tmp121.size() && tmp121.back() == 0)
				tmp121.pop_back();
			unsigned char tmp126 = tmp121.size();
			auto tmp127 = reinterpret_cast<char*>(&tmp126);
			s += std::string(tmp127, sizeof(unsigned char));
			s += tmp121;
			
			for (auto &tmp128 : __cMixtureFormulas)
			{
				s += '\x01';
				char tmp130 = (char) tmp128.first;
				auto tmp131 = reinterpret_cast<char*>(&tmp130);
				s += std::string(tmp131, sizeof(char));
				
				s += '\x01';
				std::string tmp132 = "";
				unsigned int tmp134 = tmp128.second.size();
				auto tmp135 = reinterpret_cast<char*>(&tmp134);
				tmp132 += std::string(tmp135, sizeof(unsigned int));
				while (tmp132.size() && tmp132.back() == 0)
					tmp132.pop_back();
				unsigned char tmp137 = tmp132.size();
				auto tmp138 = reinterpret_cast<char*>(&tmp137);
				s += std::string(tmp138, sizeof(unsigned char));
				s += tmp132;
				
				for (auto &tmp139 : tmp128.second)
				{
					s += '\x01';
					char tmp141 = (char) tmp139.first;
					auto tmp142 = reinterpret_cast<char*>(&tmp141);
					s += std::string(tmp142, sizeof(char));
					
					s += '\x01';
					int tmp144 = tmp139.second;
					auto tmp145 = reinterpret_cast<char*>(&tmp144);
					s += std::string(tmp145, sizeof(int));
				}
			}
		}
		
		// serialize cConstructionDurations
		s += __has_cConstructionDurations;
		if (__has_cConstructionDurations)
		{
			std::string tmp146 = "";
			unsigned int tmp148 = __cConstructionDurations.size();
			auto tmp149 = reinterpret_cast<char*>(&tmp148);
			tmp146 += std::string(tmp149, sizeof(unsigned int));
			while (tmp146.size() && tmp146.back() == 0)
				tmp146.pop_back();
			unsigned char tmp151 = tmp146.size();
			auto tmp152 = reinterpret_cast<char*>(&tmp151);
			s += std::string(tmp152, sizeof(unsigned char));
			s += tmp146;
			
			for (auto &tmp153 : __cConstructionDurations)
			{
				s += '\x01';
				char tmp155 = (char) tmp153.first;
				auto tmp156 = reinterpret_cast<char*>(&tmp155);
				s += std::string(tmp156, sizeof(char));
				
				s += '\x01';
				int tmp158 = tmp153.second;
				auto tmp159 = reinterpret_cast<char*>(&tmp158);
				s += std::string(tmp159, sizeof(int));
			}
		}
		
		// serialize cAmmoBoxSizes
		s += __has_cAmmoBoxSizes;
		if (__has_cAmmoBoxSizes)
		{
			std::string tmp160 = "";
			unsigned int tmp162 = __cAmmoBoxSizes.size();
			auto tmp163 = reinterpret_cast<char*>(&tmp162);
			tmp160 += std::string(tmp163, sizeof(unsigned int));
			while (tmp160.size() && tmp160.back() == 0)
				tmp160.pop_back();
			unsigned char tmp165 = tmp160.size();
			auto tmp166 = reinterpret_cast<char*>(&tmp165);
			s += std::string(tmp166, sizeof(unsigned char));
			s += tmp160;
			
			for (auto &tmp167 : __cAmmoBoxSizes)
			{
				s += '\x01';
				char tmp169 = (char) tmp167.first;
				auto tmp170 = reinterpret_cast<char*>(&tmp169);
				s += std::string(tmp170, sizeof(char));
				
				s += '\x01';
				int tmp172 = tmp167.second;
				auto tmp173 = reinterpret_cast<char*>(&tmp172);
				s += std::string(tmp173, sizeof(int));
			}
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize machines
		__has_machines = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_machines)
		{
			unsigned char tmp174;
			tmp174 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp175 = std::string(&s[offset], tmp174);
			offset += tmp174;
			while (tmp175.size() < sizeof(unsigned int))
				tmp175 += '\x00';
			unsigned int tmp176;
			tmp176 = *((unsigned int*) (&tmp175[0]));
			
			__machines.clear();
			for (unsigned int tmp177 = 0; tmp177 < tmp176; tmp177++)
			{
				Position tmp178;
				offset++;
				offset = tmp178.deserialize(s, offset);
				
				Machine tmp179;
				offset++;
				offset = tmp179.deserialize(s, offset);
				
				__machines[tmp178] = tmp179;
			}
		}
		
		// deserialize cMixtureFormulas
		__has_cMixtureFormulas = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_cMixtureFormulas)
		{
			unsigned char tmp180;
			tmp180 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp181 = std::string(&s[offset], tmp180);
			offset += tmp180;
			while (tmp181.size() < sizeof(unsigned int))
				tmp181 += '\x00';
			unsigned int tmp182;
			tmp182 = *((unsigned int*) (&tmp181[0]));
			
			__cMixtureFormulas.clear();
			for (unsigned int tmp183 = 0; tmp183 < tmp182; tmp183++)
			{
				AmmoType tmp184;
				offset++;
				char tmp186;
				tmp186 = *((char*) (&s[offset]));
				offset += sizeof(char);
				tmp184 = (AmmoType) tmp186;
				
				std::map<MaterialType, int> tmp185;
				offset++;
				unsigned char tmp187;
				tmp187 = *((unsigned char*) (&s[offset]));
				offset += sizeof(unsigned char);
				std::string tmp188 = std::string(&s[offset], tmp187);
				offset += tmp187;
				while (tmp188.size() < sizeof(unsigned int))
					tmp188 += '\x00';
				unsigned int tmp189;
				tmp189 = *((unsigned int*) (&tmp188[0]));
				
				tmp185.clear();
				for (unsigned int tmp190 = 0; tmp190 < tmp189; tmp190++)
				{
					MaterialType tmp191;
					offset++;
					char tmp193;
					tmp193 = *((char*) (&s[offset]));
					offset += sizeof(char);
					tmp191 = (MaterialType) tmp193;
					
					int tmp192;
					offset++;
					tmp192 = *((int*) (&s[offset]));
					offset += sizeof(int);
					
					tmp185[tmp191] = tmp192;
				}
				
				__cMixtureFormulas[tmp184] = tmp185;
			}
		}
		
		// deserialize cConstructionDurations
		__has_cConstructionDurations = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_cConstructionDurations)
		{
			unsigned char tmp194;
			tmp194 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp195 = std::string(&s[offset], tmp194);
			offset += tmp194;
			while (tmp195.size() < sizeof(unsigned int))
				tmp195 += '\x00';
			unsigned int tmp196;
			tmp196 = *((unsigned int*) (&tmp195[0]));
			
			__cConstructionDurations.clear();
			for (unsigned int tmp197 = 0; tmp197 < tmp196; tmp197++)
			{
				AmmoType tmp198;
				offset++;
				char tmp200;
				tmp200 = *((char*) (&s[offset]));
				offset += sizeof(char);
				tmp198 = (AmmoType) tmp200;
				
				int tmp199;
				offset++;
				tmp199 = *((int*) (&s[offset]));
				offset += sizeof(int);
				
				__cConstructionDurations[tmp198] = tmp199;
			}
		}
		
		// deserialize cAmmoBoxSizes
		__has_cAmmoBoxSizes = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_cAmmoBoxSizes)
		{
			unsigned char tmp201;
			tmp201 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp202 = std::string(&s[offset], tmp201);
			offset += tmp201;
			while (tmp202.size() < sizeof(unsigned int))
				tmp202 += '\x00';
			unsigned int tmp203;
			tmp203 = *((unsigned int*) (&tmp202[0]));
			
			__cAmmoBoxSizes.clear();
			for (unsigned int tmp204 = 0; tmp204 < tmp203; tmp204++)
			{
				AmmoType tmp205;
				offset++;
				char tmp207;
				tmp207 = *((char*) (&s[offset]));
				offset += sizeof(char);
				tmp205 = (AmmoType) tmp207;
				
				int tmp206;
				offset++;
				tmp206 = *((int*) (&s[offset]));
				offset += sizeof(int);
				
				__cAmmoBoxSizes[tmp205] = tmp206;
			}
		}
		
		return offset;
	}
};


class Agent : public KSObject
{

protected:

	AgentType __type;
	Position __position;
	std::map<MaterialType, int> __materialsBag;
	int __cMaterialsBagCapacity;
	std::map<AmmoType, int> __ammosBag;
	int __cAmmosBagCapacity;

	bool __has_type;
	bool __has_position;
	bool __has_materialsBag;
	bool __has_cMaterialsBagCapacity;
	bool __has_ammosBag;
	bool __has_cAmmosBagCapacity;


public: // getters

	inline AgentType type() const
	{
		return __type;
	}
	
	inline Position position() const
	{
		return __position;
	}
	
	inline std::map<MaterialType, int> materialsBag() const
	{
		return __materialsBag;
	}
	
	inline int cMaterialsBagCapacity() const
	{
		return __cMaterialsBagCapacity;
	}
	
	inline std::map<AmmoType, int> ammosBag() const
	{
		return __ammosBag;
	}
	
	inline int cAmmosBagCapacity() const
	{
		return __cAmmosBagCapacity;
	}
	

public: // reference getters

	inline AgentType &ref_type() const
	{
		return (AgentType&) __type;
	}
	
	inline Position &ref_position() const
	{
		return (Position&) __position;
	}
	
	inline std::map<MaterialType, int> &ref_materialsBag() const
	{
		return (std::map<MaterialType, int>&) __materialsBag;
	}
	
	inline int &ref_cMaterialsBagCapacity() const
	{
		return (int&) __cMaterialsBagCapacity;
	}
	
	inline std::map<AmmoType, int> &ref_ammosBag() const
	{
		return (std::map<AmmoType, int>&) __ammosBag;
	}
	
	inline int &ref_cAmmosBagCapacity() const
	{
		return (int&) __cAmmosBagCapacity;
	}
	

public: // setters

	inline void type(const AgentType &type)
	{
		__type = type;
		has_type(true);
	}
	
	inline void position(const Position &position)
	{
		__position = position;
		has_position(true);
	}
	
	inline void materialsBag(const std::map<MaterialType, int> &materialsBag)
	{
		__materialsBag = materialsBag;
		has_materialsBag(true);
	}
	
	inline void cMaterialsBagCapacity(const int &cMaterialsBagCapacity)
	{
		__cMaterialsBagCapacity = cMaterialsBagCapacity;
		has_cMaterialsBagCapacity(true);
	}
	
	inline void ammosBag(const std::map<AmmoType, int> &ammosBag)
	{
		__ammosBag = ammosBag;
		has_ammosBag(true);
	}
	
	inline void cAmmosBagCapacity(const int &cAmmosBagCapacity)
	{
		__cAmmosBagCapacity = cAmmosBagCapacity;
		has_cAmmosBagCapacity(true);
	}
	

public: // has_attribute getters

	inline bool has_type() const
	{
		return __has_type;
	}
	
	inline bool has_position() const
	{
		return __has_position;
	}
	
	inline bool has_materialsBag() const
	{
		return __has_materialsBag;
	}
	
	inline bool has_cMaterialsBagCapacity() const
	{
		return __has_cMaterialsBagCapacity;
	}
	
	inline bool has_ammosBag() const
	{
		return __has_ammosBag;
	}
	
	inline bool has_cAmmosBagCapacity() const
	{
		return __has_cAmmosBagCapacity;
	}
	

public: // has_attribute setters

	inline void has_type(const bool &has_type)
	{
		__has_type = has_type;
	}
	
	inline void has_position(const bool &has_position)
	{
		__has_position = has_position;
	}
	
	inline void has_materialsBag(const bool &has_materialsBag)
	{
		__has_materialsBag = has_materialsBag;
	}
	
	inline void has_cMaterialsBagCapacity(const bool &has_cMaterialsBagCapacity)
	{
		__has_cMaterialsBagCapacity = has_cMaterialsBagCapacity;
	}
	
	inline void has_ammosBag(const bool &has_ammosBag)
	{
		__has_ammosBag = has_ammosBag;
	}
	
	inline void has_cAmmosBagCapacity(const bool &has_cAmmosBagCapacity)
	{
		__has_cAmmosBagCapacity = has_cAmmosBagCapacity;
	}
	

public:

	Agent()
	{
		has_type(false);
		has_position(false);
		has_materialsBag(false);
		has_cMaterialsBagCapacity(false);
		has_ammosBag(false);
		has_cAmmosBagCapacity(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "Agent";
	}
	
	virtual inline const std::string name() const
	{
		return "Agent";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize type
		s += __has_type;
		if (__has_type)
		{
			char tmp209 = (char) __type;
			auto tmp210 = reinterpret_cast<char*>(&tmp209);
			s += std::string(tmp210, sizeof(char));
		}
		
		// serialize position
		s += __has_position;
		if (__has_position)
		{
			s += __position.serialize();
		}
		
		// serialize materialsBag
		s += __has_materialsBag;
		if (__has_materialsBag)
		{
			std::string tmp211 = "";
			unsigned int tmp213 = __materialsBag.size();
			auto tmp214 = reinterpret_cast<char*>(&tmp213);
			tmp211 += std::string(tmp214, sizeof(unsigned int));
			while (tmp211.size() && tmp211.back() == 0)
				tmp211.pop_back();
			unsigned char tmp216 = tmp211.size();
			auto tmp217 = reinterpret_cast<char*>(&tmp216);
			s += std::string(tmp217, sizeof(unsigned char));
			s += tmp211;
			
			for (auto &tmp218 : __materialsBag)
			{
				s += '\x01';
				char tmp220 = (char) tmp218.first;
				auto tmp221 = reinterpret_cast<char*>(&tmp220);
				s += std::string(tmp221, sizeof(char));
				
				s += '\x01';
				int tmp223 = tmp218.second;
				auto tmp224 = reinterpret_cast<char*>(&tmp223);
				s += std::string(tmp224, sizeof(int));
			}
		}
		
		// serialize cMaterialsBagCapacity
		s += __has_cMaterialsBagCapacity;
		if (__has_cMaterialsBagCapacity)
		{
			int tmp226 = __cMaterialsBagCapacity;
			auto tmp227 = reinterpret_cast<char*>(&tmp226);
			s += std::string(tmp227, sizeof(int));
		}
		
		// serialize ammosBag
		s += __has_ammosBag;
		if (__has_ammosBag)
		{
			std::string tmp228 = "";
			unsigned int tmp230 = __ammosBag.size();
			auto tmp231 = reinterpret_cast<char*>(&tmp230);
			tmp228 += std::string(tmp231, sizeof(unsigned int));
			while (tmp228.size() && tmp228.back() == 0)
				tmp228.pop_back();
			unsigned char tmp233 = tmp228.size();
			auto tmp234 = reinterpret_cast<char*>(&tmp233);
			s += std::string(tmp234, sizeof(unsigned char));
			s += tmp228;
			
			for (auto &tmp235 : __ammosBag)
			{
				s += '\x01';
				char tmp237 = (char) tmp235.first;
				auto tmp238 = reinterpret_cast<char*>(&tmp237);
				s += std::string(tmp238, sizeof(char));
				
				s += '\x01';
				int tmp240 = tmp235.second;
				auto tmp241 = reinterpret_cast<char*>(&tmp240);
				s += std::string(tmp241, sizeof(int));
			}
		}
		
		// serialize cAmmosBagCapacity
		s += __has_cAmmosBagCapacity;
		if (__has_cAmmosBagCapacity)
		{
			int tmp243 = __cAmmosBagCapacity;
			auto tmp244 = reinterpret_cast<char*>(&tmp243);
			s += std::string(tmp244, sizeof(int));
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize type
		__has_type = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_type)
		{
			char tmp245;
			tmp245 = *((char*) (&s[offset]));
			offset += sizeof(char);
			__type = (AgentType) tmp245;
		}
		
		// deserialize position
		__has_position = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_position)
		{
			offset = __position.deserialize(s, offset);
		}
		
		// deserialize materialsBag
		__has_materialsBag = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_materialsBag)
		{
			unsigned char tmp246;
			tmp246 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp247 = std::string(&s[offset], tmp246);
			offset += tmp246;
			while (tmp247.size() < sizeof(unsigned int))
				tmp247 += '\x00';
			unsigned int tmp248;
			tmp248 = *((unsigned int*) (&tmp247[0]));
			
			__materialsBag.clear();
			for (unsigned int tmp249 = 0; tmp249 < tmp248; tmp249++)
			{
				MaterialType tmp250;
				offset++;
				char tmp252;
				tmp252 = *((char*) (&s[offset]));
				offset += sizeof(char);
				tmp250 = (MaterialType) tmp252;
				
				int tmp251;
				offset++;
				tmp251 = *((int*) (&s[offset]));
				offset += sizeof(int);
				
				__materialsBag[tmp250] = tmp251;
			}
		}
		
		// deserialize cMaterialsBagCapacity
		__has_cMaterialsBagCapacity = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_cMaterialsBagCapacity)
		{
			__cMaterialsBagCapacity = *((int*) (&s[offset]));
			offset += sizeof(int);
		}
		
		// deserialize ammosBag
		__has_ammosBag = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_ammosBag)
		{
			unsigned char tmp253;
			tmp253 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp254 = std::string(&s[offset], tmp253);
			offset += tmp253;
			while (tmp254.size() < sizeof(unsigned int))
				tmp254 += '\x00';
			unsigned int tmp255;
			tmp255 = *((unsigned int*) (&tmp254[0]));
			
			__ammosBag.clear();
			for (unsigned int tmp256 = 0; tmp256 < tmp255; tmp256++)
			{
				AmmoType tmp257;
				offset++;
				char tmp259;
				tmp259 = *((char*) (&s[offset]));
				offset += sizeof(char);
				tmp257 = (AmmoType) tmp259;
				
				int tmp258;
				offset++;
				tmp258 = *((int*) (&s[offset]));
				offset += sizeof(int);
				
				__ammosBag[tmp257] = tmp258;
			}
		}
		
		// deserialize cAmmosBagCapacity
		__has_cAmmosBagCapacity = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_cAmmosBagCapacity)
		{
			__cAmmosBagCapacity = *((int*) (&s[offset]));
			offset += sizeof(int);
		}
		
		return offset;
	}
};


class Unit : public KSObject
{

protected:

	UnitType __type;
	int __health;
	int __cIndividualHealth;
	int __cIndividualDamage;
	std::map<UnitType, float> __cDamageDistribution;
	int __ammoCount;
	int __reloadRemTime;
	int __cReloadDuration;

	bool __has_type;
	bool __has_health;
	bool __has_cIndividualHealth;
	bool __has_cIndividualDamage;
	bool __has_cDamageDistribution;
	bool __has_ammoCount;
	bool __has_reloadRemTime;
	bool __has_cReloadDuration;


public: // getters

	inline UnitType type() const
	{
		return __type;
	}
	
	inline int health() const
	{
		return __health;
	}
	
	inline int cIndividualHealth() const
	{
		return __cIndividualHealth;
	}
	
	inline int cIndividualDamage() const
	{
		return __cIndividualDamage;
	}
	
	inline std::map<UnitType, float> cDamageDistribution() const
	{
		return __cDamageDistribution;
	}
	
	inline int ammoCount() const
	{
		return __ammoCount;
	}
	
	inline int reloadRemTime() const
	{
		return __reloadRemTime;
	}
	
	inline int cReloadDuration() const
	{
		return __cReloadDuration;
	}
	

public: // reference getters

	inline UnitType &ref_type() const
	{
		return (UnitType&) __type;
	}
	
	inline int &ref_health() const
	{
		return (int&) __health;
	}
	
	inline int &ref_cIndividualHealth() const
	{
		return (int&) __cIndividualHealth;
	}
	
	inline int &ref_cIndividualDamage() const
	{
		return (int&) __cIndividualDamage;
	}
	
	inline std::map<UnitType, float> &ref_cDamageDistribution() const
	{
		return (std::map<UnitType, float>&) __cDamageDistribution;
	}
	
	inline int &ref_ammoCount() const
	{
		return (int&) __ammoCount;
	}
	
	inline int &ref_reloadRemTime() const
	{
		return (int&) __reloadRemTime;
	}
	
	inline int &ref_cReloadDuration() const
	{
		return (int&) __cReloadDuration;
	}
	

public: // setters

	inline void type(const UnitType &type)
	{
		__type = type;
		has_type(true);
	}
	
	inline void health(const int &health)
	{
		__health = health;
		has_health(true);
	}
	
	inline void cIndividualHealth(const int &cIndividualHealth)
	{
		__cIndividualHealth = cIndividualHealth;
		has_cIndividualHealth(true);
	}
	
	inline void cIndividualDamage(const int &cIndividualDamage)
	{
		__cIndividualDamage = cIndividualDamage;
		has_cIndividualDamage(true);
	}
	
	inline void cDamageDistribution(const std::map<UnitType, float> &cDamageDistribution)
	{
		__cDamageDistribution = cDamageDistribution;
		has_cDamageDistribution(true);
	}
	
	inline void ammoCount(const int &ammoCount)
	{
		__ammoCount = ammoCount;
		has_ammoCount(true);
	}
	
	inline void reloadRemTime(const int &reloadRemTime)
	{
		__reloadRemTime = reloadRemTime;
		has_reloadRemTime(true);
	}
	
	inline void cReloadDuration(const int &cReloadDuration)
	{
		__cReloadDuration = cReloadDuration;
		has_cReloadDuration(true);
	}
	

public: // has_attribute getters

	inline bool has_type() const
	{
		return __has_type;
	}
	
	inline bool has_health() const
	{
		return __has_health;
	}
	
	inline bool has_cIndividualHealth() const
	{
		return __has_cIndividualHealth;
	}
	
	inline bool has_cIndividualDamage() const
	{
		return __has_cIndividualDamage;
	}
	
	inline bool has_cDamageDistribution() const
	{
		return __has_cDamageDistribution;
	}
	
	inline bool has_ammoCount() const
	{
		return __has_ammoCount;
	}
	
	inline bool has_reloadRemTime() const
	{
		return __has_reloadRemTime;
	}
	
	inline bool has_cReloadDuration() const
	{
		return __has_cReloadDuration;
	}
	

public: // has_attribute setters

	inline void has_type(const bool &has_type)
	{
		__has_type = has_type;
	}
	
	inline void has_health(const bool &has_health)
	{
		__has_health = has_health;
	}
	
	inline void has_cIndividualHealth(const bool &has_cIndividualHealth)
	{
		__has_cIndividualHealth = has_cIndividualHealth;
	}
	
	inline void has_cIndividualDamage(const bool &has_cIndividualDamage)
	{
		__has_cIndividualDamage = has_cIndividualDamage;
	}
	
	inline void has_cDamageDistribution(const bool &has_cDamageDistribution)
	{
		__has_cDamageDistribution = has_cDamageDistribution;
	}
	
	inline void has_ammoCount(const bool &has_ammoCount)
	{
		__has_ammoCount = has_ammoCount;
	}
	
	inline void has_reloadRemTime(const bool &has_reloadRemTime)
	{
		__has_reloadRemTime = has_reloadRemTime;
	}
	
	inline void has_cReloadDuration(const bool &has_cReloadDuration)
	{
		__has_cReloadDuration = has_cReloadDuration;
	}
	

public:

	Unit()
	{
		has_type(false);
		has_health(false);
		has_cIndividualHealth(false);
		has_cIndividualDamage(false);
		has_cDamageDistribution(false);
		has_ammoCount(false);
		has_reloadRemTime(false);
		has_cReloadDuration(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "Unit";
	}
	
	virtual inline const std::string name() const
	{
		return "Unit";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize type
		s += __has_type;
		if (__has_type)
		{
			char tmp261 = (char) __type;
			auto tmp262 = reinterpret_cast<char*>(&tmp261);
			s += std::string(tmp262, sizeof(char));
		}
		
		// serialize health
		s += __has_health;
		if (__has_health)
		{
			int tmp264 = __health;
			auto tmp265 = reinterpret_cast<char*>(&tmp264);
			s += std::string(tmp265, sizeof(int));
		}
		
		// serialize cIndividualHealth
		s += __has_cIndividualHealth;
		if (__has_cIndividualHealth)
		{
			int tmp267 = __cIndividualHealth;
			auto tmp268 = reinterpret_cast<char*>(&tmp267);
			s += std::string(tmp268, sizeof(int));
		}
		
		// serialize cIndividualDamage
		s += __has_cIndividualDamage;
		if (__has_cIndividualDamage)
		{
			int tmp270 = __cIndividualDamage;
			auto tmp271 = reinterpret_cast<char*>(&tmp270);
			s += std::string(tmp271, sizeof(int));
		}
		
		// serialize cDamageDistribution
		s += __has_cDamageDistribution;
		if (__has_cDamageDistribution)
		{
			std::string tmp272 = "";
			unsigned int tmp274 = __cDamageDistribution.size();
			auto tmp275 = reinterpret_cast<char*>(&tmp274);
			tmp272 += std::string(tmp275, sizeof(unsigned int));
			while (tmp272.size() && tmp272.back() == 0)
				tmp272.pop_back();
			unsigned char tmp277 = tmp272.size();
			auto tmp278 = reinterpret_cast<char*>(&tmp277);
			s += std::string(tmp278, sizeof(unsigned char));
			s += tmp272;
			
			for (auto &tmp279 : __cDamageDistribution)
			{
				s += '\x01';
				char tmp281 = (char) tmp279.first;
				auto tmp282 = reinterpret_cast<char*>(&tmp281);
				s += std::string(tmp282, sizeof(char));
				
				s += '\x01';
				float tmp284 = tmp279.second;
				auto tmp285 = reinterpret_cast<char*>(&tmp284);
				s += std::string(tmp285, sizeof(float));
			}
		}
		
		// serialize ammoCount
		s += __has_ammoCount;
		if (__has_ammoCount)
		{
			int tmp287 = __ammoCount;
			auto tmp288 = reinterpret_cast<char*>(&tmp287);
			s += std::string(tmp288, sizeof(int));
		}
		
		// serialize reloadRemTime
		s += __has_reloadRemTime;
		if (__has_reloadRemTime)
		{
			int tmp290 = __reloadRemTime;
			auto tmp291 = reinterpret_cast<char*>(&tmp290);
			s += std::string(tmp291, sizeof(int));
		}
		
		// serialize cReloadDuration
		s += __has_cReloadDuration;
		if (__has_cReloadDuration)
		{
			int tmp293 = __cReloadDuration;
			auto tmp294 = reinterpret_cast<char*>(&tmp293);
			s += std::string(tmp294, sizeof(int));
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize type
		__has_type = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_type)
		{
			char tmp295;
			tmp295 = *((char*) (&s[offset]));
			offset += sizeof(char);
			__type = (UnitType) tmp295;
		}
		
		// deserialize health
		__has_health = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_health)
		{
			__health = *((int*) (&s[offset]));
			offset += sizeof(int);
		}
		
		// deserialize cIndividualHealth
		__has_cIndividualHealth = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_cIndividualHealth)
		{
			__cIndividualHealth = *((int*) (&s[offset]));
			offset += sizeof(int);
		}
		
		// deserialize cIndividualDamage
		__has_cIndividualDamage = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_cIndividualDamage)
		{
			__cIndividualDamage = *((int*) (&s[offset]));
			offset += sizeof(int);
		}
		
		// deserialize cDamageDistribution
		__has_cDamageDistribution = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_cDamageDistribution)
		{
			unsigned char tmp296;
			tmp296 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp297 = std::string(&s[offset], tmp296);
			offset += tmp296;
			while (tmp297.size() < sizeof(unsigned int))
				tmp297 += '\x00';
			unsigned int tmp298;
			tmp298 = *((unsigned int*) (&tmp297[0]));
			
			__cDamageDistribution.clear();
			for (unsigned int tmp299 = 0; tmp299 < tmp298; tmp299++)
			{
				UnitType tmp300;
				offset++;
				char tmp302;
				tmp302 = *((char*) (&s[offset]));
				offset += sizeof(char);
				tmp300 = (UnitType) tmp302;
				
				float tmp301;
				offset++;
				tmp301 = *((float*) (&s[offset]));
				offset += sizeof(float);
				
				__cDamageDistribution[tmp300] = tmp301;
			}
		}
		
		// deserialize ammoCount
		__has_ammoCount = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_ammoCount)
		{
			__ammoCount = *((int*) (&s[offset]));
			offset += sizeof(int);
		}
		
		// deserialize reloadRemTime
		__has_reloadRemTime = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_reloadRemTime)
		{
			__reloadRemTime = *((int*) (&s[offset]));
			offset += sizeof(int);
		}
		
		// deserialize cReloadDuration
		__has_cReloadDuration = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_cReloadDuration)
		{
			__cReloadDuration = *((int*) (&s[offset]));
			offset += sizeof(int);
		}
		
		return offset;
	}
};


class Base : public KSObject
{

protected:

	std::map<Position, ECell> __cArea;
	std::map<AgentType, Agent> __agents;
	std::vector<FrontlineDelivery> __frontlineDeliveries;
	Warehouse __warehouse;
	BacklineDelivery __backlineDelivery;
	Factory __factory;
	std::map<UnitType, Unit> __units;

	bool __has_cArea;
	bool __has_agents;
	bool __has_frontlineDeliveries;
	bool __has_warehouse;
	bool __has_backlineDelivery;
	bool __has_factory;
	bool __has_units;


public: // getters

	inline std::map<Position, ECell> cArea() const
	{
		return __cArea;
	}
	
	inline std::map<AgentType, Agent> agents() const
	{
		return __agents;
	}
	
	inline std::vector<FrontlineDelivery> frontlineDeliveries() const
	{
		return __frontlineDeliveries;
	}
	
	inline Warehouse warehouse() const
	{
		return __warehouse;
	}
	
	inline BacklineDelivery backlineDelivery() const
	{
		return __backlineDelivery;
	}
	
	inline Factory factory() const
	{
		return __factory;
	}
	
	inline std::map<UnitType, Unit> units() const
	{
		return __units;
	}
	

public: // reference getters

	inline std::map<Position, ECell> &ref_cArea() const
	{
		return (std::map<Position, ECell>&) __cArea;
	}
	
	inline std::map<AgentType, Agent> &ref_agents() const
	{
		return (std::map<AgentType, Agent>&) __agents;
	}
	
	inline std::vector<FrontlineDelivery> &ref_frontlineDeliveries() const
	{
		return (std::vector<FrontlineDelivery>&) __frontlineDeliveries;
	}
	
	inline Warehouse &ref_warehouse() const
	{
		return (Warehouse&) __warehouse;
	}
	
	inline BacklineDelivery &ref_backlineDelivery() const
	{
		return (BacklineDelivery&) __backlineDelivery;
	}
	
	inline Factory &ref_factory() const
	{
		return (Factory&) __factory;
	}
	
	inline std::map<UnitType, Unit> &ref_units() const
	{
		return (std::map<UnitType, Unit>&) __units;
	}
	

public: // setters

	inline void cArea(const std::map<Position, ECell> &cArea)
	{
		__cArea = cArea;
		has_cArea(true);
	}
	
	inline void agents(const std::map<AgentType, Agent> &agents)
	{
		__agents = agents;
		has_agents(true);
	}
	
	inline void frontlineDeliveries(const std::vector<FrontlineDelivery> &frontlineDeliveries)
	{
		__frontlineDeliveries = frontlineDeliveries;
		has_frontlineDeliveries(true);
	}
	
	inline void warehouse(const Warehouse &warehouse)
	{
		__warehouse = warehouse;
		has_warehouse(true);
	}
	
	inline void backlineDelivery(const BacklineDelivery &backlineDelivery)
	{
		__backlineDelivery = backlineDelivery;
		has_backlineDelivery(true);
	}
	
	inline void factory(const Factory &factory)
	{
		__factory = factory;
		has_factory(true);
	}
	
	inline void units(const std::map<UnitType, Unit> &units)
	{
		__units = units;
		has_units(true);
	}
	

public: // has_attribute getters

	inline bool has_cArea() const
	{
		return __has_cArea;
	}
	
	inline bool has_agents() const
	{
		return __has_agents;
	}
	
	inline bool has_frontlineDeliveries() const
	{
		return __has_frontlineDeliveries;
	}
	
	inline bool has_warehouse() const
	{
		return __has_warehouse;
	}
	
	inline bool has_backlineDelivery() const
	{
		return __has_backlineDelivery;
	}
	
	inline bool has_factory() const
	{
		return __has_factory;
	}
	
	inline bool has_units() const
	{
		return __has_units;
	}
	

public: // has_attribute setters

	inline void has_cArea(const bool &has_cArea)
	{
		__has_cArea = has_cArea;
	}
	
	inline void has_agents(const bool &has_agents)
	{
		__has_agents = has_agents;
	}
	
	inline void has_frontlineDeliveries(const bool &has_frontlineDeliveries)
	{
		__has_frontlineDeliveries = has_frontlineDeliveries;
	}
	
	inline void has_warehouse(const bool &has_warehouse)
	{
		__has_warehouse = has_warehouse;
	}
	
	inline void has_backlineDelivery(const bool &has_backlineDelivery)
	{
		__has_backlineDelivery = has_backlineDelivery;
	}
	
	inline void has_factory(const bool &has_factory)
	{
		__has_factory = has_factory;
	}
	
	inline void has_units(const bool &has_units)
	{
		__has_units = has_units;
	}
	

public:

	Base()
	{
		has_cArea(false);
		has_agents(false);
		has_frontlineDeliveries(false);
		has_warehouse(false);
		has_backlineDelivery(false);
		has_factory(false);
		has_units(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "Base";
	}
	
	virtual inline const std::string name() const
	{
		return "Base";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize cArea
		s += __has_cArea;
		if (__has_cArea)
		{
			std::string tmp303 = "";
			unsigned int tmp305 = __cArea.size();
			auto tmp306 = reinterpret_cast<char*>(&tmp305);
			tmp303 += std::string(tmp306, sizeof(unsigned int));
			while (tmp303.size() && tmp303.back() == 0)
				tmp303.pop_back();
			unsigned char tmp308 = tmp303.size();
			auto tmp309 = reinterpret_cast<char*>(&tmp308);
			s += std::string(tmp309, sizeof(unsigned char));
			s += tmp303;
			
			for (auto &tmp310 : __cArea)
			{
				s += '\x01';
				s += tmp310.first.serialize();
				
				s += '\x01';
				char tmp312 = (char) tmp310.second;
				auto tmp313 = reinterpret_cast<char*>(&tmp312);
				s += std::string(tmp313, sizeof(char));
			}
		}
		
		// serialize agents
		s += __has_agents;
		if (__has_agents)
		{
			std::string tmp314 = "";
			unsigned int tmp316 = __agents.size();
			auto tmp317 = reinterpret_cast<char*>(&tmp316);
			tmp314 += std::string(tmp317, sizeof(unsigned int));
			while (tmp314.size() && tmp314.back() == 0)
				tmp314.pop_back();
			unsigned char tmp319 = tmp314.size();
			auto tmp320 = reinterpret_cast<char*>(&tmp319);
			s += std::string(tmp320, sizeof(unsigned char));
			s += tmp314;
			
			for (auto &tmp321 : __agents)
			{
				s += '\x01';
				char tmp323 = (char) tmp321.first;
				auto tmp324 = reinterpret_cast<char*>(&tmp323);
				s += std::string(tmp324, sizeof(char));
				
				s += '\x01';
				s += tmp321.second.serialize();
			}
		}
		
		// serialize frontlineDeliveries
		s += __has_frontlineDeliveries;
		if (__has_frontlineDeliveries)
		{
			std::string tmp325 = "";
			unsigned int tmp327 = __frontlineDeliveries.size();
			auto tmp328 = reinterpret_cast<char*>(&tmp327);
			tmp325 += std::string(tmp328, sizeof(unsigned int));
			while (tmp325.size() && tmp325.back() == 0)
				tmp325.pop_back();
			unsigned char tmp330 = tmp325.size();
			auto tmp331 = reinterpret_cast<char*>(&tmp330);
			s += std::string(tmp331, sizeof(unsigned char));
			s += tmp325;
			
			for (auto &tmp332 : __frontlineDeliveries)
			{
				s += '\x01';
				s += tmp332.serialize();
			}
		}
		
		// serialize warehouse
		s += __has_warehouse;
		if (__has_warehouse)
		{
			s += __warehouse.serialize();
		}
		
		// serialize backlineDelivery
		s += __has_backlineDelivery;
		if (__has_backlineDelivery)
		{
			s += __backlineDelivery.serialize();
		}
		
		// serialize factory
		s += __has_factory;
		if (__has_factory)
		{
			s += __factory.serialize();
		}
		
		// serialize units
		s += __has_units;
		if (__has_units)
		{
			std::string tmp333 = "";
			unsigned int tmp335 = __units.size();
			auto tmp336 = reinterpret_cast<char*>(&tmp335);
			tmp333 += std::string(tmp336, sizeof(unsigned int));
			while (tmp333.size() && tmp333.back() == 0)
				tmp333.pop_back();
			unsigned char tmp338 = tmp333.size();
			auto tmp339 = reinterpret_cast<char*>(&tmp338);
			s += std::string(tmp339, sizeof(unsigned char));
			s += tmp333;
			
			for (auto &tmp340 : __units)
			{
				s += '\x01';
				char tmp342 = (char) tmp340.first;
				auto tmp343 = reinterpret_cast<char*>(&tmp342);
				s += std::string(tmp343, sizeof(char));
				
				s += '\x01';
				s += tmp340.second.serialize();
			}
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize cArea
		__has_cArea = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_cArea)
		{
			unsigned char tmp344;
			tmp344 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp345 = std::string(&s[offset], tmp344);
			offset += tmp344;
			while (tmp345.size() < sizeof(unsigned int))
				tmp345 += '\x00';
			unsigned int tmp346;
			tmp346 = *((unsigned int*) (&tmp345[0]));
			
			__cArea.clear();
			for (unsigned int tmp347 = 0; tmp347 < tmp346; tmp347++)
			{
				Position tmp348;
				offset++;
				offset = tmp348.deserialize(s, offset);
				
				ECell tmp349;
				offset++;
				char tmp350;
				tmp350 = *((char*) (&s[offset]));
				offset += sizeof(char);
				tmp349 = (ECell) tmp350;
				
				__cArea[tmp348] = tmp349;
			}
		}
		
		// deserialize agents
		__has_agents = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_agents)
		{
			unsigned char tmp351;
			tmp351 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp352 = std::string(&s[offset], tmp351);
			offset += tmp351;
			while (tmp352.size() < sizeof(unsigned int))
				tmp352 += '\x00';
			unsigned int tmp353;
			tmp353 = *((unsigned int*) (&tmp352[0]));
			
			__agents.clear();
			for (unsigned int tmp354 = 0; tmp354 < tmp353; tmp354++)
			{
				AgentType tmp355;
				offset++;
				char tmp357;
				tmp357 = *((char*) (&s[offset]));
				offset += sizeof(char);
				tmp355 = (AgentType) tmp357;
				
				Agent tmp356;
				offset++;
				offset = tmp356.deserialize(s, offset);
				
				__agents[tmp355] = tmp356;
			}
		}
		
		// deserialize frontlineDeliveries
		__has_frontlineDeliveries = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_frontlineDeliveries)
		{
			unsigned char tmp358;
			tmp358 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp359 = std::string(&s[offset], tmp358);
			offset += tmp358;
			while (tmp359.size() < sizeof(unsigned int))
				tmp359 += '\x00';
			unsigned int tmp360;
			tmp360 = *((unsigned int*) (&tmp359[0]));
			
			__frontlineDeliveries.clear();
			for (unsigned int tmp361 = 0; tmp361 < tmp360; tmp361++)
			{
				FrontlineDelivery tmp362;
				offset++;
				offset = tmp362.deserialize(s, offset);
				__frontlineDeliveries.push_back(tmp362);
			}
		}
		
		// deserialize warehouse
		__has_warehouse = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_warehouse)
		{
			offset = __warehouse.deserialize(s, offset);
		}
		
		// deserialize backlineDelivery
		__has_backlineDelivery = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_backlineDelivery)
		{
			offset = __backlineDelivery.deserialize(s, offset);
		}
		
		// deserialize factory
		__has_factory = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_factory)
		{
			offset = __factory.deserialize(s, offset);
		}
		
		// deserialize units
		__has_units = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_units)
		{
			unsigned char tmp363;
			tmp363 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp364 = std::string(&s[offset], tmp363);
			offset += tmp363;
			while (tmp364.size() < sizeof(unsigned int))
				tmp364 += '\x00';
			unsigned int tmp365;
			tmp365 = *((unsigned int*) (&tmp364[0]));
			
			__units.clear();
			for (unsigned int tmp366 = 0; tmp366 < tmp365; tmp366++)
			{
				UnitType tmp367;
				offset++;
				char tmp369;
				tmp369 = *((char*) (&s[offset]));
				offset += sizeof(char);
				tmp367 = (UnitType) tmp369;
				
				Unit tmp368;
				offset++;
				offset = tmp368.deserialize(s, offset);
				
				__units[tmp367] = tmp368;
			}
		}
		
		return offset;
	}
};


class World : public KSObject
{

protected:

	int __maxCycles;
	std::map<std::string, Base> __bases_;
	std::map<std::string, int> __totalHealths;

	bool __has_maxCycles;
	bool __has_bases;
	bool __has_totalHealths;


public: // getters

	inline int maxCycles() const
	{
		return __maxCycles;
	}
	
	inline std::map<std::string, Base> bases() const
	{
		return __bases_;
	}
	
	inline std::map<std::string, int> totalHealths() const
	{
		return __totalHealths;
	}
	

public: // reference getters

	inline int &ref_maxCycles() const
	{
		return (int&) __maxCycles;
	}
	
	inline std::map<std::string, Base> &ref_bases() const
	{
		return (std::map<std::string, Base>&) __bases_;
	}
	
	inline std::map<std::string, int> &ref_totalHealths() const
	{
		return (std::map<std::string, int>&) __totalHealths;
	}
	

public: // setters

	inline void maxCycles(const int &maxCycles)
	{
		__maxCycles = maxCycles;
		has_maxCycles(true);
	}
	
	inline void bases(const std::map<std::string, Base> &bases)
	{
		__bases_ = bases;
		has_bases(true);
	}
	
	inline void totalHealths(const std::map<std::string, int> &totalHealths)
	{
		__totalHealths = totalHealths;
		has_totalHealths(true);
	}
	

public: // has_attribute getters

	inline bool has_maxCycles() const
	{
		return __has_maxCycles;
	}
	
	inline bool has_bases() const
	{
		return __has_bases;
	}
	
	inline bool has_totalHealths() const
	{
		return __has_totalHealths;
	}
	

public: // has_attribute setters

	inline void has_maxCycles(const bool &has_maxCycles)
	{
		__has_maxCycles = has_maxCycles;
	}
	
	inline void has_bases(const bool &has_bases)
	{
		__has_bases = has_bases;
	}
	
	inline void has_totalHealths(const bool &has_totalHealths)
	{
		__has_totalHealths = has_totalHealths;
	}
	

public:

	World()
	{
		has_maxCycles(false);
		has_bases(false);
		has_totalHealths(false);
	}
	
	static inline const std::string nameStatic()
	{
		return "World";
	}
	
	virtual inline const std::string name() const
	{
		return "World";
	}
	
	std::string serialize() const
	{
		std::string s = "";
		
		// serialize maxCycles
		s += __has_maxCycles;
		if (__has_maxCycles)
		{
			int tmp371 = __maxCycles;
			auto tmp372 = reinterpret_cast<char*>(&tmp371);
			s += std::string(tmp372, sizeof(int));
		}
		
		// serialize bases
		s += __has_bases;
		if (__has_bases)
		{
			std::string tmp373 = "";
			unsigned int tmp375 = __bases_.size();
			auto tmp376 = reinterpret_cast<char*>(&tmp375);
			tmp373 += std::string(tmp376, sizeof(unsigned int));
			while (tmp373.size() && tmp373.back() == 0)
				tmp373.pop_back();
			unsigned char tmp378 = tmp373.size();
			auto tmp379 = reinterpret_cast<char*>(&tmp378);
			s += std::string(tmp379, sizeof(unsigned char));
			s += tmp373;
			
			for (auto &tmp380 : __bases_)
			{
				s += '\x01';
				std::string tmp381 = "";
				unsigned int tmp383 = tmp380.first.size();
				auto tmp384 = reinterpret_cast<char*>(&tmp383);
				tmp381 += std::string(tmp384, sizeof(unsigned int));
				while (tmp381.size() && tmp381.back() == 0)
					tmp381.pop_back();
				unsigned char tmp386 = tmp381.size();
				auto tmp387 = reinterpret_cast<char*>(&tmp386);
				s += std::string(tmp387, sizeof(unsigned char));
				s += tmp381;
				
				s += tmp380.first;
				
				s += '\x01';
				s += tmp380.second.serialize();
			}
		}
		
		// serialize totalHealths
		s += __has_totalHealths;
		if (__has_totalHealths)
		{
			std::string tmp388 = "";
			unsigned int tmp390 = __totalHealths.size();
			auto tmp391 = reinterpret_cast<char*>(&tmp390);
			tmp388 += std::string(tmp391, sizeof(unsigned int));
			while (tmp388.size() && tmp388.back() == 0)
				tmp388.pop_back();
			unsigned char tmp393 = tmp388.size();
			auto tmp394 = reinterpret_cast<char*>(&tmp393);
			s += std::string(tmp394, sizeof(unsigned char));
			s += tmp388;
			
			for (auto &tmp395 : __totalHealths)
			{
				s += '\x01';
				std::string tmp396 = "";
				unsigned int tmp398 = tmp395.first.size();
				auto tmp399 = reinterpret_cast<char*>(&tmp398);
				tmp396 += std::string(tmp399, sizeof(unsigned int));
				while (tmp396.size() && tmp396.back() == 0)
					tmp396.pop_back();
				unsigned char tmp401 = tmp396.size();
				auto tmp402 = reinterpret_cast<char*>(&tmp401);
				s += std::string(tmp402, sizeof(unsigned char));
				s += tmp396;
				
				s += tmp395.first;
				
				s += '\x01';
				int tmp404 = tmp395.second;
				auto tmp405 = reinterpret_cast<char*>(&tmp404);
				s += std::string(tmp405, sizeof(int));
			}
		}
		
		return s;
	}
	
	unsigned int deserialize(const std::string &s, unsigned int offset=0)
	{
		// deserialize maxCycles
		__has_maxCycles = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_maxCycles)
		{
			__maxCycles = *((int*) (&s[offset]));
			offset += sizeof(int);
		}
		
		// deserialize bases
		__has_bases = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_bases)
		{
			unsigned char tmp406;
			tmp406 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp407 = std::string(&s[offset], tmp406);
			offset += tmp406;
			while (tmp407.size() < sizeof(unsigned int))
				tmp407 += '\x00';
			unsigned int tmp408;
			tmp408 = *((unsigned int*) (&tmp407[0]));
			
			__bases_.clear();
			for (unsigned int tmp409 = 0; tmp409 < tmp408; tmp409++)
			{
				std::string tmp410;
				offset++;
				unsigned char tmp412;
				tmp412 = *((unsigned char*) (&s[offset]));
				offset += sizeof(unsigned char);
				std::string tmp413 = std::string(&s[offset], tmp412);
				offset += tmp412;
				while (tmp413.size() < sizeof(unsigned int))
					tmp413 += '\x00';
				unsigned int tmp414;
				tmp414 = *((unsigned int*) (&tmp413[0]));
				
				tmp410 = s.substr(offset, tmp414);
				offset += tmp414;
				
				Base tmp411;
				offset++;
				offset = tmp411.deserialize(s, offset);
				
				__bases_[tmp410] = tmp411;
			}
		}
		
		// deserialize totalHealths
		__has_totalHealths = *((unsigned char*) (&s[offset]));
		offset += sizeof(unsigned char);
		if (__has_totalHealths)
		{
			unsigned char tmp415;
			tmp415 = *((unsigned char*) (&s[offset]));
			offset += sizeof(unsigned char);
			std::string tmp416 = std::string(&s[offset], tmp415);
			offset += tmp415;
			while (tmp416.size() < sizeof(unsigned int))
				tmp416 += '\x00';
			unsigned int tmp417;
			tmp417 = *((unsigned int*) (&tmp416[0]));
			
			__totalHealths.clear();
			for (unsigned int tmp418 = 0; tmp418 < tmp417; tmp418++)
			{
				std::string tmp419;
				offset++;
				unsigned char tmp421;
				tmp421 = *((unsigned char*) (&s[offset]));
				offset += sizeof(unsigned char);
				std::string tmp422 = std::string(&s[offset], tmp421);
				offset += tmp421;
				while (tmp422.size() < sizeof(unsigned int))
					tmp422 += '\x00';
				unsigned int tmp423;
				tmp423 = *((unsigned int*) (&tmp422[0]));
				
				tmp419 = s.substr(offset, tmp423);
				offset += tmp423;
				
				int tmp420;
				offset++;
				tmp420 = *((int*) (&s[offset]));
				offset += sizeof(int);
				
				__totalHealths[tmp419] = tmp420;
			}
		}
		
		return offset;
	}
};

} // namespace models

} // namespace ks

#endif // _KS_MODELS_H_
