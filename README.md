This is the first game engine i developed from Scratch hence the name Noob Engine :P. It's 2D data driven component based engine using C++/OpenGl. I developed 2d side platformer using this engine, both engine and game were developed over a course of 2 months. 
 
Some of the features of the engine are :

Component Factory : 
Creates components for game objects.
Serializing the game objects from json files.
Creates objects from the archetypes.

InputHandler:
An input handler for managing input events.
Keyboard and Mouse Event listener and dispatcher system.

2d Collision System : 
Impulse based 2d collision.
Has support for timed based collision also.

Graphics :
OpenGL based hardware accelerated graphics.
A basic Particle System.
Sprite Animation and sprite sheet support.

Message Handling and Event System:
Subscription based event handling.
Supports time based events as well.
Supports Message delegation.

Memory Management:
Creating Pools of game objects and components.
Implemented Linked List based structure for the first available resource for quick access.

Miscellaneous:
A logging and asserting utility.
A json parser for data driven development.
