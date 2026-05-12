# Protocol for Running a Training Session

## Local Configuration (first-time setup on a new machine)

Before running sessions on a new PC or rig, update the machine-specific settings inside the Bonsai workflow:

1. Open `Behivior_new.bonsai` in Bonsai.
2. In the **main window**, update the **Path** parameter to the local data directory where animal folders will be saved (default in the workflow: `E:\Ben\Omer training`).
3. If the Teensy boards are assigned different COM ports on this PC, update them inside the workflow:
   - **Teensy #1 (Firmata bridge)** — default `COM9`; appears in the Arduino/Firmata serial nodes.
   - **Teensy #2 (Motor controller)** — default `COM15`; appears in the serial-port nodes that send motor commands.
4. Save the workflow after updating these values.

> **Tip:** You can check which COM port each Teensy is assigned to by opening Device Manager (Windows) and expanding *Ports (COM & LPT)* while the boards are connected.

---

## Setup

1. Open `Behivior_new.bonsai` in Bonsai.
2. Enter the animal ID in the main window.
3. Set the **BufferCount** based on the expected trial duration.
4. Open **Avisoft USGH** and start acquisition.
5. Reset Teensy #2 using the physical button on the board.
6. Place the objects in the holder according to the positions defined in the Arduino code.
   - Periodically, and before each test session, randomize the physical positions of the objects relative to each other.
   - After changing positions, update the position constants in the Arduino code and re-flash Teensy #2.
7. Re-attach the running wheel (should be drying next to the sink).

## Animal Placement

8. Place the animal on the wheel and attach the headbar to the holder.
9. Verify that:
   - The animal can run freely on the wheel.
   - There is sufficient clearance for the object to reach the whiskers without touching the wheel.
   - There is space to position the lick port in front of the mouth.
10. Tighten the headbar screws so the animal is firmly and comfortably restrained.

## Stimulus Calibration

11. Start Bonsai and close the camera properties window that appears automatically.
12. Press **Shift+A** to rotate the object holder to the aluminum foil position.
13. Advance the linear motor in steps using **F4** (default: 5 mm per step) until the object is close to the whiskers.
14. While listening through headphones, fine-adjust the object height, angle, and distance (using **F4**) until whisker contact produces a clear audible sound.
15. Send the motor to the home position with **Shift+F**, then advance again to confirm the contact sound is reproducible.
16. Send the motor back with **Shift+F**, press **Shift+A** to advance to the second aluminum foil position, then press **Shift+F** again to confirm this position also produces a clear contact sound.

## Water Port Setup

17. Fill the syringe with sucrose water.
18. Press the solenoid manually until water flows from the lick port (use a tissue to collect it).
19. Position the lick port below the snout in front of the mouth.
20. Press **Shift+W** to release a small amount of water and confirm:
    - The animal drinks.
    - Individual licks are audible through the headphones.
    - The lick sensor is not continuously triggered (contacts should be brief and discrete).

## Camera and Environment

21. Turn off the setup light and position the camera to frame the whisker pad, the eye, and the objects.
22. In Bonsai's camera tab, adjust the crop region for a clean ROI.
23. Close the curtains.

## Loading and Verifying Settings

24. Send the motor to the home position with the **reset/back** command.
25. Load the animal with **F10**.
26. Open the settings node and verify the loaded parameters match the expected configuration.
27. Open the lick report node, press **Shift+W** to release water, and confirm licks are being recorded.
    - If licks are not recorded, restart Bonsai and reload the animal.
28. Close the lick report node.

## Starting the Session

29. Turn off the room lights.
30. Press **F12** to start the session.
31. Monitor the first few trials to confirm:
    - Trials are advancing at the expected rate.
    - The BufferCount is appropriate.
    - The protocol is not getting stuck.
32. Close the monitor, draw the entrance curtain, and leave the room.
33. Continue monitoring remotely via Remote Desktop.

---

## After a Training Session

**After each animal:**
1. Release the animal and return it to its home cage.
2. Provide the animal with its required daily water supplement.
3. If training another animal: clean the wheel.
4. If testing another animal: clean the objects as well.

**After the last session of the day:**
1. Detach the wheel and rinse with soap and warm water.
2. Empty the syringe; flush the water line with soapy water followed by double-distilled water (×2).
3. Clean feces from the setup.
