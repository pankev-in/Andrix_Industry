## Concept

Nowadays computers under ARM architecture are getting common. Variate smartphones, sigle-board computers like Raspberry Pi are getting cheaper and much more affordable. To be able to use ARM Devices as robot controllers, some additional hardware that enables connecting and controlling robot components such as sensors, motors and servos are required. The hardware (aka. Low-Level Control, LLC) and the ARM devices(aka. High-Level Control, HLC) should be able to be connected together using both wired and wireless communications. The following figure illustrates the concept:

![](/Volumes/DATA/Programming/Github/Andriox_Industry/Documentation/img/Andrix_concept_v3.png)

AndriX Industry is the concept of implementing this kind of structure in a industrial environment and its controller has to be low-cost(relatively), stable and expansional for different uses.

In this project, we are using a standard industrial conveying belt to test our idea. We will connect  our Andrix controller (including an Raspberry Pi as the High level control) to a external Motor Controller (aka. External Hardware Controller level) to be able to drive the conveying belt using a Stepper Motor.

NEMA Stepper motor series is one of the most popular Motors in both pre-industrial and professional fields. It is amazingly  accurate and powerful, but at the same time very easy to control.

## Processes

To be able to achive the goal, we planned the project precisely and here is a quick overall view of our working processes:

1. Choosing matching hardware
2. Designing other mechanical parts we need
3. Producing mechanic parts by using CNC or 3D-printer
4. Calculate needed supply power 
5. Design external motor controller
6. Prototyping electronic design
7. Communication protocol
8. Software programming
9. Debug, test and other finalisation process

There are some different conditions have to be satisfied to achieve our concept. At first, we need to find a industrial conveying belt, which has to be samll enough to let us drive it easily with one stepper-motor without having too many problems. There are mainly two kind of conveying belt on the market today - limited and unlimited countineus conveying Systems. 

Unlimited countineus conveying systems are the most common version and have been applicated in various areas like raw meterial supplyment or warehaus transportation systems. They don’t need any sesors to detect current position and can be controlled easily by changing the speed of the rotations. Limited conveying belts works in principle familiar to countineus system, but the position of the belt is controlled precisely using servo motor and has integrated sensors working with hall effect(magnet) or IR encoders(light), but both of them need extra circuit to drive them and need externel programm to decode the position.

This is also one of the reason why we use stepper motor. NEMA stepper motors are in compare to other motors much more flexible to control. It can be controlled pretty easily with two H-Bridge Motor controller or FET-Transistors. We can dettect the position just by counting the steps in the register from the microcontroller. Of course it also has disadvantage - speed. The accurency and the speed of the motor are proportional to each other and in our case, we can lose our accurency by changing the step resolution, which isn’t a mechanical problem that can be simply avoided.

An agreement for the communication protocol between the andrix and the external motor controller has to be made too. We are using 9600 bit/s as our communication speed. It is a standard bandwitdh and can be even controlled with other computers. The electronic controllers has to be choosed carefully. We have to calculate and test the maximum supply current the motor needed to run stabely and compare it with the datasheet from the manufacture.

## Mechanic
### Overview:IEF profiLine 140
### Conveying belt
### Motor
### Shaft Adapter


## Conclutions
































aasdfas