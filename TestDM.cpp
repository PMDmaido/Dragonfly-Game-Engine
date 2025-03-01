// Test.cpp
#include "TestDM.h"
#include "DisplayManager.h"
//#include "TestObject.h"

void TestDM::runTest() {
    // Check-point 1
    //test1();
	test2();
}


// Test base Manager 
void TestDM::test1() {
    DM.startUp();
    sf::RenderWindow* window = DM.getWindow();
    sf::Font font;
    sf::Text text(font);
    text.setString("Hello, world!");
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition({ 10, 10 }); // Set position on window (in pixels).

    window->clear();
    window->draw(text);
    window->display();

    int horizontal_chars = DM.getHorizontal();
    int vertical_chars = DM.getVertical();

    LM.writeLog("DisplayManager::getHorizontal(): %d\n", horizontal_chars);
    LM.writeLog("DisplayManager::getVertical(): %d\n", vertical_chars);

    Sleep(2000);
    DM.shutDown();
}

void TestDM::test2() {
    // TEST DisplayManager outside of GameManager

    DM.startUp();

    DM.drawCh(df::Vector({5,5}), '*', df::GREEN);
    DM.drawCh(df::Vector({ 10,7 }), 'X', df::RED);

    DM.drawString(df::Vector({ 20,20 }), "Hello, world!", df::LEFT_JUSTIFIED, df::RED);
    DM.drawString(df::Vector({ 20,15 }), "Hello, world!", df::CENTER_JUSTIFIED, df::YELLOW);
    DM.drawString(df::Vector({ 20,10 }), "Hello, world!", df::RIGHT_JUSTIFIED, df::BLACK);

    DM.swapBuffers();

    Sleep(2000);

    DM.shutDown();
}