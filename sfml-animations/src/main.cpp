#include <SFML/Graphics.hpp>
#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include "./sorting.hpp"


int main() {

    constexpr int MAX_SIMULTANEOUS_SOUNDS = 2;
    std::vector<sf::Sound> soundPool(MAX_SIMULTANEOUS_SOUNDS);
    int currentSoundIndex = 0;

    sf::SoundBuffer buffer;
    if(!buffer.loadFromFile("/home/deba/Documents/lmms/projects/fein2.ogg")) {
    // if(!buffer.loadFromFile("/usr/share/lmms/samples/instruments/piano01.ogg")) {
        std::cerr << "Error loading from sound file" << std::endl;
        std::cerr << "Check if the file exists and its path is correct" << std::endl;
        return -1;
    }

    for(auto& s: soundPool) {
        s.setBuffer(buffer);
    }
    sf::RenderWindow window(sf::VideoMode(1024, 720), "bounzerd");

    std::vector<int> arraytobe = {63, 91, 17, 104, 45, 82, 29, 116, 8, 73, 39, 97, 54, 118, 22, 66, 88, 13, 101, 49, 75, 34, 109, 19, 85, 52, 96, 11, 77, 43, 112, 26, 69, 94, 6, 81, 48, 105, 35, 92, 58, 114, 21, 70, 87, 14, 102, 59, 78, 41, 107, 24, 83, 50, 119, 33, 90, 16, 72, 55};
    std::vector<sf::RectangleShape> barsToBeSorted;

    for(int i = 0; i < int(arraytobe.size()); ++i) {
        sf::RectangleShape bar(sf::Vector2f(10.f, arraytobe[i]*5.f));
        bar.setPosition(sf::Vector2f(5.f + i * 16.f, window.getSize().y - bar.getSize().y));
        bar.setOutlineThickness(2.f);
        bar.setOutlineColor(sf::Color::Red);
        barsToBeSorted.push_back(bar);
    }

    InsertionSortState sorter;
    BubbleSortState bubblesorter;
    SelectionSortState selectionsorter;
    MergeSortState mergesorter;
    bool sorting = false;
    bool bubble_sorting = false;
    bool selection_sorting = false;
    bool merge_sorting = false;

    SortingDoneState doneIterator;

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) { // event loop
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                if( !sorting && !bubble_sorting && !selection_sorting && !merge_sorting ) {
                    switch (event.key.code) {
                        case sf::Keyboard::S:
                            sorting = true;
                            sorter = InsertionSortState();
                            doneIterator = SortingDoneState();
                            break;
                        case sf::Keyboard::B:
                            bubble_sorting = true;
                            bubblesorter = BubbleSortState();
                            doneIterator = SortingDoneState();
                            break;
                        case sf::Keyboard::E:
                            selection_sorting = true;
                            selectionsorter = SelectionSortState();
                            doneIterator = SortingDoneState();
                            break;
                        case sf::Keyboard::M:
                            merge_sorting = true;
                            mergesorter.initialize(barsToBeSorted);
                            doneIterator = SortingDoneState();
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        float shouldPlaySound = -1.f;

        if(sorting && !sorter.done) {
            shouldPlaySound = sorter.step(barsToBeSorted);
            if(shouldPlaySound >= 0.f) {
                soundPool[currentSoundIndex].stop();
                soundPool[currentSoundIndex].setPlayingOffset(sf::Time::Zero);
                soundPool[currentSoundIndex].setPitch(shouldPlaySound/200.f);
                soundPool[currentSoundIndex].play();

                currentSoundIndex = (currentSoundIndex + 1) % MAX_SIMULTANEOUS_SOUNDS;
            }
            sf::sleep(sf::milliseconds(30));
        } else if(bubble_sorting && !bubblesorter.done) {
            shouldPlaySound = bubblesorter.step(barsToBeSorted);
            if(shouldPlaySound >= 0.f) {
                soundPool[currentSoundIndex].stop();
                soundPool[currentSoundIndex].setPlayingOffset(sf::Time::Zero);
                soundPool[currentSoundIndex].setPitch(shouldPlaySound/200.f);
                soundPool[currentSoundIndex].play();

                currentSoundIndex = (currentSoundIndex + 1) % MAX_SIMULTANEOUS_SOUNDS;
            }
            sf::sleep(sf::milliseconds(30));
        } else if(selection_sorting && !selectionsorter.done) {
            shouldPlaySound = selectionsorter.step(barsToBeSorted);
            if(shouldPlaySound >= 0.f) {
                soundPool[currentSoundIndex].stop();
                soundPool[currentSoundIndex].setPlayingOffset(sf::Time::Zero);
                soundPool[currentSoundIndex].setPitch(shouldPlaySound/200.f);
                soundPool[currentSoundIndex].play();

                currentSoundIndex = (currentSoundIndex + 1) % MAX_SIMULTANEOUS_SOUNDS;
            }
            sf::sleep(sf::milliseconds(30));
        } else if(merge_sorting && !mergesorter.done) {
            shouldPlaySound = mergesorter.step(barsToBeSorted);
            if(shouldPlaySound >= 0.f) {
                soundPool[currentSoundIndex].stop();
                soundPool[currentSoundIndex].setPlayingOffset(sf::Time::Zero);
                soundPool[currentSoundIndex].setPitch(shouldPlaySound/200.f);
                soundPool[currentSoundIndex].play();

                currentSoundIndex = (currentSoundIndex + 1) % MAX_SIMULTANEOUS_SOUNDS;
            }
            sf::sleep(sf::milliseconds(30));
        } else if(sorter.done || selectionsorter.done || bubblesorter.done || mergesorter.done) {
            shouldPlaySound = doneIterator.step(barsToBeSorted);
            if(shouldPlaySound >= 0.f) {
                soundPool[currentSoundIndex].stop();
                soundPool[currentSoundIndex].setPlayingOffset(sf::Time::Zero);
                soundPool[currentSoundIndex].setPitch(shouldPlaySound/200.f);
                soundPool[currentSoundIndex].play();

                currentSoundIndex = (currentSoundIndex + 1) % MAX_SIMULTANEOUS_SOUNDS;
            }
            sf::sleep(sf::milliseconds(30));
        } else {
            sorting = false;
            bubble_sorting = false;
            selection_sorting = false;
            merge_sorting = false;
        }

        window.clear();
        set_new_positions(barsToBeSorted, window);
        window.display();
    }

  return 0;
}
