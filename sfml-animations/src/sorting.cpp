#include "./sorting.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <iostream>

float SortingDoneState::step(std::vector<sf::RectangleShape>& A) {
    int n = static_cast<int>(A.size());
    if(done) {
        return -1.f;
    }
    if(highlightIndex != -1) A[highlightIndex].setFillColor(sf::Color::White);
    highlightIndex = -1;

    if(i >= n) {
        done = true;
    } else {
        highlightIndex = i;
        A[highlightIndex].setFillColor(sf::Color::Red);
        ++i;
        return A[i].getSize().y;
    }

    return -1.f;
}

void MergeSortState::initialize(const std::vector<sf::RectangleShape> &A) {
    done = false;
    while(!callStack.empty()) {
        callStack.pop();
    }
    callStack.push({0, static_cast<int>(A.size() - 1), -1, MergeSortPhase::DIVIDE});
    // std::cout << callStack.size() << '\n';
}

float MergeSortState::step(std::vector<sf::RectangleShape>& A) {
    if(done || callStack.empty()) {
        done = true;
        return -1.f;
    }

    MergeSortFrame& frame = callStack.top();
    // std::cout << frame.left << "\t" << frame.right << "\n";

    if(frame.phase == MergeSortPhase::DIVIDE) {

        if(frame.left >= frame.right) {
            callStack.pop();
            return -1.f;
        }

        frame.mid = (frame.left + frame.right) / 2;

        //Push right side first, then left
        callStack.push({frame.mid + 1, frame.right, -1, MergeSortPhase::DIVIDE});
        callStack.push({frame.left, frame.mid, -1, MergeSortPhase::DIVIDE});

        frame.phase = MergeSortPhase::CONQUER;
        return -1.f;
    }

    else if (frame.phase == MergeSortPhase::CONQUER) {
        if(!frame.merged) {
            int n1 = frame.mid - frame.left + 1;
            int n2 = frame.right - frame.mid;

            frame.L.resize(n1);
            frame.R.resize(n2);

            //setting up the L and R arrays with unsorted values
            for(int i = 0; i < n1; ++i) {
                frame.L[i] = A[frame.left + i].getSize().y;
            }
            // for(int i = 0; i < n1; ++i) {
            //     std::cout << frame.L[i] << '\t';
            // }
            // std::cout << '\n';
            for(int j = 0; j < n2; ++j) {
                frame.R[j] = A[frame.mid + 1 + j].getSize().y;
            }
            // for(int j = 0; j < n2; ++j) {
            //     std::cout << frame.R[j] << '\t';
            // }
            // std::cout << '\n';

            frame.i = frame.j = 0;
            frame.k = frame.left;
            frame.merged = true;
        }

        //this is the main block to handle correct sorting of values
        if(frame.i < frame.L.size() && frame.j < frame.R.size()) {

            if(frame.L[frame.i] <= frame.R[frame.j]) {
                A[frame.k].setSize({A[frame.k].getSize().x, frame.L[frame.i++]});
            } else {
                A[frame.k].setSize({A[frame.k].getSize().x, frame.R[frame.j++]});
            }
            A[frame.k].setFillColor(sf::Color::Red);
            return A[frame.k++].getSize().y;
        }

        if(frame.i < frame.L.size()) {
            A[frame.k].setSize({A[frame.k].getSize().x, frame.L[frame.i++]});
            A[frame.k].setFillColor(sf::Color::Red);
            return A[frame.k++].getSize().y;
        }

        if(frame.j < frame.R.size()) {
            A[frame.k].setSize({A[frame.k].getSize().x, frame.R[frame.j++]});
            A[frame.k].setFillColor(sf::Color::Red);
            return A[frame.k++].getSize().y;
        }

        callStack.pop();
        return -1.f;
    }

    return -1.f;
}

float SelectionSortState::step(std::vector<sf::RectangleShape>& A) {
    int n = A.size();
    float returnValue = -1.f;

    if(highlightIndex1 != -1) A[highlightIndex1].setFillColor(sf::Color::White);
    if(highlightIndex2 != -1) A[highlightIndex2].setFillColor(sf::Color::White);
    highlightIndex1 = highlightIndex2 = -1;

    if(done) {
        return -1.f;
    }

    if(j >= n) {
        if(minIndex != i) {
            swap_two_bars(A[i], A[minIndex]);
            minIndex = i;
            highlightIndex1 = i;
            highlightIndex2 = minIndex;
            A[i].setFillColor(sf::Color::Red);
            A[minIndex].setFillColor(sf::Color::Red);
            return A[i].getSize().y;//return the magnitude that the bar represents
        }
        i++;
        j = i + 1;
        minIndex = i;
    } else {
        //this block increments j and finds the ith minimum throughout the array
        if(A[j].getSize().y < A[minIndex].getSize().y) {
            minIndex = j;
            returnValue = A[j].getSize().y;
            highlightIndex1 = j;
            A[j].setFillColor(sf::Color::Red);
        }
        j++;
    }

    if(i >= n - 1) {
        done = true;
    }

    return returnValue;
}

float BubbleSortState::step(std::vector<sf::RectangleShape>& A) {

    int n = A.size();

    if(highlightIndex1 != -1) A[highlightIndex1].setFillColor(sf::Color::White);
    if(highlightIndex2 != -1) A[highlightIndex2].setFillColor(sf::Color::White);
    highlightIndex1 = highlightIndex2 = -1;

    if(done) {
        return -1.f;
    }

    if(j > n - i - 1) {
        if(!swapped) {
            done = true;
            return -1.f;
        }
        j = 0;
        ++i;
        swapped = false;
    }


    if(A[j - 1].getSize().y >  A[j].getSize().y) {
        swap_two_bars(A[j-1], A[j]);
        swapped = true;
        j++;
        highlightIndex1 = j;
        highlightIndex2 = j - 1;
        A[j].setFillColor(sf::Color::Red);
        A[j-1].setFillColor(sf::Color::Red);
        return (A[j - 1].getSize().y);
    }

    j++;
    return -1.f;
}

float InsertionSortState::step(std::vector<sf::RectangleShape> &A) {

    if(done) return -1.f;

    if(highlightIndex1 != -1) A[highlightIndex1].setFillColor(sf::Color::White);
    if(highlightIndex2 != -1) A[highlightIndex2].setFillColor(sf::Color::White);
    highlightIndex1 = highlightIndex2 = -1;

    if(j >= (int)A.size()) {
        done = true;
        return -1.f;
    }

    if (!isSwapping) {
        key = A[j];
        i = j - 1;
        isSwapping = true;
    }

    if(i >= 0 && A[i].getSize().y > key.getSize().y) {
        swap_two_bars(A[i + 1], A[i]);

        highlightIndex1 = i;
        highlightIndex2 = i + 1;
        A[i].setFillColor(sf::Color::Red);
        A[i+1].setFillColor(sf::Color::Red);

        i--;
        // return (float)(A[i].getSize().y - key.getSize().y);
        return (float)(A[i].getSize().y);
    } else {
        A[i+1] = key;
        isSwapping = false;
        j++;
    }

    return -1.f;
}

void swap_two_bars(sf::RectangleShape &A, sf::RectangleShape &B) {
    sf::RectangleShape temp_bar = A;
    A = B;
    B = temp_bar;
}

void set_new_positions(std::vector<sf::RectangleShape> &A, sf::RenderWindow &window) {
    for(int i = 0; i < (int)A.size(); ++i) {
        A[i].setPosition(sf::Vector2f(5.f + i*16.f, window.getSize().y - A[i].getSize().y));
        window.draw(A[i]);
    }
}
