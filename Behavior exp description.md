# Behavioral Experiment Description

## Bonsai (Real-Time Behavior Controller)

[Bonsai](https://bonsai-rx.org/) is a reactive programming environment used here as the master controller for the experiment. It handles trial timing, stimulus delivery commands, reward logic, and all data logging.

### Loading and Starting a Session

1. Enter the animal ID in the main window and press **F10** to load the animal.
   - If the animal is new, default settings are applied and a new folder is created automatically.
   - If the animal has been trained before, its previous settings are restored.
2. Press **F12** to start the training session with the current settings.

### Workgroups

#### Initialization Parameters
Controls all behavioral parameters for the session:

| Parameter | Description |
|-----------|-------------|
| `Difficulty` | Binomial probability controlling how often the rewarded stimulus is presented. `0.5` = fully random. |
| `Level` | Training level (0–3); see table below. |
| `Time Between` | Inter-trial interval in seconds. |
| `Time Out` | Punishment duration (seconds) after an incorrect response. |
| `Reward Time` | Duration the solenoid valve stays open; calibrated to µL. |
| `P2I` | Fraction of trials where reward is delivered regardless of whether the mouse licked (instructed trials). |

Default settings are loaded for each new animal. After changing parameters, press **F1** to apply them and **F12** to restart the session.

**Training levels:**

| Level | Behavior |
|-------|----------|
| 0 | Lick training — reward is delivered for any lick; `difficulty` controls whether reward is always given or only contingent on licking |
| 1 | Go/No-Go — `difficulty` controls the proportion of go/no-go trials; `P2I` controls the proportion of instructed vs. learned trials |
| 2 | Object detection — aluminum foil (go) vs. attenuated/silent object (no-go) |
| 3 | Test — full detection task with attenuated objects |

#### Files
Each animal has a unique ID. When loaded, Bonsai creates or updates a dedicated folder containing:
- An **events CSV** — timestamped log of every trial event (hits, misses, false alarms, correct rejections, water deliveries, licks)
- A **settings CSV** — updated each time a parameter changes; used to restore the last configuration on the next load

#### Inputs / Outputs
Real-time interface with all physical hardware:
- **Lick sensor** — capacitive touch sensor at the water port
- **Water valve** — solenoid for reward delivery
- **Camera** — behavioral video acquisition
- **Speaker** — white noise playback during catch/no-object conditions
- **Motors** — serial command interface to the Teensy motor controller

---

## Arduino / Teensy Hardware

Two **Teensy 4.0** microcontrollers form the hardware control layer:

1. **Teensy 1 (Firmata bridge)** — runs the Firmata protocol to communicate with Bonsai over serial. Receives high-level commands and relays them to Teensy 2.
2. **Teensy 2 (Motor controller)** — receives commands from Teensy 1 and directly drives both motors.

### Motor Control Modes

**Manual calibration** (used during setup before each session):
- Move the linear motor forward/backward to determine the correct whisker-contact distance
- Rotate the object holder to each object position and verify contact quality
- Set the safe whisker-contact distance and the catch trial offset (default: 10 mm short)

**Automated trial mode** (during experiments):
1. Rotate the stepper motor randomly clockwise and counterclockwise before settling on the target object — this prevents the mouse from predicting the stimulus identity from motor sounds
2. Randomly select between two physical positions of the same object
3. Retract the linear motor away from the whiskers
4. Send a feedback pulse when the motor reaches the retracted position
5. Advance the linear motor to the target distance
6. Send a second feedback pulse when the advance is complete
7. Emit identity pulses: `1` = aluminum foil, `2` = attenuated object, `3` = no object

Identity pulses synchronize the behavioral event log with the ultrasonic audio recording (Avisoft USGH), enabling offline alignment of neural and behavioral data.
