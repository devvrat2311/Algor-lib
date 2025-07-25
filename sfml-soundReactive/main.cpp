
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main() {

    sf::Sound sound;
    sf::SoundBuffer buffer;
    if(!buffer.loadFromFile("/home/deba/Prog/Algor-lib/sfml-soundReactive/fein.ogg")) {
        std::cerr << "Error loading from sound file" << std::endl;
        std::cerr << "Check if the file exists and its path is correct" << std::endl;
        return -1;
    }

    sound.setBuffer(buffer);


    bool isPlaying = false;

    sf::RenderWindow window(sf::VideoMode(1024, 720), "soundReactiveBars");
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                if(event.key.code == sf::Keyboard::Space) {
                    if(!isPlaying) {
                        isPlaying = true;
                        sound.play();
                    } else {
                        isPlaying = false;
                        sound.pause();
                    }
                }
                if(event.key.code == sf::Keyboard::S) {
                    isPlaying = false;
                    sound.stop();
                }
            }
        }

        window.clear(isPlaying ? sf::Color(66, 162, 141) : sf::Color(248, 114, 97));
        window.display();
    }
}
