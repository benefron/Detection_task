Description of Bonsai software for behavior:
Bonsai:
	Main window (Workflow):
		Need to load an animal by the animal ID and than pressing F10, if it is a new animal, the software starts with defult settings
		and creates a new folder for the animal with event csv, and a csv with one line that saves the last configuration of the animal
		training.
		
		Pressing F12 starts the training session based on the settings uploaded
		
		WorkGroups:
			Initialization parameters:
				Settings for the training:
				- Difficulty: Sets how random the presentation of the rewarded stimuli is presented,
							  this is binomal distribution 0.5 is random
				- Level: Sets the level of training 0 - just lick 1 - motor movement 2 - Object presentation 3 - test with attaunated object
						0 - Give reward for licking the water spout. difficulty determines if a reward is given always or 
							just if the mouse licked
						1 - Introduces motor movement as trail initiation. difficulty same as for level 0.
						2 - Main training, can control presentation of the rewarded object 0-0.5 unrewarded object
							0.5-1 unrewarded object
						3 - Testing, give three options: noisy, attanuated, no object
				- Time between: The time of each trail in sec 
				- Time out: Time that the animal is punished by no further trails after failing
				- Reward time: The time of the lick port gioving reward (will be in uL after calibration
				
				Defult will be loaded for each new mouse
				When changing parameters you need to press F1 to load them and F12 to restart the training.
			
			Files: Inside are the nodes to create or update a file. Each animal gets a unique ID and that ID creats a folder 
				   that will be uploaded with last settings and updated for the animal. this will create a csv file,
				   containing every event that happens, time of event and the settings.
				   Two files are created one containg the events and times and one that updates every time a setting is changed
				   and allows for the last settings to be uploaded.
			Inputs Outputs: 
				The inputs and outputs of the system:
				 - Lick sensor
				 - Water valve
				 - Camera
				 - Speaker (for white noise)
				 - Motors
			
Arduino:
	Two Teensy 4.0 one running firmata to communicate with Bonsai. The second recriving input from the first and
	controlling the motors based on the inputs. 
	
		
				   
				
		
		