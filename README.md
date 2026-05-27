<a name="readme-top"></a>

<!-- GENERAL GAME INFO -->
<br />
<div align="center">

  <h2 align="center">Cave Story+</h2>

  <p align="center">
Cave Story+ is an enhanced commercial version of the original CaveStory.
Cave Story is a 2004 Metroidvania game. It was developed over five years by Japanese independent developer Daisuke "Pixel" Amaya in his free time. It blends tight shooting mechanics, nonlinear exploration, and multiple endings in a retro pixel-art world inspired by classic 8- and 16-bit games.
    <br />
    <strong>Original game : </strong>
    <a href="https://en.wikipedia.org/wiki/Cave_Story#Cave_Story+"><strong>General info »</strong></a>
    ·
    <a href="https://youtu.be/el2GUSEyMGU"><strong>Youtube video »<strong></a>
    <br />
    <br />
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#my-version">My version</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
    </li>
    <li><a href="#how-to-play">How To Play</a></li>
    <li><a href="#class-structure">Class structure</a></li>
    <li><a href="#checklist">Checklist</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

![alt text](image.png)
Here's why:
* It is a remaster of a classic indie game with a passionate fanbase I somehow haven't gotten around to play earlier.
* The game high variety of worlds with lively and rich characters.
* Focused and strong core gameplay loop.
* I think it serves great for learning how to program platformers.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## My version

This section gives a clear and detailed overview of which parts of the original game I planned to make.

### The minimum I will most certainly develop:
- [x] Overlay  first cave level as a texture and lay-out collision shapes.
- [x] Player with horizontal movement, jumping, and basic air control
- [x] Collision detection between player
- [x] Camera that follows player within level bounds
- [x] Rendering the player sprite and animation states (idle, run, jump)
- [X] Basic enemy entity with position and simple movement pattern
- [X] Player projectile system (spawn bullet, movement, lifetime)
- [X] Collision detection between bullets and enemies
- [X] Enemy damage, hit feedback, and removal on defeat
- [X] Player damage on enemy contact
- [X] Basic HUD showing player health
- [X] Beginning of Mimiga Village area layout
- [X] Trigger zone that stops player and opens dialog
- [X] Dialog box UI with text rendering
- [X] Input handling to advance dialog text
- [X] Camera lock during dialog events

### What I will probably make as well:
- [ ] Save station entity placed in first level
- [ ] Interaction key to activate save station
- [ ] Save system storing player position and health
- [X] Boss entity with larger sprite
- [X] Boss attack patterns (movement phases)
- [X] Boss health display
- [x] Boss defeat event triggering dialog or transition
- [X] Transition between cave level and Mimiga Village
- [X] NPC entity system for characters in village
- [X] NPC interaction trigger and dialog events

### What I plan to create if I have enough time left:
- [ ] Smaller details like particles
- [ ] Full Mimiga Village map layout
- [x] Multiple NPCs with multiple dialog lines

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started
Detailed instructions on how to run your game project are in this section.

### Prerequisites

* Visual Studio 2022

### How to run the project

The game project is called CaveStoryPlus.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- HOW TO PLAY -->
## How to play

Use this space to show useful examples of how a game can be played. 
Additional screenshots and demos work well in this space. 

### Controls

* Left and Right arrow keys to move around.
* Down arrow to interact with NPC, objects and going through doors.
* Z key to Jump.
* X key to shoot and read through dialog.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CLASS STRUCTURE -->
## Class structure 

### Object composition 
**Player** object contains pointer to child class object of **Weapon**. 
The **Player** class also has a field of a **DialogManager** and **PlayerGUI**.

An object of **Level** class contains pointers to different Texture sheets.
It also contains a **BulletManager** among various **std::vector**s of objects in the game.

A **BossEnemy** object holds a **BarWidget** as a field or component.

### Inheritance 
All interactable things in the game inherit from the base abstract class **Interactable**:
for example **DoorInteractable**, **GoldInteractable** and **ChestInteractable**.

There is also a **DecorInteractable** class that provides shared code for its children classes (NPCs).

### ..

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CHECKLIST -->
## Checklist

- [x] Accept / set up github project
- [x] week 01 topics applied
    - [x] const keyword applied proactively (variables, functions,..)
    - [x] static keyword applied proactively (class variables, static functions,..)
    - [x] object composition (optional)
- [x] week 02 topics applied
    - [x] Use of transformations: *BossEnemy, Bullet, Camera, PolarStar*
    - [x] Use of Manager classes: *BulletManager, TextManager, DialogManager, ...* 
- [x] week 03 topics applied
    - [X] Apply OO principles: Data members, Accessors, Mutators, Behavior
    - [X] Seperate .h from implementation .cpp
    - [X] Classes with constructors to prevent invariant states.
- [X] week 04 topics applied
    - [X] Use of class forwarding in headers when possible over including headers. Prevent cylic dependencies with forward declaration.
    - [X] object composition
    - [X] Implementation of platforms. Collision between player and platforms.
- [x] week 05 topics applied
    - [x] Single responsibility principle
    - [x] Class relationships: composition, aggregation, association, inheritance
    - [x] Delegating constructors to avoid duplicate code (see **Interactable** .cpp file)
    - [X] Use of inheritance (see Class structure above)
- [ ] week 06 topics applied
    - [x] Polymorphism
    - [x] C++ style casting (used static_cast)
    - [X] Use of (pure) virtual (see **Interactable** class)
    - [x] Camera (object space, world space, camera space)
    - [ ] Sound
    - [x] Music
- [x] week 07 topics applied
    - [x] friend keyword (see **Level** class)
    - [x] operator overloading (see **Level** class)
    - [x] use explicit keyword for constructors
- [x] week 08 topics applied
    - [x] Copy semantics, Rule of 3
- [ ] week 09 topics applied (optional)
- [ ] week 10 topics applied (optional)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Your Name - bram.deraeve@student.howest.be

Project Link: [https://github.com/HowestDAE/gd25-bramderaeve](https://github.com/HowestDAE/gd25-bramderaeve)

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Use this space to list resources you find helpful and would like to give credit to. 

* [Cave Story Wiki: Textures of the entire levels](https://cavestory.fandom.com/wiki/Mimiga_Village)
* ["My favourite animation trick: exponential smoothing"](https://lisyarus.github.io/blog/posts/exponential-smoothing.html)
* [Cave Story Font as TrueType font](https://fontlibrary.org/en/font/cave-story)
* All other game assets are ripped from CaveStory+ and CaveStory.
* * ..

<p align="right">(<a href="#readme-top">back to top</a>)</p>

