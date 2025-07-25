#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <stack>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Audio.hpp>

void insertion_sort(std::vector<sf::RectangleShape> &A, sf::Sound s, sf::RenderWindow &window);

void swap_two_bars(sf::RectangleShape &A, sf::RectangleShape &B);

void set_new_positions(std::vector<sf::RectangleShape> &A, sf::RenderWindow &window);



enum class MergeSortPhase { DIVIDE, CONQUER };

struct MergeSortFrame {
    int left;
    int right;
    int mid;
    MergeSortPhase phase;

    //Optional merge process info;
    bool merged = false;
    int i = 0, j = 0, k = 0;
    std::vector<float> L, R;
};

struct MergeSortState {
    std::stack<MergeSortFrame> callStack;
    bool done = false;

    void initialize(const std::vector<sf::RectangleShape>& A);
    float step(std::vector<sf::RectangleShape>& A);
};

struct SortingDoneState {
    int i = 0;
    bool done = false;
    int highlightIndex = -1;
    float step(std::vector<sf::RectangleShape>& A);
};

struct InsertionSortState {
    int j = 1;
    int i = 0;
    bool isSwapping = false;
    bool done = false;
    sf::RectangleShape key;
    int highlightIndex1 = -1;
    int highlightIndex2 = -1;

    float step(std::vector<sf::RectangleShape>& A);
};

struct BubbleSortState {
    int i = 0;
    int j = 0;
    bool done = false;
    bool swapped = false;
    int highlightIndex1 = -1;
    int highlightIndex2 = -1;

    float step(std::vector<sf::RectangleShape>& A);
};

struct SelectionSortState {
    int i = 0;
    int j = 1;
    int minIndex = 0;
    bool done = false;
    int highlightIndex1 = -1;
    int highlightIndex2 = -1;

    float step(std::vector<sf::RectangleShape>& A);
};
