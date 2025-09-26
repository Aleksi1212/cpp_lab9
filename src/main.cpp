#include <iostream>

using namespace std;

class Observer;
class Subject
{
	public:
		virtual void Attach(Observer *o) = 0;
		virtual void Notify() const = 0;
};
class Observer
{
	public:
		virtual void Update() const = 0;
};

class Person
{
	private:
		string name;
	public:
		Person(const char* name = "nobody");
		virtual ~Person() = default;
		virtual void identity() const;
		virtual void interrogate() {};
};

class Spy: public Person, public Subject
{
	private:
		string alias;
		int resistance;
		Observer *observer = nullptr;
	public:
		Spy(const char* name, const char* alias, int resistance = 0);
		void set_identity(const char *alias);
		void identity() const;
		void interrogate();
		void Attach(Observer *o);
		void Notify() const;
};

class Judge: public Person, public Observer
{
	public:
		Judge(const char *name);
		void Update() const;
};

/*
	Person methods
*/
Person::Person(const char *name) : name(name) {}
void Person::identity() const { cout << "My name is: " << name << endl; }

/*
	Spy methods
*/
Spy::Spy(const char *name, const char *alias, int resistance) :
Person(name), alias(alias), resistance(resistance) {}
void Spy::set_identity(const char *_alias) { alias = _alias; }
void Spy::interrogate() { resistance--; }
void Spy::identity() const
{
	if (resistance <= 0) {
		Notify();
		Person::identity();
	}
	cout << ((resistance > 0) ? "My name is: " : "My alias is: ")
		<< alias << endl;
}
void Spy::Attach(Observer *o) { observer = o; }
void Spy::Notify() const
{
	if (observer)
		observer->Update();
}

/*
	Judge methods
*/
Judge::Judge(const char *name) : Person(name) {}
void Judge::Update() const
{
	cout << '[';
	Person::identity();
	cout << " I'm sending a spy to prison!]" << endl;
}

int main(int argc, char** argv) {

	Person agent("James Bond");
	Spy spy("Emilio Largo", "William Johnson", 3);
	Spy spy2("Ernst Blofield", "John Keats", 5);
	Judge judge("Judge Barnhill");
	spy.Attach(&judge);
	spy2.Attach(&judge);

	cout << endl << "Nice to meet you. ";
	agent.identity();

	for (int i = 0; i < 6; ++i) {
		cout << "Who are you?" << endl;
		spy.interrogate();
		spy.identity();
	}
	spy.set_identity("Bill Munny");
	spy.identity();

	cout << endl << "Nice to meet you. ";
	agent.identity();

	for (int i = 0; i < 6; ++i) {
		cout << "Who are you?" << endl;
		spy2.interrogate();
		spy2.identity();
	}

	return 0;
}