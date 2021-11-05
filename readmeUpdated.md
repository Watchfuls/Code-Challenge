# Virtex Code Challenge

## Getting Started

### Dependencies

* Make sure that you are using Unreal 4.26.2 or above
* It's a more a code test so be sure that you have VisualStudio, Rider or NotePad++

### Getting project

Create a Fork of this project with your github account. If you don't have one or you want to just clone the project it's also fine, just remember to put it on WeTransfer or your GDrive afterwards. After finishing it, please share it with [Tomek](mailto:tomasz@virtexstadium.com)

## The Problem

We have a simple multiplayer project. At the moment movement does not work properly (offline and online), not everything is replicated from Pawn, I don't know why our PrintString in pawn blueprint does not work - help us find why.

## The Solution

##### <u>Movement:</u>

The issue with the movement is that while the function to set the variable "MoveCharacter" was set on the server, it was not replicated out to the clients, meaning all clients wouldn't have received the value of "MoveCharacter" and only the server would know it's location.

From here there is also no functionality to move the character. I wasn't sure if the intended application for the movement was, if it was to affect the velocity or the position, so I went with the simpler method of simply affecting the position for now.

If we take a look at the overall networking the pawn is an Autonomous proxy. This means for the best feel to a multiplayer game, the player should move on their own, then their positional data should be sent up to the server before being replicated to other clients.

On top of this the bindings of the Input Settings in the engine were not set up correctly, and so only the W and A key were bound.

![image-20211105102255826](C:\Users\gregh\AppData\Roaming\Typora\typora-user-images\image-20211105102255826.png)



##### <u>Not Everything is Replicated:</u>

There's 2 main options for networking. Either we can simply send the inputs as the original program seems to function, though this is much more likely in my opinions to cause inconsistencies with the position of the pawn, as if the input information is lost a permanent dislocation of the pawn would happen. By transferring the data of the position this inconsistency can still happen but is able to be rectified.

Here more data is replicated as a full vector is replicated instead of just a int32. Depending on the number of clients and platform constraints there may be limits to this, and so it's not the perfect solution, though information passed from a vector can be optimised.

I have also changed it so the information of the movement direction is only local, as for the purposes of movement it's not needed if we are sending the information of the position.

From here the pawn is replicated to the other clients from the server.

##### <u>PrintString issue:</u>

This wasn't functioning because there was no "Super" for the tick function. The super denoted when the parent functionality inherited by the function should be ran, which is the location in which the blueprint function is called. As this was missing there were no called to the blueprint Tick function.

For now I have disconnected this log in the blueprint to stop the log spamming both the console and the debug screen. Due to a rearranging of code this will also no longer function on the server. This could be quickly changed if needed though.

## The Goal

The goal of this test is not to create the bestest multiplayer experience ever. Experience has to work in a multiplayer environment - that's all.
We really want to see your way of thinking and approaching the problem. There is no good or bad way to do it - there are many solutions for this challenge.

In project you will find:
* VTPawn C++ class
* VP_VTPawn Blueprint which parent class is VTPawn
* TestMap - this is a map where magic should happen
* Defined Inputs

## Requirements

Finished project has to run properly in Client mode with 2+ players in Editor. That's all.

## Bonuses

* If you can find a fun way to diversify projects, go for it! New class? New BP? New mechanics? TPP? Go for it!
* If your code is self explanatory, comments are not required.
* C++11 is welcome, however not required.

## Useful links

* [Coding Standard](https://docs.unrealengine.com/4.26/en-US/ProductionPipelines/DevelopmentSetup/CodingStandard/)
* [Networking and Multiplayer](https://docs.unrealengine.com/4.26/en-US/InteractiveExperiences/Networking/)
* [UE4 Network Compendium](https://cedric-neukirchen.net/Downloads/Compendium/UE4_Network_Compendium_by_Cedric_eXi_Neukirchen.pdf) <- I love this, I've always used it when it comes to networking.
* [Actor Lifecycle](https://docs.unrealengine.com/4.26/en-US/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Actors/ActorLifecycle/)
* [the_coding_love](https://thecodinglove.com/)
* [Multiplayer in Blueprints](https://docs.unrealengine.com/4.27/en-US/InteractiveExperiences/Networking/Blueprints/) I know the networking and multiplayer is included above, but I thought this page was particularly relevant to this test.
