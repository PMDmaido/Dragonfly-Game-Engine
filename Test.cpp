// Test.cpp
#include "Test.h"
//#include "TestObject.h"


void Test::runTest() {
    // Check-point 1
    testManager();
    testLogManager();
    // Check-point 2
    TestSystemTime();
    testClock();
    // Check-point 3
    testVector();
    testObject();
    testObjectList();

    int tests_passed = 0;
    int tests_failed = 0;

    if (testDM_DrawCharacter()) tests_passed++; else tests_failed++;
    if (testDM_DrawString()) tests_passed++; else tests_failed++;
    if (testWM_Collision()) tests_passed++; else tests_failed++;
    if (testObject_Solidness()) tests_passed++; else tests_failed++;
    if (testObject_Altitude()) tests_passed++; else tests_failed++;
    if (testObject_Velocity()) tests_passed++; else tests_failed++;

    if (testSoundAttributes()) tests_passed++; else tests_failed++;
    if (testMusicAttributes()) tests_passed++; else tests_failed++;
    if (testFrameAttributes()) tests_passed++; else tests_failed++;
    if (testBoxAttributes()) tests_passed++; else tests_failed++;
    if (testViewObjectAttributes()) tests_passed++; else tests_failed++;
    if (testEventViewAttributes()) tests_passed++; else tests_failed++;
    if (testBoxIntersections()) tests_passed++; else tests_failed++;
    if (testBoxNonIntersection()) tests_passed++; else tests_failed++;
    if (testEventViewData()) tests_passed++; else tests_failed++;

    LM.writeLog("Tests passed: %d, Tests failed: %d\n", tests_passed, tests_failed);


}
bool Test::testBoxIntersections() {
    df::Box box1(df::Vector(0, 0), 5, 5);
    df::Box box2(df::Vector(2, 2), 5, 5); // Intersecting

    bool success = df::boxIntersectsBox(box1, box2);

    LM.writeLog("%s %s.", __func__, success ? "passed" : "failed\n");
    return success;
}

bool Test::testBoxNonIntersection() {
    df::Box box1(df::Vector(0, 0), 5, 5);
    df::Box box2(df::Vector(10, 10), 5, 5); // Not intersecting

    bool success = !df::boxIntersectsBox(box1, box2);

    LM.writeLog("%s %s.", __func__, success ? "passed" : "failed\n");
    return success;
}

bool Test::testEventViewData() {
    df::EventView ev("score", 100, true);

    bool success = (ev.getTag() == "score") &&
        (ev.getValue() == 100) &&
        (ev.getDelta() == true);

    LM.writeLog("%s %s.", __func__, success ? "passed" : "failed\n");
    return success;
}

bool Test::testSoundAttributes() {
    df::Sound sound;
    sound.setLabel("fire");

    bool success = sound.getLabel() == "fire";
    LM.writeLog("%s %s.", __func__, success ? "passed" : "failed\n");
    return success;
}

bool Test::testMusicAttributes() {
    df::Music music;
    music.setLabel("theme");

    bool success = music.getLabel() == "theme";
    LM.writeLog("%s %s.", __func__, success ? "passed" : "failed\n");
    return success;
}

bool Test::testFrameAttributes() {
    df::Frame frame(10, 10, "**********\n*        *\n*  **    *\n*  **    *\n**********");

    bool success = frame.getWidth() == 10 && frame.getHeight() == 10;
    LM.writeLog("%s %s.", __func__, success ? "passed" : "failed\n");
    return success;
}

bool Test::testBoxAttributes() {
    df::Box box(df::Vector(5, 5), 10, 10);
    bool success = box.getCorner().getX() == 5 && box.getCorner().getY() == 5;
    LM.writeLog("%s %s.", __func__, success ? "passed" : "failed\n");
    return success;
}


bool Test::testViewObjectAttributes() {
    df::ViewObject viewObj;
    viewObj.setViewString("Score");
    viewObj.setValue(10);
    viewObj.setLocation(df::TOP_CENTER);

    bool success = viewObj.getViewString() == "Score" &&
        viewObj.getValue() == 10 &&
        viewObj.getLocation() == df::TOP_CENTER;
    LM.writeLog("%s %s.", __func__, success ? "passed" : "failed\n");
    return success;
}

bool Test::testEventViewAttributes() {
    df::EventView eventView("Score", 5, true);

    bool success = eventView.getTag() == "Score" &&
        eventView.getValue() == 5 &&
        eventView.getDelta() == true;
    LM.writeLog("%s %s.", __func__, success ? "passed" : "failed\n");
    return success;
}

bool Test::testDM_DrawCharacter() {
    if (DM.startUp() != 0) return false;
    bool success = DM.drawCh(df::Vector(10, 5), 'A', df::RED) == 0;
    LM.writeLog("%s %s.", __func__, success ? "passed" : "failed\n");
    return success;
}

bool Test::testDM_DrawString() {
    if (DM.startUp() != 0) return false;
    bool success = DM.drawString(df::Vector(5, 5), "Hello", df::CENTER_JUSTIFIED, df::GREEN) == 0;
    LM.writeLog("%s %s.", __func__, success ? "passed" : "failed\n");
    return success;
}


bool Test::testWM_Collision() {
    df::Object obj1, obj2;
    obj1.setPosition(df::Vector(10, 10));
    obj2.setPosition(df::Vector(10, 10)); // Same position should trigger a collision.

    df::EventCollision collision(&obj1, &obj2, obj1.getPosition());

    if (collision.getObject1() != &obj1 || collision.getObject2() != &obj2) {
        LM.writeLog("Error: Collision event incorrect.");
        return false;
    }
    LM.writeLog("%s passed.\n", __func__);
    return true;
}

bool Test::testObject_Solidness() {
    df::Object obj;
    obj.setSolidness(df::SPECTRAL);

    if (obj.getSolidness() != df::SPECTRAL) {
        LM.writeLog("Error: Object solidness incorrect.");
        return false;
    }
    LM.writeLog("%s passed.\n", __func__);
    return true;
}

bool Test::testObject_Altitude() {
    df::Object obj;
    obj.setAltitude(1);

    if (obj.getAltitude() != 1) {
        LM.writeLog("Error: Object altitude incorrect.");
        return false;
    }
    LM.writeLog("%s passed.\n", __func__);
    return true;
}

bool Test::testObject_Velocity() {
    df::Object obj;
    obj.setVelocity(df::Vector(2, -3));

    if (obj.getVelocity().getX() != 2 || obj.getVelocity().getY() != -3) {
        LM.writeLog("Error: Object velocity incorrect.");
        return false;
    }
    LM.writeLog("%s passed.\n", __func__);
    return true;
}


// Test base Manager 
void Test::testManager() {
    std::cout << "\nTesting Manager base class..." << std::endl;

    df::Manager manager;

    // Test initial state
    assert(!manager.isStarted() && "Manager should start in not-started state");
    assert(manager.getType() == "Manager" && "Default type should be 'Manager'");
    std::cout << "Manager:: Initial state verified" << std::endl;

    // Test startup
    assert(manager.startUp() == 0 && "StartUp should return 0 on success");
    assert(manager.isStarted() && "Manager should be started after startUp");
    std::cout << "Manager::startUp(): verified" << std::endl;

    // Test shutdown
    manager.shutDown();
    assert(!manager.isStarted() && "Manager should not be started after shutDown");
    std::cout << "Manager::shutDown(): verified" << std::endl;
}

// Test LogManager 
void Test::testLogManager() {
    std::cout << "\nTesting LogManager..." << std::endl;

    // The GameManager should start the LogManager 

    // Test singleton pattern
    df::LogManager& lm1 = df::LogManager::getInstance();
    df::LogManager& lm2 = df::LogManager::getInstance();
    assert(&lm1 == &lm2 && "getInstance should return same instance");
    std::cout << "LogManager:: Singleton verified" << std::endl;

    ///// Test writeLog
    // Test writing with no arguments
    if (LM.writeLog("TEST: Hello World!\n") < 0) {
        std::cerr << "Error: writeLog Hello World! failed!" << std::endl;
        return;
    }
    // Test writing with integer
    int testNum = 42;
    if (LM.writeLog("TEST: number: %d\n", testNum) < 0) {
        std::cerr << "Error: writeLog Test number failed!" << std::endl;
        return;
    }
    // Test writing with float
    float testFloat = 3.14f;
    if (LM.writeLog("TEST: float: %.2f\n", testFloat) < 0) {
        std::cerr << "Error: writeLog Test number failed!" << std::endl;
        return;
    }
    // Test writing with string
    std::string testStr = "test string";
    if (LM.writeLog("TEST: string: %s\n", testStr.c_str()) < 0) {
        std::cerr << "Error: writeLog Test number failed!" << std::endl;
        return;
    }
    // Test writing multiple arguments
    if (LM.writeLog("TEST: Multiple args: %d, %.2f, %s\n", testNum, testFloat, testStr.c_str()) < 0) {
        std::cerr << "Error: writeLog Test number failed!" << std::endl;
        return;
    }
    std::cout << "LogManager::writeLog(): verified" << std::endl;

}

void Test::TestSystemTime() {
    std::cout << "\nTesting System Time..." << std::endl;

    // Get initial time
    SYSTEMTIME st1;
    GetSystemTime(&st1);

    // Calculate initial microseconds
    long long initial_time = (static_cast<long long>(st1.wDay) * 24LL * 60LL * 60LL * 1000000LL)
        + (static_cast<long long>(st1.wHour) * 60LL * 60LL * 1000000LL)
        + (static_cast<long long>(st1.wMinute) * 60LL * 1000000LL)
        + (static_cast<long long>(st1.wSecond) * 1000000LL)
        + (static_cast<long long>(st1.wMilliseconds) * 1000LL);

    // Print initial time components
    std::cout << "Initial time components - Day: " << st1.wDay << ", Hour: " << st1.wHour
        << ", Minute: " << st1.wMinute << ", Second: " << st1.wSecond
        << ", Milliseconds: " << st1.wMilliseconds
        << ", Total microseconds: " << initial_time << std::endl;

    // Sleep for exactly 1 second
    Sleep(1000);

    // Get time after sleep
    SYSTEMTIME st2;
    GetSystemTime(&st2);

    // Calculate final microseconds
    long long final_time = (static_cast<long long>(st2.wDay) * 24LL * 60LL * 60LL * 1000000LL)
        + (static_cast<long long>(st2.wHour) * 60LL * 60LL * 1000000LL)
        + (static_cast<long long>(st2.wMinute) * 60LL * 1000000LL)
        + (static_cast<long long>(st2.wSecond) * 1000000LL)
        + (static_cast<long long>(st2.wMilliseconds) * 1000LL);

    // Print final time components
    std::cout << "Final time components - Day: " << st2.wDay << ", Hour: " << st2.wHour
        << ", Minute: " << st2.wMinute << ", Second: " << st2.wSecond
        << ", Milliseconds: " << st2.wMilliseconds
        << ", Total microseconds: " << final_time << std::endl;

    // Calculate and verify elapsed time
    long long elapsed_microseconds = final_time - initial_time;
    std::cout << "\nElapsed time: " << elapsed_microseconds << " microseconds" << std::endl;

    // 1 second should be 1,000,000 microseconds
    // Allow for some system delay (between 0.9 and 1.1 seconds)
    assert(elapsed_microseconds >= 900000 && elapsed_microseconds <= 1100000 &&
        "Elapsed time should be approximately 1,000,000 microseconds");

    std::cout << "System Time verified." << std::endl;
    LM.writeLog("System Time tests completed successfully!\n");
}


// Test Clock 
void Test::testClock() {
    std::cout << "\nTesting Clock class..." << std::endl;

    df::Clock clock_t;
    // Test initial state
    long int initial_split = clock_t.split();
    assert(initial_split >= 0 && "Clock:: Initial split should be non-negative");
    std::cout << "Clock:: Initial state verified" << std::endl;

    Sleep(100); // Wait 100 milliseconds (100,000 microseconds or 0.1 seconds)
    long int elapsed_time = clock_t.delta();
    std::cout << "Clock:: Elapsed time (delta): " << elapsed_time << " microseconds" << std::endl;
    assert(elapsed_time >= 100000 && elapsed_time <= 120000 && "Clock::delta() timing mismatch!");

    Sleep(50);
    long int split_time = clock_t.split();
    std::cout << "Clock:: Elapsed time (split): " << split_time << " microseconds" << std::endl;
    assert(split_time >= 50000 && split_time <= 66000 && "Clock::split() timing mismatch!");

    std::cout << "Clock class verified." << std::endl;

    LM.writeLog("Clock tests completed successfully!\n");
}

// Test Vector
void Test::testVector() {
    std::cout << "\nTesting Vector class..." << std::endl;

    df::Vector v_0; // Default Vector
    assert(v_0.getX() == 0 && "Vector()::getX() return incorrectly");
    assert(v_0.getY() == 0 && "Vector()::getY() return incorrectly");
    std::cout << "Vector:: Initial state verified" << std::endl;

    df::Vector v_t(3, 4); // Vector get test
    assert(v_t.getX() == 3 && "Vector()::getX() return incorrectly");
    assert(v_t.getY() == 4 && "Vector()::getY() return incorrectly");
    assert(v_t.getMagnitude() == 5 && "Vector()::getMagnitude() return incorrectly"); // 3^2 + 4^2 = 5 Pythagorean theorem

    v_t.setX(5); // Vector set test
    assert(v_t.getX() == 5 && "Vector()::setX() return incorrectly");
    v_t.setY(12);
    assert(v_t.getY() == 12 && "Vector()::setY() return incorrectly");

    df::Vector v_2(1, 2); // Vector addition test
    df::Vector sum = v_t + v_2; // (5, 12) + (1, 2) = (6, 14)
    assert((sum.getX() == 6 && sum.getY() == 14) && "Vector()::sum return incorrectly");

    v_t.normalize(); // Vector normalize test
    assert(v_t.getMagnitude() == 1 && "Vector()::normalize() return incorrectly"); // (5, 12) / 13 = (0.38, 0.92)

    std::cout << "Vector class verified" << std::endl;

    LM.writeLog("Vector tests completed successfully!\n");
}

// Test Object
void Test::testObject() {
    std::cout << "\nTesting Object class..." << std::endl;

    // Test Object Initialization
    df::Object obj;
    // assert(obj.getId() == 0 && "Object::getId() return incorrectly in initial state");
    assert(obj.getType() == "Object" && "Object::getType() return incorrectly in initial state");
    assert(obj.getPosition().getX() == 0 && obj.getPosition().getY() == 0 && "Object::getPosition() return incorrectly in initial state");
    std::cout << "Object:: Initial state verified" << std::endl;

    obj.setId(42);
    assert(obj.getId() == 42 && "Object::setId() return incorrectly");
    obj.setType("Test");
    assert(obj.getType() == "Test" && "Object::setType() return incorrectly");

    obj.setPosition(df::Vector(3, 4));
    assert((obj.getPosition().getX() == 3 && obj.getPosition().getY() == 4) && "Object::setPosition() return incorrectly");
    df::Vector pos(10, 20);
    obj.setPosition(pos);
    assert((obj.getPosition().getX() == 10 && obj.getPosition().getY() == 20) && "Object::setPosition() and df::Vector call return incorrectly");

    std::cout << "Object class verified" << std::endl;
    LM.writeLog("Object tests completed successfully!\n");

    df::Object obj2;
    obj.setVelocity(df::Vector(-0.25, 0)); // Move left at 0.25 spaces per step.

    df::Vector predicted_pos = obj2.predictPosition(); 
    LM.writeLog("Predicted Position: (%f, %f)\n", predicted_pos.getX(), predicted_pos.getY());
}

// Test ObjectList
void Test::testObjectList() {
    std::cout << "\nTesting ObjectList class..." << std::endl;

    // Test ObjectList Initialization
    df::ObjectList obj_list;
    assert(obj_list.getCount() == 0 && "ObjectList::getCount() return incorrectly in initial state");
    assert(obj_list.isEmpty() && "ObjectList::isEmpty() return incorrectly in initial state");
    assert(!obj_list.isFull() && "ObjectList::isFull() return incorrectly in initial state");
    std::cout << "ObjectList:: Initial state verified" << std::endl;

    // Test ObjectList Insertion
    df::Object obj_1, obj_2, obj_3, obj_4, obj_5;

    obj_list.insert(&obj_1);
    assert(obj_list.getCount() == 1 && "ObjectList::getCount() return incorrectly (1)");
    obj_list.insert(&obj_2);
    assert(obj_list.getCount() == 2 && "ObjectList::getCount() return incorrectly (2)");
    obj_list.insert(&obj_3);
    assert(obj_list.getCount() == 3 && "ObjectList::getCount() return incorrectly (3)");


    obj_list.insert(&obj_4);
    assert(!obj_list.isFull() && "ObjectList::isFull() return incorrectly [1]");


    // Test ObjectList Clear
    obj_list.clear();
    assert(obj_list.getCount() == 0 && "ObjectList::getCount() return incorrectly (0)");
    assert(obj_list.isEmpty() && "ObjectList::isEmpty() return incorrectly [2]");
    std::cout << "ObjectList::clear() verified" << std::endl;

    // Test Indexing
    df::ObjectList obj_list_I;
    df::Object obj_a, obj_b, obj_c;
    obj_list.insert(&obj_a);
    obj_list.insert(&obj_b);
    obj_list.insert(&obj_c);

    // Success cases
    assert(obj_list[0] == &obj_a && "ObjectList::operator[] return incorrectly (index 0)");
    assert(obj_list[1] == &obj_b && "ObjectList::operator[] return incorrectly (index 1)");
    assert(obj_list[2] == &obj_c && "ObjectList::operator[] return incorrectly (index 2)");
    std::cout << "ObjectList::operator[] verified (success case)" << std::endl;

    // Failure cases
    try {
        obj_list[-1]; // Accessing negative index
        assert(false && "ObjectList::operator[] should throw exception for negative index");
    }
    catch (const std::out_of_range& e) {
        std::cout << "ObjectList::operator[] verified (failure case: negative index)" << std::endl;
    }

    try {
        obj_list[obj_list.getCount()]; // Accessing index beyond count
        assert(false && "ObjectList::operator[] should throw exception for out-of-bounds index");
    }
    catch (const std::out_of_range& e) {
        std::cout << "ObjectList::operator[] verified (failure case: out-of-bounds index)" << std::endl;
    }

    std::cout << "ObjectList class verified" << std::endl;
    LM.writeLog("ObjectList tests completed successfully!\n");
}

/*
// Test GameManager
void Test::testGameManager() {
    std::cout << "\nTesting GameManager..." << std::endl;

    // Test singleton
    df::GameManager& gm_t = df::GameManager::getInstance(); // GameManager test instance
    df::GameManager& gm_2 = df::GameManager::getInstance();
    assert(&gm_t == &gm_2 && "getInstance should return same instance");
    std::cout << "GameManager:: Singleton verified" << std::endl;

    // Test startup
    assert(GM.startUp() == 0 && "GameManager::startUp() should return 0 on success");
    std::cout << "GameManager::startUp(): verified." << std::endl;

    // Test game loop timing
    df::Clock clock_t;
    clock_t.delta();

    Sleep(100);
    long int elapsed_time = clock_t.delta();
    std::cout << "GameManager::delta(): elapsed_time =" << elapsed_time <<"." << std::endl;
    assert(elapsed_time >= 90000 && elapsed_time <= 120000 && "Game loop timing mismatch!");

    // Test get frame time
    int frame_time = GM.getFrameTime();
    std::cout << "GameManager:: Frame time: " << frame_time << " ms" << std::endl;
    assert(frame_time == FRAME_TIME_DEFAULT && "Frame time should match default value");

    // Test game over behavior
    GM.setGameOver(true);
    assert(GM.getGameOver() == true && "GameManager should recognize game over state");
    std::cout << "GameManager::getGameOver(): verified." << std::endl;

    // Test shutdown

    // GM.shutDown();
    // assert(GM.getGameOver() && "Game should be over after shutDown");
    // std::cout << "GameManager::shutDown(): verified." << std::endl;

LM.writeLog("GameManager tests completed successfully!\n");
}

*/