#include "TimeStepper.h"

void ForwardEuler::takeStep(ParticleSystem* particleSystem, float stepSize)
{
  vector<Vector3f> state = particleSystem->getState();
  vector<Vector3f> deriv = particleSystem->evalF(state);
  vector<Vector3f> newState = vector<Vector3f>();
  for (unsigned i=0; i < state.size(); i++) {
    newState.push_back( state[i]+stepSize*deriv[i] );
  }
  particleSystem->setState(newState);
}

void Trapzoidal::takeStep(ParticleSystem* particleSystem, float stepSize)
{
  vector<Vector3f> state = particleSystem->getState();
  vector<Vector3f> f_0 = particleSystem->evalF(state);

  vector<Vector3f> temp = vector<Vector3f>();
  for (unsigned i=0; i < state.size(); i++) {
    temp.push_back( state[i]+ stepSize*f_0[i] );
  }

  vector<Vector3f> f_1 = particleSystem->evalF(temp);

  vector<Vector3f> newState = vector<Vector3f>();
  for (unsigned i=0; i < state.size(); i++) {
    newState.push_back( state[i]+(stepSize/2.0 * (f_0[i] + f_1[i])) );
  }
  particleSystem->setState( newState );
}
