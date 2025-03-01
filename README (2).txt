### Project 2c Dragonfly Naiad
# Phuong Mai Do - pdo@wpi.edu
Feb 25 2025

## Platform: 
Windows - Microsoft

- Tested Platform: Visual Studio Code 2022 for Windows
- Programming Library: SFML 3.0

## How to compile (especially if non-standard)
1. Navigate to the project directory
2. Open the .sln file to a IDE such as Visual Studio Code 2022 
3. Build solution by navigate to the menu, select Build, and select Build solution from
the drop down. To quickly Build, press Ctrl + Shift + B
4. Press Ctrl + F5 OR Press F5 (Debug) OR Open the just built .exe file to RUN
5. A terminal will pop up and show the tests that run in real time. Wait for a few seconds so that the program finished, then open the dragonfly.log to see the logfile output, includes of other tests, and game notices. 

** Notes: For Linux and Mac, a makefile is needed to compile the game instead of the .sln

## To test with Dragonfly saucer-shoot master
1. Include the header and source files of Dragonfly saucer-shoot in the same solution as the engine.
OR
2. Create a library from this Dragonfly by:
    Set the type to a Static Library.  
    Under Properties -> General -> Configuration Type.  
    Then, you build Dragonfly game engine normally. 
    Link in your "game" (test code) such as Dragonfly saucer-shoot the same way as in project 1.

Notes: eventhough I know and have shown the steps of method 2, as Professor has told me how, I still cannot link the saucershoot game to my engine, which I think it is a system problem. So I decided, for the sake of time, to test the game using method 1.

## OLD: Dragonfly 2b Update additional capabilities
Output
    Support drawing 2d (ASCII) characters
    Clean refresh each game loop
    Support color
Input
    Accept non-blocking keyboard and mouse input
    Send as event to all game objects
Object Control
    Support "velocity" for game objects with automatic updates
Collisions
    Detect between any two solid game objects
        Provide "solid" attribute for game objects
    Send as event to both game objects
Misc
    Provide "altitude" attribute for game objects for layered drawing
    Send "out of bounds" event when game objects off screen

## NEW: Dragonfly 2c Update additional capabilities
-- Sprites
    Provide multi-character frame
    Provide for animation and animation “slowdown”
-- Audio
    Provide support for sound effects
    Provide support for music
-- Resource management
    Read and parse sprite data from file
    Provide Sprite access for Object
    Load sound effect from file
    Provide Sound access for Object
    Associate music with file
    Provide Music access for Object
-- Bounding boxes
    Provide for game objects larger than single character (for movement and collisions)
    Bounding box based on Sprite size
-- Camera control
    Game world larger than screen (viewport)
    View port movement around game world
-- View Objects
    Support for “heads-up display” objects that don’t interact with game world
    Objects have integer values that can be updated (delta or new value)
-- Object (base class)
    -- Associate Sprite with Object
    -- Draw frames in sequence to achieve animation
    -- Support “slowdown” of animation
## Code structure
Each includes a header file and a cpp file, except for game.cpp and game_saucer.cpp, which all have main()

Note: Features start with '-' means that they are updated 2b features from the old 2a version.

Note: Features start with '--' means that they are updated 2c features from the old 2b version.

Manager (base class)
    Startup and shutdown
    - Add support for sending events (onEvent)
LogManager (derived class from Manager)
    Singleton
    Startup and shutdown
    Flexible means of writing data (integers, strings, ...)
Clock
    Milliseconds of resolution for timing
Vector
    (x,y) location
Object (base class)
    Position, Type, ID, Add / remove self to game world
    - Getting/setting Solidness (hard, soft, or spectral)
    - Getting/setting Altitude
    - Getting/setting x-velocity, y-velocity

    -- Support Sprites
        -- Centered
        -- Animation rate (slowdown)
    -- Getting/setting bounding box
        -- Centered based on Sprite

ObjectList
    Store 1+ Objects
    Add/remove Object
    Index [] support
GameManger (derived class from Manager)
    Singleton
    Startup and shutdown
    - Modify game loop
        Input: Get input (InputManager)
        Draw: Have Objects draw themselves (WorldManager)
        Swap: Refresh screen (DisplayManager)
    Send step event to all Objects each loop
WorldManager (derived class)
    Singleton
    Store all game objects
    Add/remove game objects
    Provide list of all game objects
    Support deferred, batch removal of game objects (markForDelete)

    - Support boundary limits (equal to screen limits)
    - Detect collisions
    - Move Objects
        Modify update to support velocities
        If out of bounds, provide event
        If solid, provide collisions (detection and event generation)
    - Draw method, where all Objects draw themselves
        Support altitude, where lowest Objects drawn first

    -- Modify collision detection for box intersection
    -- Add camera (viewport) control
        -- Get/set view
        -- Translate world (x,y) to view (x,y)
    -- Modify to support adding/removing View Objects
    -- Modify update to support View Objects

Event (base class)
    Getting/setting type
EventStep (derived class)
    Getting/setting type

- DisplayManager
    Singleton
    Startup and shutdown
    Draw character at (x,y) with (and without) color
    Draw string at (x,y) with (and without) color, with justifications
    Detect and store horizontal and vertical screen boundaries
    SwapBuffers to refresh display to latest world image

- InputManager
    Singleton
    Startup and shutdown
    Support keyboard and mouse input

And more new classes derived from the base class Event:

- EventOut
    Getting/setting type
- EventCollision
    Getting/setting type
    Getting/setting both Objects in collision
    Getting/setting collision position
- EventMouse
    Getting/setting type
    Getting/setting mouse action (button)
    Getting/setting (x,y) location on screen
- EventKeyboard
    Getting/setting type
    Getting/setting key pressed
    Convert SFML keyboard to dragonfly keyboard

-- ResourceManager
    Singleton
    Startup and shutdown
    Load Sprites, Sounds and Music from files
    Find Sprites, Sounds and Music with given labels
-- Sprite
    Width, height
    Label
    Color
    Frame count and frame
-- Sound
    SFML sound
    SFML buffer
    Label
-- Music
    SFML music
    Label
-- Frame
    Width, height
    Data
-- Box
    Corner, position
-- ViewObject (derived from Object)
    Getting/setting location
    Getting/setting border, color and display string
    Getting/setting value
    Event handler to handle EventViews
-- EventView (derived from Event)
    Getting/setting tag
    Getting/setting value
    Getting/setting delta
# Plus:

game.cpp
    main()
        call GameManager
        run Test
        populate world - Hero, Saucer, Star
        run game of saucer shoot with Hero, Saucer, Bullet, Reticle, Star, etc.
        This is the game.cpp of the saucer shoot master.

Test
    run test functions to test other features than those in game loop, usually by creating a object of that class and test with every function and some possible scenarios within it. These tests includes tests of Manager, LogManager, Clock, Vector, Object, Object list. 

    Test update:
    (old) 6 more tests on new updated features such as DrawCharacter, DrawString, Display, Velocity, Altitude, Collision that returns true if past, false if not past
    New: 9 more tests on new updated features such as adding sounds, music, sprites, frames, box intersections, event view.

## The Loop
Each game loop or engine activity are mostly logged out using LogManager, mainly because of the sake of debugging and testing.
Checkout dragonfly.log to see real time reported game process.

1. In game.cpp main(), start GameManager. GM start the LogManager and the WorldManager, in that order. Right after this, the main() will run the Test.
2. Then, main() run populate(), which populate the world by loading resource (sprites, sounds, musics).
3.  Run the GameManager.run(), executes the game loop with controlled timing by create a Clock, so when game is not over, for each loop (step count):
    
    1. WM sending each Object a step event.
    WM.onEvent(&event_step); // Send to all Objects.  

	2. Create step event
    int step_count = event_step.getStepCount();

    3. Get Input
    InputManager::getInstance().getInput(); check for
        - Key pressed
        - Key released
        - Mouse move (use pixel to space)
        - Mouse pressed (use pixel to space)

    4. Update game world state
    WM.update();

        -  Iterate over all Objects in m_deletions list and delete each one.
        -  Clear m_deletions list.
        -  Iterate over all Objects in m_updates list and update each object's positions based on velocities.
        - move object moveObject(p_o, new_pos); 
            - moveObject(): - getCollision()/box intersection and Set new position.
                            - Check if object moved out of bounds
                            - Generate out of bounds event and send to object

    5. Draw current scene to back buffer based on the Altitude of the objects
    WM.draw();

    6. Swap back buffer to current buffer
    DM.swapBuffers();


5. Objects such as Hero, Saucer, Bullet, Reticle, Star, etc. handle the events in their eventHandler() methods and calls on other functions.

6. When the hero hit a saucer, the GameOver is displayed and the engine shut everything down by invoking GameManager shutDown(). This should shutdown the WorldManager, LogManager, DisplayManager, InputManager, etc. in that order.

## Credit
This project was made by following the instruction of chapter 1-7 of the Dragonfly Book https://dragonfly.wpi.edu/book/ .