#ifndef _TELEGRAM_H_
#define _TELEGRAM_H_

namespace GOAP
{
	class Object;
	enum ObjectID;
}

struct Telegram
{
	ObjectID Sender;
	ObjectID Receiver;
	MessageType Msg;
	void*	ExtraInfo;

};

#endif