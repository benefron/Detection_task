Workflow main window

Parameters at main window:
    - Animal ID: The unique ID given to the animal to be able to save the data and load the configurations
    - BufferCount: Determines the buffer (in sec) for the histogram window of licks. The buffer needs to be set based on the configuration, prior to starting the Bonsai software.
    - Catch Trial: True - trials with the motor reaching short of the whiksers. False - all trials the motor reach the whiskers
    - Catch trial %: detrmines the fraction of trials that will have "Catch" distance, defult is 0.1
    - Count Aluminum: The running average window for the aluminum hit rate graph
    - Count Non: The running average window for the non FA rate graph
    - load Animal: just a reminder that to load an animal to run the training you need to press F10. 
        * To change animals you need to stop the Bonsai, change the name, restart and load the animal. 
        * To start a new animal that was never trained before, you need to try once and load it, this will return an error and crash the software, rerun it and reload the animal and it will work fine.

    - Serial command: This allows you to send commands to the teensy controling the motors, this can be a text or a number. To send the command you press F4. This can receive the following:
        * l - rotate to aluminum position
        * m - rotate to the attenuated position
        * n - rotate to the no object position
        * int - moves the linear motor by the number in mm, can also recieve negative to move backwards
        * r+int - rotates the object motor by the degrees given
        & c + int - determines the catch trial position relative to the save whisker position. Default: 10mm
    - start session: the key you need to press to start teh session F2
    - Water per drop: The calibrated amount of water 
    - Water reward: the time the selonid valve is open (determines the amount of water)
    - White
        