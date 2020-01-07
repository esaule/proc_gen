#include <iostream>
#include <cstdint>
#include <math.h>
#include <random>

std::default_random_engine generator;

void genblock(int64_t i, int64_t j, int64_t sx, int64_t sy, int64_t worldID) {
  float dist_to_center = sqrt((i-sx/2.)/sx * (i-sx/2.)/sx + (j-sy/2.)/sy * (j-sy/2.)/sy);
  float density = 0;
  if (dist_to_center > .25  && dist_to_center < .4)
    density = dist_to_center;

  float boxsizex = (1./sx);
  float boxsizey = (1./sy);

  float orix = i*boxsizex;
  float oriy = j*boxsizey;
  
  
  double gentotalexpected = 1000*density/(sx*sy);
  std::poisson_distribution<int64_t> distribution(gentotalexpected);
  int64_t gentotal = distribution(generator);
  gentotal = std::max (gentotal, (int64_t)0);
  
  
  std::cerr<<"i="<<i<<" j="<<j<<" sx="<<sx<<" sy="<<sy<<" density="<<density<<" gentotal="<<gentotal<<" gentotalexpected="<<gentotalexpected<<"\n";
  
  for (uint64_t it = 0; it<gentotal; it++) {
    float rx = ((double)(generator()-generator.min()))/(generator.max() - generator.min());
    float ry = ((double)(generator()-generator.min()))/(generator.max() - generator.min());

    float px = rx*boxsizex+orix;
    float py = ry*boxsizey+oriy;

    std::cout<<px<<" "<<py<<"\n";
  }
}

void genblock_reproducible(int64_t i, int64_t j, int64_t sx, int64_t sy, int64_t worldID) {
  std::default_random_engine generator (worldID + i*sy+j);
    
  float dist_to_center = sqrt((i-sx/2.)/sx * (i-sx/2.)/sx + (j-sy/2.)/sy * (j-sy/2.)/sy);
  float density = 0;
  if (dist_to_center > .25  && dist_to_center < .4)
    density = dist_to_center;

  float boxsizex = (1./sx);
  float boxsizey = (1./sy);

  float orix = i*boxsizex;
  float oriy = j*boxsizey;
  
  
  double gentotalexpected = 1000*density/(sx*sy);
  std::poisson_distribution<int64_t> distribution(gentotalexpected);
  int64_t gentotal = distribution(generator);
  gentotal = std::max (gentotal, (int64_t)0);
  
  
  std::cerr<<"i="<<i<<" j="<<j<<" sx="<<sx<<" sy="<<sy<<" density="<<density<<" gentotal="<<gentotal<<" gentotalexpected="<<gentotalexpected<<"\n";
  
  for (uint64_t it = 0; it<gentotal; it++) {
    float rx = ((double)(generator()-generator.min()))/(generator.max() - generator.min());
    float ry = ((double)(generator()-generator.min()))/(generator.max() - generator.min());

    float px = rx*boxsizex+orix;
    float py = ry*boxsizey+oriy;

    std::cout<<px<<" "<<py<<"\n";
  }
}


int main () {
  int64_t nbblocksX = 20;
  int64_t nbblocksY = 20;

  generator.seed(0);

  //all
  if (0)
  for (int64_t i=0; i<nbblocksX; ++i)
    for (int64_t j=0; j<nbblocksY; ++j)
      genblock(i, j, nbblocksX, nbblocksY, 0);

  //reverse
  if (0)
  for (int64_t j=0; j<nbblocksY; ++j)
    for (int64_t i=0; i<nbblocksX; ++i)
      genblock(i, j, nbblocksX, nbblocksY, 0);

  //allrep
  if (0)
  for (int64_t i=0; i<nbblocksX; ++i)
    for (int64_t j=0; j<nbblocksY; ++j)
      genblock_reproducible(i, j, nbblocksX, nbblocksY, 0);

  //reverserep
  if (1)
  for (int64_t j=0; j<nbblocksY; ++j)
    for (int64_t i=0; i<nbblocksX; ++i)
      genblock_reproducible(i, j, nbblocksX, nbblocksY, 0);
  
  return 0;
}
