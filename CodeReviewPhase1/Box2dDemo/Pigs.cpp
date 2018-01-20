#include "Pigs.h"

Pigs::Pigs(b2World& world, CSDL_Setup* csdl_setup, int xpos, int ypos)
{
	createPig(world, xpos, ypos);
	
	m_pigIdleAnimation = new Sprite(csdl_setup->GetRenderer(), "images/Piggy.png", xpos, ypos, 25, 25,2,1);
	m_pigDeathAnimation = new Sprite(csdl_setup->GetRenderer(), "images/pigDeath.png", xpos, ypos, 25, 25, 3, 1);
}


Pigs::~Pigs()
{
	delete m_pigIdleAnimation;
	delete m_pigDeathAnimation;
}

void Pigs::createPig(b2World& world, int xpos, int ypos)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(xpos * P2M, ypos * P2M);
	m_pigBody = world.CreateBody(&bodyDef);
	m_pigBody->SetAngularDamping(5.0f);
	m_pigBody->SetUserData(&pigUserData);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = 25 * P2M;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;
	m_pigBody->CreateFixture(&fixtureDef);
}
