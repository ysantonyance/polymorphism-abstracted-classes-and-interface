#include <iostream>
using namespace std;

class Ability abstract
{
public:
	virtual void Use() = 0;
	virtual string Name() = 0;
	virtual ~Ability() {};
};

class Flight : public Ability
{
	void Use() override
	{
		cout << "I'm flying!\n";
	}

	string Name() override
	{
		return "Flight";
	}
};

class SpiderWebs : public Ability
{
public:
	void Use() override
	{
		cout << "*shoots*\t*pew pew pew*\n";
	}

	string Name() override
	{
		return "Spider Webs";
	}
};

class SpiderSense : public Ability
{
public:
	void Use() override
	{
		cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	}

	string Name() override
	{
		return "Spider Sense";
	}
};

class SuperRegeneration : public Ability
{
public:
	void Use() override
	{
		cout << "I'm ready to fight again\n";
	}

	string Name() override
	{
		return "Super Regeneration";
	}
};

class LaserEyes : public Ability
{
public:
	void Use() override
	{
		cout << "*shoots with lasers*\n";
	}

	string Name() override
	{
		return "Laser Eyes";
	}
};


/////////////////////////////////////////////////////

class Role abstract
{
public:
	virtual bool IsGood() abstract {};
	virtual ~Role() = 0;
};

class Good : public Role
{
public:
	bool IsGood() override
	{
		return true;
	}
};

class Bad : public Role
{
public:
	bool IsGood()
	{
		return false;
	}
};

/////////////////////////////////////////////////////

enum class Race
{
	Human,
	Alien,
	God
};

/////////////////////////////////////////////////////

class SuperHero abstract
{
protected:
	string name;
	Race race;
	Role* role;

	Ability* abilities[5];
	int AbilityCount;

public:
	SuperHero(string name, Race race, Role* role) : name(name), race(race), role(role), AbilityCount(0)
	{}

	void AddAbility(Ability* abilities)
	{
		if (AbilityCount < 5)
		{
			this->abilities[AbilityCount++] = abilities;
		}	
	}

	bool CanFly()
	{
		for (int i = 0; i < AbilityCount; i++)
		{
			if (string(abilities[i]->Name()) == "Flight")
				return true;
		}
		return false;
	}

	void ShowInfo() const
	{
		cout << "Name: " << name << "\n";
		cout << "Race: " << (race == Race::Human ? "Human" : race == Race::God ? "God" : "Alien") << "\n";
		cout << "Role: " << (role->IsGood() ? "Good" : "Bad") << "\n";
		cout << "Abilities: ";
		for (int i = 0; i < AbilityCount; i++)
		{
			if (i == AbilityCount - 1)
				cout << abilities[i]->Name() << ".";
			else
				cout << abilities[i]->Name() << ", ";
		}
		cout << "\n\n";
	}

	virtual ~SuperHero()
	{
		delete role;
		for (int i = 0; i < AbilityCount; i++)
		{
			delete abilities[i];
		}
	}

	string GetName()
	{
		return name;
	}
};

class SpiderMan : public SuperHero
{
public:
	SpiderMan() : SuperHero("Spider-Man", Race::Human, new Good)
	{
		AddAbility(new SpiderWebs());
		AddAbility(new SpiderSense());
	}
};

class Thor : public SuperHero
{
public:
	Thor() : SuperHero("Thor", Race::God, new Good)
	{
		AddAbility(new Flight());
		AddAbility(new SuperRegeneration());
	}
};

class SuperMan : public SuperHero
{
public:
	SuperMan() : SuperHero("SuperMan", Race::Alien, new Good)
	{
		AddAbility(new Flight());
		AddAbility(new LaserEyes());
	}
};

Role::~Role() {};

int main()
{
	SuperHero* heroes[3];
	heroes[0] = new SpiderMan();
	heroes[1] = new Thor();
	heroes[2] = new SuperMan();

	for (int i = 0; i < 3; i++)
	{
		heroes[i]->ShowInfo();
	}

	for (int i = 0; i < 3; i++)
	{
		if (heroes[i]->CanFly())
			cout << heroes[i]->GetName() << " can fly\n";
	}

	for (int i = 0; i < 3; i++)
	{
		delete heroes[i];
	}
}