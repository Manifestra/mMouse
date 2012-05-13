/*
PID LIBRARY
  ~Functions
  PID(&Input, &Output, &Setpoint, Kp, Ki, Kd, Direction)
    Creates a PID controller linked to the specific input, output, and setpoint
    &Input - the variable we're trying to countrol (double)
    &Output -The variable that will be adjusted by the pid (double)
    &Setpoint - The value we want to Input to maintain (double)
    Kp, Ki, Kd - Tuning Parameters. these affect how the pid will chage the output. (double>=0)  
    Direction - Either DIRECT or REVERSE. determines which direction the output will move 
      when faced with a given error. DIRECT is most common. 
  Compute()
    Contains the pid algorithm. it should be called once every loop(). Most of the time it 
      will just return without doing anything. At a frequency specified by SetSampleTime it will 
      calculate a new Output. 
    returns - none
  SetMode(mode)
     Specifies whether the PID should be on (Automatic) or off (Manual). The PID defaults to 
       the off position when created. 
     parameters: mode - AUTOMATIC or MANUAL
  SetOutputLimits(min, max)
     The PID controller is designed to vary its output within a given range. By default this 
       range is 0-255: the arduino PWM range. There's no use sending 300, 400, or 500 to the PWM. 
       Depending on the application though, a different range may be desired. 
     min - low end of the range. must be < max (double)
     max - high end of the range. must be > min (double)
   SetTunings(Kp, Ki, Kd)
     Tuning parameters (or "Tunings") dictate the dynamic behavior of the PID. Will it oscillate 
       or not? Will it be fast or slow? An initial set of Tunings is specified when the PID is 
       created. For most users this will be enough. There are times however, tunings need to be
       changed during run-time. At those times this function can be called. 
     Kp: Determines how aggressively the PID reacts to the current amount of error (Proportional) (double >=0)
     Ki: Determines how aggressively the PID reacts to error over time (Integral) (double>=0)
     Kd: Determines how aggressively the PID reacts to the change in error (Derivative) (double>=0) 
   SetSampleTime(SampleTime)
     Determines how often the PID algorithm evaluates. The default is 200mS. For robotics applications 
       this may need to be faster, but for the most part 200mS is plenty fast.
     SampleTime - How often, in milliseconds, the PID will be evaluated.
   SetControllerDirection(Direction)
     If my Input is above Setpoint, should the output be increased or decreased? Depending on what the 
       PID is connected to, either could be true. With a car, the output should be decreased to bring 
       the speed down (i.e. foot off the gas or less power. For a refrigerator, the opposite is true. 
       The output (cooling) needs to be increased to bring my temperature down.
       This function specifies which type of process the PID is connected to. This information is also 
       specified when the PID constructed. Since it's unlikely that the process will switch from direct 
       to reverse, it's equally unlikely that anyone will actually use this function. 
     Direction - DIRECT (like a car or motor) or REVERSE (like a refrigerator)

   PID basic example
   ********************************************************
   * PID Basic Example
   * Reading analog input 0 to control analog PWM output 3
   ********************************************************
    
    #include <PID_v1.h>
    
    //Define Variables we'll be connecting to
    double Setpoint, Input, Output;
    
    //Specify the links and initial tuning parameters
    PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);
    
    void setup()
    {
      //initialize the variables we're linked to
      Input = analogRead(0);
      Setpoint = 100;
    
      //turn the PID on
      myPID.SetMode(AUTOMATIC);
    }
    
    void loop()
    {
      Input = analogRead(0);
      myPID.Compute();
      analogWrite(3,Output);
    }   
     
*/
