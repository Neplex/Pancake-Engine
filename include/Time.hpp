//
// Created by Darenn on 13/01/2017.
//

#ifndef PANCAKE_TIME_HPP
#define PANCAKE_TIME_HPP


class Time {
public:
    /**
     * The time in seconds it took to complete the last frame.
     * @return The time in seconds it took to complete the last frame.
     */
    static float getDeltaTime();
    Time() : deltaTime(0) {

    }
    float deltaTime;
};


#endif //PANCAKE_TIME_HPP
