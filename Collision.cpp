#include "Collision.h"

const double RADIUS = 0.1;
const double COEFICIENT_OF_RESTITUTION = 0;

// Box dimension
const double FRONT = 1;
const double BACK = -1;
const double LEFT = -1;
const double RIGHT = 1;
const double BOTTOM = -0.5;
const double TOP = 2;

collision_info detect_particle_collision(Particle* particle) {
    
    collision_info ci;
    ci.collided = false;

	particle->find_neighborhood(H);
    for (int i = 0; i < particle->adjList.size(); i++) {
		double distance = distanceVec3(particle->getPosition(), particle->adjList[i]->getPosition());
        
		if (distance <= (PARTICLE_RADIUS * 2)){//distance < (PARTICLE_RADIUS * 2)+ 0.001){
            ci.collided = true;
            ci.d = PARTICLE_RADIUS * 2 - distance;
            ci.cp = Vec3(
				((particle->getPosition()).x + (particle->adjList[i]->getPosition()).x) / 2,
				((particle->getPosition()).y + (particle->adjList[i]->getPosition()).y) / 2,
				((particle->getPosition()).z + (particle->adjList[i]->getPosition()).z) / 2
                         );
            ci.n = difVec3(ci.cp, particle->getPosition());
            break;
        }
    }
    
    return ci;
}

collision_info detect_boundary_collision(Particle* particle) {
    
    collision_info ci;
    ci.collided = false;
    ci.n = Vec3(0, 0, 0);
    
    Vec3 pos = particle->getPosition();
    
    if (pos.x > RIGHT - PARTICLE_RADIUS){
        ci.n.x = -1;
       // std::cout << "x+col" << std::endl;
    }

    if (pos.x < LEFT + PARTICLE_RADIUS){
        ci.n.x = 1;
       // std::cout << "x-col" << std::endl;

    }
    if (pos.y > TOP - PARTICLE_RADIUS){
        ci.n.y = -1;
       // std::cout << "y+col" << std::endl;

    }
    
    if (pos.y < BOTTOM + PARTICLE_RADIUS){
        ci.n.y = 1;
      //  std::cout << "y-col" << std::endl;

    }
    
    if (pos.z < BACK + PARTICLE_RADIUS){
        ci.n.z = 1;
      //  std::cout << "z+col" << std::endl;

    }
    
    if (pos.z > FRONT - PARTICLE_RADIUS){
        ci.n.z = -1;
      //  std::cout << "z-col" << std::endl;

    }
    
    if (normVec3(ci.n) > 0) {
        
        ci.collided = true;
        
        Vec3 cp = Vec3(0,0,0);
        
        if (ci.n.x != 0) {
            cp.y = pos.y;
            cp.z = pos.z;
            
            if (ci.n.x > 0) {
                cp.x = LEFT + PARTICLE_RADIUS;
            }else {
                cp.x = RIGHT - PARTICLE_RADIUS;
            }
        }else if (ci.n.y != 0) {
            cp.x = pos.x;
            cp.z = pos.z;
            
            if (ci.n.y > 0) {
                cp.y = BOTTOM + PARTICLE_RADIUS;
            }else {
                cp.y = TOP - PARTICLE_RADIUS;
            }
        }else if (ci.n.z != 0) {
            cp.x = pos.x;
            cp.y = pos.y;
            
            if (ci.n.z > 0) {
                cp.z = BACK - PARTICLE_RADIUS;
            }else {
                cp.z = FRONT + PARTICLE_RADIUS;
            }
        }

        ci.d = distanceVec3(cp, pos);
        ci.cp = cp;
    }
    
    return ci;
}

void handle_collision(Particle* particle, collision_info ci, double timestep) {
    if (ci.collided) {
        Vec3 velocity = particle->getVelocity();
    
        double  term1 = 1 + (COEFICIENT_OF_RESTITUTION * (ci.d / (timestep * normVec3(velocity))));
    
        Vec3    term2 = multscalarVec3(ci.n, dot3(velocity, ci.n));
        Vec3    term1_term2 = multscalarVec3(term2, term1);
        Vec3    res = difVec3(velocity, term1_term2);

        particle->setPosition(ci.cp);
        particle->setVelocity(res);
       // std::cout << "newVel: " << res.x << " " << res.z << " " << res.y << std::endl;
    }
    
}