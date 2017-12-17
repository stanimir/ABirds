#include "Birds.h"



Birds::Birds(b2World& world, CSDL_Setup* csdl_setup, int xpos, int ypos)
{
	createBird(world, xpos, ypos);
	m_birdSprite = new Sprite(csdl_setup->GetRenderer(), "images/newbird.png", xpos, ypos, 25, 25);
}


Birds::~Birds()
{
	delete m_birdSprite;
}

void Birds::createBird(b2World & world, int xpos, int ypos)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(xpos * P2M, ypos * P2M);
	m_birdBody = world.CreateBody(&bodyDef);
	m_birdBody->SetAngularDamping(5.0f);
	m_birdBody->SetUserData(&birdUserData);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = 25 * P2M;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.1f;
	m_birdBody->CreateFixture(&fixtureDef);
}
