# Bonsai Workflow — Main Window Reference

## Parameters

| Parameter | Description |
|-----------|-------------|
| **Animal ID** | Unique identifier for the animal. Used to save data and load the animal's previous configuration. |
| **BufferCount** | Sets the time window (in seconds) for the lick histogram display. Must be set before starting Bonsai, based on the expected trial duration. |
| **Catch Trial** | `True` — some trials deliver the object short of whisker contact. `False` — all trials deliver the object to full whisker-contact distance. |
| **Catch Trial %** | Fraction of trials designated as catch trials (short-distance). Default: `0.1` (10%). |
| **Count Aluminum** | Window size (number of trials) for the running average of the aluminum foil hit rate graph. |
| **Count Non** | Window size (number of trials) for the running average of the no-object false alarm rate graph. |
| **Water Per Drop** | The calibrated water volume (µL) delivered per reward event. |
| **Water Reward** | Duration the solenoid valve stays open per reward (determines water volume delivered). |
| **White Noise** | Duration of white noise playback during no-object and catch trials. |

> **Loading a new animal:** Enter the animal ID and press **F10**.
> On first load for a brand-new animal, the workflow should create the animal folder and default `Settings.csv` automatically.
> To switch animals: stop Bonsai, change the ID, restart, and press **F10** again.
> If a new animal does not load correctly, verify that Bonsai has permission to create files in the data location and that no other Bonsai session is using the same animal folder.

---

## Key Bindings

| Key | Action |
|-----|--------|
| **F2** | Apply updated parameters (change settings) |
| **F4** | Send serial command to motor Teensy |
| **F10** | Load animal by ID |
| **F12** | Start / restart training session |
| **Shift+A** | Rotate object holder to aluminum foil position |
| **Shift+F** | Send linear motor to home (starting) position |
| **Shift+W** | Manually trigger water reward |

---

## Serial Commands (Motor Control)

Enter a command in the **Serial Command** field and press **F4** to send it to the motor Teensy.

| Command | Action |
|---------|--------|
| `l` | Rotate to aluminum foil position |
| `m` | Rotate to attenuated object position |
| `n` | Rotate to no-object position |
| `<int>` | Move linear motor by N mm (negative value = backward) |
| `r<int>` | Rotate stepper motor by N degrees |
| `c<int>` | Set catch trial distance: how many mm short of the whisker-contact position the motor stops. Default: `10` |
