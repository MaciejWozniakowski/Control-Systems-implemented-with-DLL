#include <stdio.h>
#include <math.h>

int * modulator(float power){
  static int outputs[4];
  float x1 = 0, x2 = 0;
  if(x1>2.0){ // counter reset, so that sin function takes memory efficient args
    x1 = 0;
  }
  if(sin(0.0001*x1)>=0){ // transistor 1 and 2 signals are inverted
    x1+= 0.000001;
    outputs[0] = 1;
    outputs[1] = 0;
  }
    
  if(sin(0.0001*x1)<0){

    x1+= 0.000001;
    outputs[0] = 0;
    outputs[1] = 1;
  }
 // transistor 3 and 4 signals dictate the power of the converter
 // signal 4 is signal 3 inverted  
  if(x2 > 2.0){
    x2 = 0;
  }
  if(sin(0.0001*x2 +(0.0001 * power))>= 0){
    x2 += 0.000001;
    outputs[2] = 1;
    outputs[3] = 0;
  }
  if(sin(0.0001*x2 +(0.0001 * power))< 0){
    x2 += 0.000001;
    outputs[2] = 0;
    outputs[3] = 1;
  }
  
  return outputs;
}

int main(){
  int *sth; 
  sth = modulator(0.1);
  return 0;
}
