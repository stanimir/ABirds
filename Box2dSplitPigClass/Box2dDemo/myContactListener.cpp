#include "myContactListener.h"

myContactListener::myContactListener()
{
}

myContactListener::~myContactListener()
{
}

void myContactListener::BeginContact(b2Contact * contact)
{
	b2Fixture* fa = contact->GetFixtureA();
	b2Fixture* fb = contact->GetFixtureB();
	std::cout << "A contact was made!" << std::endl;
	if (fa == nullptr || fb == nullptr) {
		return;
	}

	if (fa->GetUserData() == NULL || fb->GetUserData() == NULL) {
		return;
	}

}
