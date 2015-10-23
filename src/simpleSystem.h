#ifndef SIMPLESYSTEM_H
#define SIMPLESYSTEM_H

#include "extra.h"
#include <vector>

#include "particleSystem.h"

using namespace std;

class SimpleSystem: public ParticleSystem
{
public:
	SimpleSystem();
	
	vector<Vector3f> evalF(vector<Vector3f> state);
	
	void draw();
	
};

#endif
