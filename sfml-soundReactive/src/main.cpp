#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iostream>

class AudioVisualizer {
private:
    std::vector<sf::RectangleShape> bars;
    std::vector<float> frequencies;
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;
    const int numBars;
    const float windowWidth;
    const float windowHeight;
    const float barWidth;
    const float maxBarHeight;

    // For smoothing animation
    std::vector<float> smoothedHeights;
    const float smoothingFactor = 0.1f;

public:
    AudioVisualizer(int numberOfBars, float winWidth, float winHeight)
        : numBars(numberOfBars), windowWidth(winWidth), windowHeight(winHeight),
          barWidth(winWidth / numberOfBars), maxBarHeight(winHeight * 0.9f) {

        bars.resize(numBars);
        frequencies.resize(numBars, 0.0f);
        smoothedHeights.resize(numBars, 0.0f);

        // Initialize bars
        for (int i = 0; i < numBars; ++i) {
            bars[i].setSize(sf::Vector2f(barWidth - 2, 0)); // -2 for spacing
            bars[i].setPosition(i * barWidth + 1, windowHeight);

            // Create gradient color effect
            float ratio = static_cast<float>(i) / numBars;
            sf::Uint8 r = static_cast<sf::Uint8>(255 * (1.0f - ratio));
            sf::Uint8 g = 100;
            sf::Uint8 b = static_cast<sf::Uint8>(255 * ratio);
            bars[i].setFillColor(sf::Color(r, g, b));
        }
    }

    bool loadAudio(const std::string& filename) {
        if (!soundBuffer.loadFromFile(filename)) {
            return false;
        }
        sound.setBuffer(soundBuffer);
        return true;
    }

    void playAudio() {
        sound.play();
    }

    void stopAudio() {
        sound.stop();
    }

    void pauseAudio() {
        sound.pause();
    }

    sf::Sound::Status getStatus() const {
        return sound.getStatus();
    }

    void analyzeAudio() {
        // Get audio samples
        const sf::Int16* samples = soundBuffer.getSamples();
        sf::Uint64 sampleCount = soundBuffer.getSampleCount();
        unsigned int sampleRate = soundBuffer.getSampleRate();

        if (sampleCount == 0) return;

        // Calculate current playback position
        sf::Time playOffset = sound.getPlayingOffset();
        sf::Uint64 currentSample = static_cast<sf::Uint64>(playOffset.asSeconds() * sampleRate);

        // Analyze a small window of samples around current position
        const int windowSize = 4096; // Power of 2 for better performance
        sf::Uint64 startSample = (currentSample > windowSize/2) ? currentSample - windowSize/2 : 0;
        sf::Uint64 endSample = std::min(startSample + windowSize, sampleCount);

        // Clear frequency data
        std::fill(frequencies.begin(), frequencies.end(), 0.0f);

        if (startSample >= endSample) return;

        // Simple frequency analysis by dividing audio range into bands
        int samplesPerBand = (endSample - startSample) / numBars;
        if (samplesPerBand == 0) samplesPerBand = 1;

        for (int i = 0; i < numBars; ++i) {
            float amplitude = 0.0f;
            int bandStart = startSample + i * samplesPerBand;
            int bandEnd = std::min(bandStart + samplesPerBand, static_cast<int>(endSample));

            // Calculate RMS amplitude for this frequency band
            for (int j = bandStart; j < bandEnd; ++j) {
                if (j < sampleCount) {
                    float sample = static_cast<float>(samples[j]) / 32768.0f; // Normalize
                    amplitude += sample * sample;
                }
            }

            if (bandEnd > bandStart) {
                amplitude = std::sqrt(amplitude / (bandEnd - bandStart));
            }

            frequencies[i] = amplitude;
        }
    }

    void update() {
        if (sound.getStatus() == sf::Sound::Playing) {
            analyzeAudio();
        } else {
            // Fade out when not playing
            for (float& freq : frequencies) {
                freq *= 0.95f;
            }
        }

        // Update bar heights with smoothing
        for (int i = 0; i < numBars; ++i) {
            float targetHeight = frequencies[i] * maxBarHeight * 5.0f; // Scale factor
            targetHeight = std::min(targetHeight, maxBarHeight);

            // Smooth the animation
            smoothedHeights[i] += (targetHeight - smoothedHeights[i]) * smoothingFactor;

            // Update bar size and position
            bars[i].setSize(sf::Vector2f(barWidth - 2, smoothedHeights[i]));
            bars[i].setPosition(i * barWidth + 1, windowHeight - smoothedHeights[i]);

            // Dynamic color based on amplitude
            float intensity = smoothedHeights[i] / maxBarHeight;
            sf::Uint8 alpha = static_cast<sf::Uint8>(255 * std::min(1.0f, intensity + 0.3f));
            sf::Color currentColor = bars[i].getFillColor();
            currentColor.a = alpha;
            bars[i].setFillColor(currentColor);
        }
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& bar : bars) {
            window.draw(bar);
        }
    }

    // Get reference to bars for external manipulation if needed
    std::vector<sf::RectangleShape>& getBars() {
        return bars;
    }
};

int main() {
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 600;
    const int NUM_BARS = 64;


    AudioVisualizer visualizer(NUM_BARS, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Load your audio file here
    if (!visualizer.loadAudio("/home/deba/Prog/Algor-lib/sfml-soundReactive/fein.ogg")) { // Replace with your audio file
        // If file doesn't exist, create some sample bars anyway
        std::cout << "Could not load audio file 'audio.wav'. Visualizer will show demo mode.\n";
    }

    sf::Clock clock;
    bool isPlaying = false;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Audio Visualizer");
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Space to play/pause
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    if (!isPlaying) {
                        visualizer.playAudio();
                        isPlaying = true;
                    } else {
                        if (visualizer.getStatus() == sf::Sound::Playing) {
                            visualizer.pauseAudio();
                        } else {
                            visualizer.playAudio();
                        }
                    }
                }

                // R to restart
                if (event.key.code == sf::Keyboard::R) {
                    visualizer.stopAudio();
                    visualizer.playAudio();
                    isPlaying = true;
                }

                // S to stop
                if (event.key.code == sf::Keyboard::S) {
                    visualizer.stopAudio();
                    isPlaying = false;
                }
            }
        }

        // Update visualizer
        visualizer.update();

        // Render
        window.clear(sf::Color::Black);
        visualizer.draw(window);

        // Draw instructions
        sf::Font font;
        // Note: You'll need to load a font file or use default system font
        // font.loadFromFile("arial.ttf");

        window.display();
    }

    return 0;
}

// Compile with:
// g++ -o visualizer main.cpp -lsfml-graphics -lsfml-audio -lsfml-system
