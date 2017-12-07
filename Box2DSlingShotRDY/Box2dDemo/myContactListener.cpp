#include "myContactListener.h"

myContactListener::myContactListener()
{
}

myContactListener::~myContactListener()
{
}

void myContactListener::BeginContact(b2Contact * contact)
{
	/*b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	int dataA = *((int*)bodyA->GetUserData());
	int dataB = *((int*)bodyB->GetUserData());
	if (dataA == 2) {
		std::cout << "PigA made contact!" << std::endl;
	}
	if (dataB == 2) {
		std::cout << "PigA made contact!" << std::endl;
	}*/
}

void myContactListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
	if (contact->GetFixtureA() != NULL && contact->GetFixtureA()->GetBody()->GetUserData() != NULL  && *(int*)contact->GetFixtureA()->GetBody()->GetUserData() == 2) {
		if (*impulse->normalImpulses > 0.7f) {
			std::cout << "bird x pig" << std::endl;
			contact->GetFixtureA()->GetBody()->SetUserData(&pigDead);
		}
	}


	if (contact->GetFixtureB() != NULL && contact->GetFixtureB()->GetBody()->GetUserData() != NULL  && *(int*)contact->GetFixtureB()->GetBody()->GetUserData() == 2)
	{
		if (*impulse->normalImpulses > 0.7f) {
			std::cout << "bird x pig" << std::endl;
			contact->GetFixtureB()->GetBody()->SetUserData(&pigDead);
		}
	}
}
