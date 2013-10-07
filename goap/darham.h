enum ObjectType
{
};

enum ObjectKey
{
};

union Value
{
};

class Object
{
	int m_id;
}

class Condition
{
	int objID;
	ObjectKey key;
	Value value;
};

class ActionTemplate
{
	ObjectType m_paramTypes;
	Condition* preconds;
	Condition* effects;
};

class Action
{
	ActionTemplate* m_template;
};

class ActionFactory
{
};

class Stab : public Action
{
};