// Serialization: state -> file (like save in game)
// XML, JSON
// ctrl+K - ctrl+D	 - for proper formating
//ctrl + arrow up/down

#include <iostream>
#include <vector>
#include <bitset>		// ???


namespace Core
{
	namespace Util
	{
		// for educational purposes ???
		bool isLittleEndian() {
			int8_t a = 5;
			std::string result = std::bitset<8>(a).to_string();
			if (result.back() == '1') return true;
		}
	}

	// ???
	// little endian
	// 0 1 2 3
	// 0x00 0x00 0x00 0x5
	template <typename T>
	void encode(std::vector<int8_t>* buffer, int16_t* iterator, T value)
	{
		// IMHO could be errors here
		for (unsigned i = 0, j = 0; i < sizeof(T); i++) {
			(*buffer)[(*iterator)++] = (value >> ((sizeof(T) * 8) - 8) - ((i == 0) ? j : j += 8));		// ???

		}
	}
}

namespace ObjectModel
{

	enum class Wrapper {
		PRIMITIVE = 1,		// 1 ???
		ARRAY,
		STRING,
		OBJECT
	};

	enum class Type : int8_t {
		I8 = 1,
		I16,
		I32,
		I64,

		U8,
		U16,
		U32,
		U64,

		FLOAT,
		DOUBLE,

		BOOL
	};

	// abstract class
	class Root
	{
	protected:
		std::string name;
		int16_t nameLength;
		int8_t wrapper;
		int32_t size;		// ???

	protected:
		Root();		// protected constructor ??? can't create instance of this class. Only if inharite from it
		// similar to 
		// public:
		//	Root();
		//  virtual void pack() = 0;
	public:
		int32_t getSize();
		void setName(std::string);
		std::string getName();

		virtual void pack(std::vector<int8_t>*, int16_t*);		// ???
	};

	class Primitive : public Root
	{
	private:
		int8_t type = 0;
		std::vector<int8_t>* data = nullptr;

	private:
		Primitive();
	public:
		static Primitive* createI32(std::string name, Type type, int32_t value);	// abstract factory/builder pattern		// static ???
		void pack(std::vector<int8_t>*, int16_t*);

	};

	class Array : public Root
	{

	};

	class Object : public Root
	{

	};

	// definition

	// : - init list, best practice
	Root::Root()
		:
		name("unknown"),
		wrapper(0),
		nameLength(0),
		size(sizeof nameLength + sizeof wrapper + sizeof size) {}		// ???

	void Root::setName(std::string name) {
		this->name = name;
		nameLength = (int16_t)name.size();
		size += nameLength;
	}

	int32_t Root::getSize() {
		return size;
	}

	void Root::pack(std::vector<int8_t>*, int16_t*) {
		// maybe pure virtual ???
	}

	std::string Root::getName() {
		return name;
	}

	Primitive::Primitive() {
		size += sizeof type;
	}

	Primitive* Primitive::createI32(std::string name, Type type, int32_t value) {
		Primitive* p = new Primitive();
		p->setName(name);
		p->wrapper = static_cast<int8_t>(Wrapper::PRIMITIVE);
		p->type = static_cast<int8_t>(type);
		p->data = new std::vector<int8_t>(sizeof(value));

		int16_t iterator = 0;		// ???
		Core::encode(p->data, &iterator, value);		// ???

		return p;
	}

	void Primitive::pack(std::vector<int8_t>*, int16_t*) {
		

	}
}


// Event system
namespace EventSystem {
	class Event;

	class System {
	private:
		friend class Event;		// ???
		std::string name;
		int32_t descriptor;
		int16_t index;		// if there is more than one Event System
		bool active;
		std::vector <Event*> events;
	public:
		System(std::string);
		~System();
	public:
		void addEvent(Event*);
		Event* getEvent();	// getter
		void setEvent();	// setter
		bool isActive();

		void serialize();
	};

	class Event {
	public:
		enum DeviceType : int8_t {
			KEYBOARD = 1,		// why 1, not 0 ???
			MOUSE,
			TOUCHPAD,
			JOYSTICK,
		};
		DeviceType dType;
		System* system_p = nullptr;
	public:
		Event(DeviceType);
		DeviceType getdType();
		// for output
		// friend - this function can access to private members of class	???
		// operator overloading:
		//		return type - std::ostream&
		//		function name - operator<<
		//		parameters - std::ostream& stream, const DeviceType dType
		friend std::ostream& operator<< (std::ostream& stream, const DeviceType dType) {
			// typetraits	???
			std::string result;
#define PRINT(a) result = #a;	// stringify
			switch (dType) {
			case KEYBOARD: PRINT(KEYBOARD); break;
			case MOUSE: PRINT(MOUSE); break;
			case TOUCHPAD: PRINT(TOUCHPAD); break;
			case JOYSTICK: PRINT(KEYBOARD); break;
			}
			return stream << result;
		}
		void bind(System*, Event*);

	};

	class KeyboardEvent : public Event {
	private:
		int16_t	keyCode;
		bool pressed;
		bool released;
	public:
		KeyboardEvent(int16_t, bool, bool);

	};

	// definition
	System::System(std::string name) :
		name(name),
		descriptor(1),		// random number for now
		index(1),
		active(true)
	{}

	System::~System() {
		//TODO:
	}

	void System::addEvent(Event* e) {
		e->bind(this, e);
	}

	Event* System::getEvent() {
		return events.front();
		//TODO: ...
	}

	bool System::isActive() {
		if (system) return true;
		return false;
	}

	void System::serialize() {

	}

	/*Event::Event(DeviceType dType) :
		dType(dType){}*/
	Event::Event(DeviceType dType) {
		this->dType = dType;
	}

	void Event::bind(System* system, Event* e) {
		this->system_p = system;
		this->system_p->events.push_back(e);
	}

	Event::DeviceType Event::getdType() {
		return this->dType;
	}

	KeyboardEvent::KeyboardEvent(int16_t keyCode, bool pressed, bool released) :
		Event(Event::KEYBOARD),
		keyCode(keyCode),
		pressed(pressed),
		released(released)
	{}

}

using namespace EventSystem;
using namespace ObjectModel;

int main(int argc, char** argv) {

	int32_t foo = 5;
	Primitive* p = Primitive::createI32("int32", Type::I32, foo);




	//EventSystem::System Foo("Foo");
	//EventSystem::Event* e = new EventSystem::KeyboardEvent('a', true, false);
	//EventSystem::KeyboardEvent* kb = static_cast<EventSystem::KeyboardEvent*>(Foo.getEvent());
	//Foo.addEvent(e);
	//Foo.serialize();

	return 0;
}
