#include <list>

class WorldModel;

union Value
{
	bool bValue;
	float fValue;
	int iValue;
};

typedef void* Key;

struct Condition
{
	Key /*which is a pointer/reference to a world attribute*/ key;
	Value value;
};

class Action
{
public:
	Action(int pre, int post/*, list<cond> pre, list<cond> post*/);
	void AddPreCond(Condition);
	void AddEffect(Condition);
	void Apply(WorldModel* worldModel);
private:
	Condition* preconds;
	Condition* effects;
	int m_numPreConds;
	int m_numPostConds;	
};