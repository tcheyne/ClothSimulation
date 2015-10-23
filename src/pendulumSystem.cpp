#include <iostream>
#include "pendulumSystem.h"

using namespace std;

PendulumSystem::PendulumSystem(int numParticles):ParticleSystem(numParticles)
{
	m_numParticles = numParticles;

	m_vVecState.push_back(Vector3f(0,4,0));
	m_vVecState.push_back(Vector3f(0,0,0));
	// fill in code for initializing the state based on the number of particles
	for (int i = 0; i < m_numParticles; i++) {

		// for this system, we care about the position and the velocity
		Vector3f position = Vector3f(i+1,4,0);
		Vector3f velocity = Vector3f(0,0,0);

		m_vVecState.push_back(position);
		m_vVecState.push_back(velocity);
		m_vSprings.push_back(Vector4f(i,i+1,5,1));
	}


	m_vSprings.push_back(Vector4f(0,1,5,1));
}

// for a given state, evaluate f(X,t)
vector<Vector3f> PendulumSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;
	f.push_back(Vector3f(0,0,0));
	f.push_back(Vector3f(0,0,0));

	// YOUR CODE HERE
	for (unsigned i=2; i < state.size(); i+=2) {
		Vector3f position = state[i];
		Vector3f velocity = state[i+1];
		Vector3f force = Vector3f();

		float mass = 1;
		float g = -.25;
		Vector3f gravity = Vector3f(0,mass*g,0);
		force += gravity;

		float drag = .1;
		Vector3f viscousDrag = -drag * velocity;
		force += viscousDrag;

		for (unsigned j=0; j < m_vSprings.size(); j++) {
			Vector4f spring = m_vSprings[j];
			float springConstant = spring.z();
			float restLength = spring.w();
			if (spring.x() == i/2) {
				Vector3f dist = position - state[spring.y()*2];
				force += -springConstant*(dist.abs() - restLength)*(dist.normalized());
			}
			else if (spring.y() == i/2) {
				Vector3f dist = position - state[spring.x()*2];
				force += -springConstant*(dist.abs() - restLength)*(dist.normalized());
			}
		}

		f.push_back(velocity);
		f.push_back(force/mass);
	}

	return f;
}

// render the system (ie draw the particles)
void PendulumSystem::draw()
{
	for (int i = 0; i < m_numParticles+1; i++) {
		Vector3f pos = m_vVecState[i*2];//  position of particle i. YOUR CODE HERE
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2] );
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();
	}
}
