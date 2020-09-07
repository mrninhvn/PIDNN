#include <Arduino.h>
#include <math.h>

#define WINDOW_SIZE 30
#define DZ_TOL 1e-20


class PIDNN
{
  public:

    // User functions
    void setStartWeight(float wP, float wI, float wD);
    void setOutputLimit(float outMin, float outMax);

    // To avoid division by zero
    float DivByZero( float value);

    // Neuron Acitvation Functions
    float ptransfer( float value );
    float itransfer( float value, float accum, float ts );
    float dtransfer( float cur_value, float past_value, float ts );
    
    float predict( float measured, float expected ); // Forward Propagation

    void BackProp( float dr, float dy, float d_ow[3], float d_hw[2][3], int i ); // Back Propagation
    
    void learn( void ); // PIDNN Learn and Update

    PIDNN( float l_rate, float weight_change, float tolerance, float timestep ); // Constructor
 
  private:

    // Neural Net Parameters that can be tuned
    float n; // Learning Rate
    float max_change; // Maximum change in weight
    float tol; // Error Tolerance
    float ts; // Time Step
    float d_tol; // Maximum Tolerance for weight change

  protected:
    int pos = 0;
    float OUT_MIN = -255;
    float OUT_MAX = 255;

};
