
<h2> E-Waste Servo </h2>
<h2>
<a href = "https://www.youtube.com/watch?v=bNenPddOqr0&ab_channel=JonahMack"> Video Example With a quick test setup </a>
</h2>
<h2>
<a href = "https://github.com/Jmack66/EWaste-Servo/blob/main/ingredients.md"> Materials </a>
</h2>
<h2>
<a href ="https://github.com/jmack66/ewaste-servo/blob/main/assembly.md"> How to Assemble </a>
</h2>

<h3> Code Documentation </h3>

Note: Because the DRV8871 was used the code is based around that driver's functionality. It is likely that any Bi-Directional driver would work with the library but it may take modification. 

The Servo can be created in arduino like other arduino Servo Libraries.

`EWServo myServo = EWServo(DrivePin1, DrivePin2, Feedback);` 

The only functions that are needed to start are:
`servo.setPIDGains(Kp, Ki, Kd);` 
`servo.autoCalibrate();`


the PIDGains are important for getting the servo to respond in a desired closed loop manner. See the attached PDF for information on the tuning processed used.

The code has several test functions to easily retrive data all denoted by the "test" prefix

`int* testAnalogExtremes(int drive)` returns an array, the first of which being the maximum potentiometer value found, and the second being the minimum. Once these have been found the output can be hard coded with `setAnalogLims(int min, int max);`

Because of friction there exists a minimum drive signal to get the servo to move reliably `int testMinDriveSignal();` automatically determines and returns this signal this and the max signal can be set manually with `setDriveLims(int min, int max);` These also serve as the saturation or limits for the PID controller. 

autoCalibrate runs testMinDriveSignal and testAnalogExtremes

`testSpeed(int drive);` 
will time the servo response from a starting position to the minimum analog position of the potentiometer. 

`setTolerance(int tol);`
sets the position tolerance (on the potentiometer scale) for a commanded position

Just like a normal servo it can be commanded to a position in degrees with `write(int pos); ` this function returns a bool - because the loop is closed by the arduino itself the code itself needs to loop until it reaches the position, as opposed to a traditional servo which has its own internal loop. This is an improvement I would love to see made to the servo

to get traditional servo response `while(!myServo.write(pos)){}` should be used to allow the servo to loop. write returns true when the servo pos is within the tolerance of the commanded position.