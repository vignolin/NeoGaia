# NeoGaia
NeoGaia is an open-source project focused on automating plant care and creating affordable, eco-friendly bricks and plant pots made from sugarcane. Our goal is to make sustainable living more accessible and efficient through innovative solutions.

# NeoGaia Smart-Pots 
NeoGaia develops different plant-pot models, each of them with different shapes and functionalities.
From now on, this document talks about general functionalities that can be present in the multiple pots.

## General Specs
Micro-controllers: depending on the type of pot, different microcontrollers shall be used. The main microcontroller that is going to be used is the ESP-32, since it
has internet access allowing a communication with the user. The Arduino Uno Rev3 is also a major option, although it might limit the control of the user of the plant.
The Micro Controllers picked for the pots must have deep sleep capabilities, if you aren't into charging your plant once a week.

Features:  
 - #### Capacitive Moisture Sensors:
the Smart-Pots use either capacitive moisture sensors or regular ones, depending on which pot. Both of them have their durabilty extended by our periodical use of it.
 - #### Temperature Sensors: 
little to none pots feature this sensors, however big ones need a way of controlling temperature of the plants. When a high temperature is sensored, the pot activates its irrigation system to decrease it.
 - #### Water Pumps
Water Pump: different Smart-Pots, obviously, feature different sized water pumps, however their differences are minuscule and, in most cases, there are only a few software changes.  The prismatic design uses, picture below, a 2-6V 100-120L/h with 2,5cm of diameter water pump.

![image][imagem bomba]


[imagem bomba]: https://github.com/user-attachments/assets/d9cf12df-7039-481f-99fc-f1103f39b274
