#include <math.h>
#include "PIDNN.h"

void setup(){
  Serial.begin(115200);
  // Simulated System Variables
  float ts = 0.01;
  float measured = 0;
  float output = 0;

  // Dynamic System Variables
  float xddot = 0, xdot = 0, x = 0;
  float G = 10, a = 0.1, b = 1, c = 0.1;

  // Neural Net Variables
  float learning_rate = 1e-2*ts, max_change = 0.5*log(WINDOW_SIZE + 1), tolerance = 1e-20;
  float weightP = 0.03, weightI = 0.1, weightD = 0.6;
  
  int setpoint;

  // Initializing Neural Net
  PIDNN* NeuralNet = new PIDNN(learning_rate, max_change, tolerance, ts);
  NeuralNet -> setStartWeight(weightP, weightI, weightD);
  NeuralNet -> setOutputLimit(-6000, 6000);

  while(1){
    setpoint = 0;
    for (int i = 0; i < 100; i++)
    {
      setpoint = setpoint + analogRead(A5);
      setpoint = setpoint/100;
    }
    // Simulating the Neural net response
    output = NeuralNet->predict(measured, setpoint);
    xddot = G*(output/a) - xdot*b - measured*c;
    xdot = xdot + xddot*ts;
    measured = measured + xdot*ts;
    Serial.print(setpoint);
    Serial.print(", ");
//    Serial.print(output);
//    Serial.print(", ");
    Serial.println(measured);
    delay(5);
  }
}

void loop(){}
