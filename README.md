# IMG420-Assignment2
This project extends on the Sweet-09 Godot maze game (maze with a player, lava obstacles, and lollipop collecting) by incorporating new functionalities through GDExtension in C++.

## New Node: "CandySprite"
- CandySprite is a custom class that extends Sprite2D.
- The new custom Sprite2D (CandySprite) gives the lollipops additional interaction and animated behavior.

### Features
1. Bobbing Feature
   - The sprite moves up and down using a sine-wave motion.
   - Adjustable properties include:
       - "enable_bob": Toggle the effect of bobbing on/off
       - "height": Adjust the height of up/down motion
       - "bob_speed": Adjust the speed of up/down motion
    
2. Spinning Feature
   - The sprite rotates continuously around its center
   - Ajustable properties include:
       - "enable_spin": Toggle the effect of spinning on/off
       - "spin_speed_deg": Adjust the rotation speed

### Signal
  - "bob_cycle": Produce each complete bobbing cycle (connected in "candy.gd")

### Method
  - "apply_boost": Speeds up the bobbing/spinning for a limited time (called when candy is collected)
